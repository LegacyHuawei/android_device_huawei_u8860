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

#ifndef ANDROID_ACCEL_SENSOR_H
#define ANDROID_ACCEL_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "nusensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

/*****************************************************************************/
#define LIS3DH_NAME         "lis3dh_acc"
#define LIS3DH_SYSFS_PATH   "/sys/bus/i2c/devices/0-0018/"
/*****************************************************************************/

struct input_event;

class AccelSensor : public SensorBase {
private:
    InputEventCircularReader mInputReader;
    bool mEnabled;
    bool mHasPendingEvent;
    sensors_event_t mPendingEvent;

public:
            AccelSensor();
    virtual ~AccelSensor();
    virtual int setEnable(int32_t handle, int enabled);
    virtual int setDelay(int32_t handle, int64_t ns);
    virtual bool hasPendingEvents() const;
    virtual int readEvents(sensors_event_t* data, int count);
};

/*****************************************************************************/

#endif  // ANDROID_ACCEL_SENSOR_H
