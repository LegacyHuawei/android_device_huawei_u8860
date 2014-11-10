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

#include <hardware/sensors.h>

#include "nusensors.h"

/*****************************************************************************/

/*
 * The SENSORS Module
 */

static const struct sensor_t sSensorList[] = {
    {
        .name       = "LIS3DH 3-axis Accelerometer",
        .vendor     = "ST Microelectronics",
        .version    = 1,
        .handle     = ID_A,
        .type       = SENSOR_TYPE_ACCELEROMETER,
        .maxRange   = MAX_RANGE_A,
        .resolution = CONVERT_A,
        .power      = 0.145f,
        .minDelay   = 10000,
        .reserved   = { }
    },
    {
        .name       = "AK8975 3-axis Magnetic field sensor",
        .vendor     = "Asahi Kasei Microdevices",
        .version    = 1,
        .handle     = ID_M,
        .type       = SENSOR_TYPE_MAGNETIC_FIELD,
        .maxRange   = 1228.8f,
        .resolution = CONVERT_M,
        .power      = 0.35f,
        .minDelay   = 10000,
        .reserved   = { }
    },
    {
        .name       = "AKM Orientation sensor",
        .vendor     = "Asahi Kasei Microdevices",
        .version    = 1,
        .handle     = ID_O,
        .type       = SENSOR_TYPE_ORIENTATION,
        .maxRange   = 360.0f,
        .resolution = CONVERT_O,
        .power      = 1.0f,
        .minDelay   = 10000,
        .reserved   = { }
    },
#if 0
    {
        .name       = "AKM Rotation vector sensor",
        .vendor     = "Asahi Kasei Microdevices",
        .version    = 1,
        .handle     = ID_R,
        .type       = SENSOR_TYPE_ROTATION_VECTOR,
        .maxRange   = 34.907f,
        .resolution = CONVERT_R,
        .power      = 1.0f,
        .minDelay   = 10000,
        .reserved   = { }
    },
#endif
    {
        .name       = "L3G4200D Gyroscope sensor",
        .vendor     = "ST Microelectronics",
        .version    = 1,
        .handle     = ID_G,
        .type       = SENSOR_TYPE_GYROSCOPE,
        .maxRange   = MAX_RANGE_G,
        .resolution = CONVERT_G,
        .power      = 6.1f,
        .minDelay   = 2000,
        .reserved   = { }
    },
    {
        .name       = "L3G4200D Temperature sensor",
        "ST Microelectronics",
        .version    = 1,
        .handle     = ID_T,
        .type       = SENSOR_TYPE_AMBIENT_TEMPERATURE,
        .maxRange   = 85,
        .resolution = 1,
        .power      = 6.1f,
        .minDelay   = 2000,
        .reserved   = { }
    },
    {
        .name       = "APDS-9900 Light sensor",
        .vendor     = "Avago Technologies",
        .version    = 1,
        .handle     = ID_L,
        .type       = SENSOR_TYPE_LIGHT,
        .maxRange   = 60000.0f,
        .resolution = 0.0125f,
        .power      = 0.20f,
        .minDelay   = 1000,
        .reserved   = { }
    },
    {
        .name       = "APDS-9900 Proximity sensor",
        .vendor     = "Avago Technologies",
        .version    = 1,
        .handle     = ID_P,
        .type       = SENSOR_TYPE_PROXIMITY,
        .maxRange   = 1.0f,
        .resolution = 1.0f,
        .power      = 3.0f,
        .minDelay   = 1000,
        .reserved   = { }
    },
};

static int open_sensors(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device);

static int sensors__get_sensors_list(struct sensors_module_t* module,
        struct sensor_t const** list)
{
    *list = sSensorList;
    return ARRAY_SIZE(sSensorList);
}

static struct hw_module_methods_t sensors_module_methods = {
    .open = open_sensors
};

struct sensors_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = SENSORS_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = SENSORS_HARDWARE_MODULE_ID,
        .name = "U8860 Sensors Module",
        .author = "The Android Open Source Project",
        .methods = &sensors_module_methods,
        .dso = 0,
        .reserved = { 0 },
    },
    .get_sensors_list = sensors__get_sensors_list,
};

/*****************************************************************************/

static int open_sensors(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device)
{
    return init_nusensors(module, device);
}
