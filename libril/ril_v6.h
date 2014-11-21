/*
 * Copyright (C) 2006 The Android Open Source Project
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

#ifndef ANDROID_RIL_V6_H
#define ANDROID_RIL_V6_H

typedef struct {
    char *aidPtr;   /* AID value, See ETSI 102.221 8.1 and 101.220 4, NULL if no value. */
    int command;    /* one of the commands listed for TS 27.007 +CRSM*/
    int fileid;     /* EF id */
    char *path;     /* "pathid" from TS 27.007 +CRSM command.
                       Path is in hex asciii format eg "7f205f70"
                       Path must always be provided.
                     */
    int p1;
    int p2;
    int p3;
    char *data;     /* May be NULL*/
    char *pin2;     /* May be NULL*/
} RIL_SIM_IO_v4;

#define RIL_REQUEST_IMS_REGISTRATION_STATE_V6 109
#define RIL_REQUEST_IMS_SEND_SMS_V6 110
#define RIL_REQUEST_GET_DATA_CALL_PROFILE_V6 111
#define RIL_REQUEST_SET_UICC_SUBSCRIPTION_V6  112
#define RIL_REQUEST_SET_DATA_SUBSCRIPTION_V6  113

#define RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED_V6 1036
#define RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED_V6 1037
#define RIL_UNSOL_RESPONSE_DATA_NETWORK_STATE_CHANGED_V6 1038
#define RIL_UNSOL_ON_SS_V6 1039
#define RIL_UNSOL_STK_CC_ALPHA_NOTIFY_V6 1040
#define RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED_V6 1041

#endif /* ANDROID_RIL_V6_H */
