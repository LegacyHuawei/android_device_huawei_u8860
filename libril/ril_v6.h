/*
 * Copyright (C) 2006,2011 The Android Open Source Project
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

typedef struct {
    char *aidPtr;   /* null terminated string, e.g., from 0xA0, 0x00
                       0x41, 0x30. null for card files (outside the ADF)*/
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

/**
 * RIL_REQUEST_IMS_REGISTRATION_STATE
 *
 * Request current IMS registration state
 *
 * "data" is NULL
 *
 * "response" is int *
 * ((int *)response)[0] is == 0 for IMS not registered
 * ((int *)response)[0] is == 1 for IMS registered
 *
 * If ((int*)response)[0] is = 1, then ((int *) response)[1]
 * must follow with IMS SMS encoding:
 *
 * ((int *) response)[1] is of type const RIL_RadioTechnologyFamily
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_IMS_REGISTRATION_STATE_V6 109

/**
 * RIL_REQUEST_IMS_SEND_SMS
 *
 * Send a SMS message over IMS
 *
 * "data" is const RIL_IMS_SMS_Message *
 *
 * "response" is a const RIL_SMS_Response *
 *
 * Based on the return error, caller decides to resend if sending sms
 * fails.
 * SUCCESS is error class 0 (no error)
 * SMS_SEND_FAIL_RETRY will cause re-send with data encoded
 *   based on Voice Technology available.
 * and GENERIC_FAILURE means no retry.
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  SMS_SEND_FAIL_RETRY
 *  FDN_CHECK_FAILURE
 *  GENERIC_FAILURE
 *
 */
#define RIL_REQUEST_IMS_SEND_SMS_V6 110

/**
 * RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED
 *
 * Called when data network states has changed
 *
 * Callee will invoke the following requests on main thread:
 *
 * RIL_REQUEST_IMS_REGISTRATION_STATE
  *
 * "data" is NULL
 *
 */
#define RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED_V6 1036


/**
 * RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED
 *
 * Called when tethered mode is enabled or disabled
 *
 *
 * "data" is an int 0 - tethered mode off, 1 - tethered mode on
 *
 */
#define RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED_V6 1037

/**
 * RIL_UNSOL_RESPONSE_DATA_NETWORK_STATE_CHANGED
 *
 * Called when data network states has changed
  *
 * Callee will invoke the following requests on main thread:
 *
 * RIL_REQUEST_DATA_REGISTRATION_STATE
  *
 * "data" is NULL
 *
 */
#define RIL_UNSOL_RESPONSE_DATA_NETWORK_STATE_CHANGED_V6 1038

/**
 * RIL_UNSOL_ON_SS
 *
 * Called when SS response is received when DIAL/USSD/SS is changed to SS by
 * call control.
 *
 * "data" is const RIL_StkCcUnsolSsResponse *
 *
 */
#define RIL_UNSOL_ON_SS_V6 1039

/**
 * RIL_UNSOL_STK_CC_ALPHA_NOTIFY
 *
 * Called when there is an ALPHA from UICC during Call Control.
 *
 * "data" is const char * containing ALPHA string from UICC in UTF-8 format.
 *
 */
#define RIL_UNSOL_STK_CC_ALPHA_NOTIFY_V6 1040

/**
 * RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED
 *
 * Called when there is a change in subscription status.
 * This event will be sent in the following scenarios
 *  - subscription readiness at modem, which was selected by telephony layer
 *  - when subscription is deactivated by modem due to UICC card removal
 *
 * "data" is const int *
 * ((const int *)data)[0] == 0 for Subscription Deactivated
 * ((const int *)data)[0] == 1 for Subscription Activated
 *
 */
#define RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED_V6 1041

/**
 * RIL_UNSOL_QOS_STATE_CHANGED_IND
 *
 * Indication for any change in the QoS state of a particular QoS flow
 *
 * "data" is an char **
 * ((char **)data)[0] - QoS ID
 * ((char **)data)[1] - Status from RIL_QosIndStates
 *
 */
#define RIL_UNSOL_QOS_STATE_CHANGED_IND_V6 1042
