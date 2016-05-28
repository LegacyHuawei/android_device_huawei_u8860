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

#define GYRO_DEBUG 0

#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <cutils/log.h>

#include "GyroSensor.h"

/*****************************************************************************/

GyroSensor::GyroSensor()
    : SensorBase(NULL, L3G4200D_NAME),
      mInputReader(8), mPendingMask(0)
{
    ALOGD_IF(GYRO_DEBUG, "GyroSensor: Initializing...");

    for (int i = 0; i < numSensors; i++)
        mEnabled[i] = 0;

    memset(mPendingEvents, 0, sizeof(mPendingEvents));

    mPendingEvents[Gyroscope].version = sizeof(sensors_event_t);
    mPendingEvents[Gyroscope].sensor = ID_G;
    mPendingEvents[Gyroscope].type = SENSOR_TYPE_GYROSCOPE;

    mPendingEvents[Temperature].version = sizeof(sensors_event_t);
    mPendingEvents[Temperature].sensor = ID_T;
    mPendingEvents[Temperature].type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
}

GyroSensor::~GyroSensor() {
}

int GyroSensor::setEnable(int32_t handle, int enabled)
{
    ALOGD_IF(GYRO_DEBUG, "GyroSensor: enable %d %d", handle, enabled);

    int id = handle2id(handle);

    if (mEnabled[id] == enabled)
        return 0;

    mEnabled[id] = enabled;

    if (enabled || (!mEnabled[Gyroscope] && !mEnabled[Temperature])) {
        char buf[2];
        snprintf(buf, sizeof(buf), "%d", !!enabled);

        int ret = write_sys_attribute(L3G4200D_SYSFS_PATH "enable", buf, sizeof(buf));
        if (ret)
            return ret;
    }

    return 0;
}

int GyroSensor::setDelay(int32_t handle, int64_t ns)
{
    ALOGD_IF(GYRO_DEBUG, "GyroSensor: setDelay %d %lld", handle, ns);

    int id = handle2id(handle);

    /* Prioritize gyroscope, temperature cannot be changed. */
    if (id != Gyroscope)
        return 0;

    if (!mEnabled[id])
        return 0;

    int ms = ns / 1000000;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", ms);
    int ret = write_sys_attribute(L3G4200D_SYSFS_PATH "pollrate_ms", buf, sizeof(buf));
    if (ret)
        return ret;

    return 0;
}

bool GyroSensor::hasPendingEvents() const
{
    return mPendingMask;
}

int GyroSensor::readEvents(sensors_event_t* data, int count)
{
    if (count < 1) {
        return -EINVAL;
    }

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0) {
        return n;
    }

    int numEventReceived = 0;
    input_event const* event;

    while (count && mInputReader.readEvent(&event)) {
        int type = event->type;
        if (type == EV_ABS) {
            processEvent(event->code, event->value);
            mInputReader.next();
        } else if (type == EV_SYN) {
            int64_t time = timevalToNano(event->time);
            for (int j=0 ; count && mPendingMask && j<numSensors ; j++) {
                if (mPendingMask & (1<<j)) {
                    mPendingMask &= ~(1<<j);
                    mPendingEvents[j].timestamp = time;
                    if (mEnabled[j]) {
                        *data++ = mPendingEvents[j];
                        count--;
                        numEventReceived++;
                    }
                }
            }
            if (!mPendingMask) {
                mInputReader.next();
            }
        } else {
            ALOGE("GyroSensor: unknown event (type=%d, code=%d)",
                    type, event->code);
            mInputReader.next();
        }
    }
    return numEventReceived;
}

int GyroSensor::handle2id(int32_t handle)
{
    switch (handle) {
    case ID_G:
        return Gyroscope;
    case ID_T:
        return Temperature;
    default:
        ALOGE("GyroSensor: unknown handle (%d)", handle);
        return -EINVAL;
    }
}

void GyroSensor::processEvent(int code, int value)
{
    switch (code) {
    case EVENT_TYPE_GYRO_X:
        mPendingMask |= 1<<Gyroscope;
        mPendingEvents[Gyroscope].gyro.x = value * CONVERT_G;
        break;
    case EVENT_TYPE_GYRO_Y:
        mPendingMask |= 1<<Gyroscope;
        mPendingEvents[Gyroscope].gyro.y = value * CONVERT_G;
        break;
    case EVENT_TYPE_GYRO_Z:
        mPendingMask |= 1<<Gyroscope;
        mPendingEvents[Gyroscope].gyro.z = value * CONVERT_G;
        break;
    case EVENT_TYPE_TEMP:
        mPendingMask |= 1<<Temperature;
        mPendingEvents[Temperature].temperature = value;
        break;
    }
}
