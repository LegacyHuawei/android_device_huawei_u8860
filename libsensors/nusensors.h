/*
 * Copyright (C) 2012 The Android Open-Source Project
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

#ifndef ANDROID_SENSORS_H
#define ANDROID_SENSORS_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <math.h>

#include <linux/input.h>

#include <hardware/hardware.h>
#include <hardware/sensors.h>

__BEGIN_DECLS

/*****************************************************************************/

int init_nusensors(hw_module_t const* module, hw_device_t** device);

/*****************************************************************************/

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define ID_A  (0)
#define ID_M  (1)
#define ID_O  (2)
#define ID_R  (3)
#define ID_P  (4)
#define ID_L  (5)
#define ID_G  (6)
#define ID_T  (7)

/*****************************************************************************/

/*
 * The SENSORS Module
 */

/*****************************************************************************/

/* For Accelerometer */
#define EVENT_TYPE_ACCEL_X          ABS_X
#define EVENT_TYPE_ACCEL_Y          ABS_Y
#define EVENT_TYPE_ACCEL_Z          ABS_Z
#define EVENT_TYPE_ACCEL_STATUS     ABS_WHEEL

/* For Magnetometer */
#define EVENT_TYPE_MAGV_X           ABS_RY
#define EVENT_TYPE_MAGV_Y           ABS_RZ
#define EVENT_TYPE_MAGV_Z           ABS_THROTTLE
#define EVENT_TYPE_MAGV_STATUS      ABS_RUDDER

/* Fusion Orientation */
#define EVENT_TYPE_YAW              ABS_HAT0Y
#define EVENT_TYPE_PITCH            ABS_HAT1X
#define EVENT_TYPE_ROLL             ABS_HAT1Y

/* Fusion Rotation Vector */
#define EVENT_TYPE_ROTVEC_X         ABS_TILT_X
#define EVENT_TYPE_ROTVEC_Y         ABS_TILT_Y
#define EVENT_TYPE_ROTVEC_Z         ABS_TOOL_WIDTH
#define EVENT_TYPE_ROTVEC_W         ABS_VOLUME

/* For Proximity */
#define EVENT_TYPE_PROXIMITY        ABS_DISTANCE

/* For Light */
#define EVENT_TYPE_LIGHT            ABS_MISC

/* For Gyroscope*/
#define EVENT_TYPE_GYRO_X           ABS_X
#define EVENT_TYPE_GYRO_Y           ABS_Y
#define EVENT_TYPE_GYRO_Z           ABS_Z

/* For Temperature */
#define EVENT_TYPE_TEMP             ABS_MISC

// 1024 LSG = 1G
#define LSG                         (1024.0f)
#define MAX_RANGE_A                 (2*GRAVITY_EARTH)
// conversion of acceleration data to SI units (m/s^2)
#define CONVERT_A                   (GRAVITY_EARTH / LSG)

// conversion of magnetic data to uT units
#define CONVERT_M                   (0.06f)

// conversion of orientation data (Q6) to degree units
#define CONVERT_O                   (1.0f / 64.0f)

// conversion of rotation vector (Q14) data to float
#define CONVERT_R                   (1.0f / 16384.0f)

#define MAX_RANGE_G                 (2000.0f * ((float)(M_PI/180.0f)))
 // conversion of angular velocity(millidegrees/second) to rad/s
#define CONVERT_G                   ((70.0f/1000.0f) * ((float)(M_PI/180.0f)))

#define SENSOR_STATE_MASK           (0x7FFF)

/*****************************************************************************/

__END_DECLS

#endif  // ANDROID_SENSORS_H
