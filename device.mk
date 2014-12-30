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

# Include proprietary
$(call inherit-product, vendor/huawei/u8860/u8860-vendor.mk)

# Include common
$(call inherit-product, device/huawei/msm7x30-common/msm7x30.mk)

# Include broadcom firmware
$(call inherit-product-if-exists, hardware/broadcom/wlan/bcmdhd/firmware/bcm4329/device-bcm.mk)

# Include keyboards
$(call inherit-product, device/huawei/u8860/keyboards/keyboards.mk)

DEVICE_PACKAGE_OVERLAYS += device/huawei/u8860/overlay

# Hardware-specific features
PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
	frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml

# Init scripts
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/init.target.rc:root/init.target.rc

# Additional packages
PRODUCT_PACKAGES += \
	libnetcmdiface

# HAL
PRODUCT_PACKAGES += \
	sensors.u8860 \
	akmdfs

# RIL
PRODUCT_PROPERTY_OVERRIDES += \
	ro.telephony.call_ring.multiple=false \
	rild.libpath=/system/lib/libril-qc-1.so \
	rild.libargs=-d/dev/smd0

# Recovery
PRODUCT_PROPERTY_OVERRIDES += \
	ro.cwm.forbid_format=/boot,/recovery,/cust
