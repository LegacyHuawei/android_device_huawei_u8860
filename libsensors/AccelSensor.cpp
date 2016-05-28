/*
 * Copyright (C) 2012 The Android Open-Source Project
 * Copyright (C) 2014 Rudolf Tammekivi <rtammekivi@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define ACCEL_DEBUG 0

#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <cutils/log.h>

#include "AccelSensor.h"

/*****************************************************************************/

AccelSensor::AccelSensor()
    : SensorBase(NULL, LIS3DH_NAME),
      mInputReader(4), mEnabled(0), mHasPendingEvent(false)
{
    ALOGD_IF(ACCEL_DEBUG, "AccelSensor: Initializing...");

    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_A;
    mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
}

AccelSensor::~AccelSensor() {
}

int AccelSensor::setEnable(int32_t handle, int enabled)
{
    ALOGD_IF(ACCEL_DEBUG, "AccelSensor: enable %d %d", handle, enabled);

    if (mEnabled == enabled)
        return 0;

    char buf[2];
    snprintf(buf, sizeof(buf), "%d", !!enabled);
    int ret = write_sys_attribute(LIS3DH_SYSFS_PATH "enable", buf, sizeof(buf));
    if (ret)
        return ret;

    mEnabled = enabled;
    return 0;
}

int AccelSensor::setDelay(int32_t handle, int64_t ns)
{
    ALOGD_IF(ACCEL_DEBUG, "AccelSensor: setDelay %d %lld", handle, ns);

    if (!mEnabled)
        return 0;

    int ms = ns / 1000000;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", ms);
    int ret = write_sys_attribute(LIS3DH_SYSFS_PATH "pollrate_ms", buf, sizeof(buf));
    if (ret)
        return ret;

    return 0;
}

bool AccelSensor::hasPendingEvents() const
{
    return mHasPendingEvent;
}

int AccelSensor::readEvents(sensors_event_t* data, int count)
{
    if (count < 1)
        return -EINVAL;

    if (mHasPendingEvent)
    {
        mHasPendingEvent = false;
        mPendingEvent.timestamp = getTimestamp();
        *data = mPendingEvent;
        return mEnabled;
    }

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
        return n;

    int numEventReceived = 0;
    input_event const* event;

    while (count && mInputReader.readEvent(&event))
    {
        int type = event->type;
        if (type == EV_ABS)
        {
            if (event->code == EVENT_TYPE_ACCEL_X)
                mPendingEvent.acceleration.x = event->value * CONVERT_A;
            else if (event->code == EVENT_TYPE_ACCEL_Y)
                mPendingEvent.acceleration.y = event->value * CONVERT_A;
            else if (event->code == EVENT_TYPE_ACCEL_Z)
                mPendingEvent.acceleration.z = event->value * CONVERT_A;
        }
        else if (type == EV_SYN)
        {
            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled)
            {
                *data++ = mPendingEvent;
                count--;
                numEventReceived++;
            }
        } else {
            ALOGE("AccelSensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }

    return numEventReceived;
}
