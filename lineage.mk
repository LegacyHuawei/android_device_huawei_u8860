#
# Copyright (C) 2012 The Android Open-Source Project
# Copyright (C) 2014 Rudolf Tammekivi <rtammekivi@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Boot animation
TARGET_SCREEN_HEIGHT := 854
TARGET_SCREEN_WIDTH := 480

# Custom tag for unofficial builds
TARGET_UNOFFICIAL_BUILD_ID := LegacyHuawei

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/huawei/u8860/full_u8860.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := u8860
PRODUCT_NAME := lineage_u8860
PRODUCT_MODEL := Honor
PRODUCT_BRAND := Huawei
PRODUCT_MANUFACTURER := Huawei
