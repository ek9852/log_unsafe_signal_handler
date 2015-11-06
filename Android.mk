LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cc

# Set up the target identity
LOCAL_MODULE := log_unsafe

LOCAL_SRC_FILES := \
  main.cc

LOCAL_CFLAGS += \
  -Wno-endif-labels \
  -Wno-import \
  -Wno-format \

#LOCAL_C_INCLUDES += $(LOCAL_PATH) external/jpeg

#LOCAL_SHARED_LIBRARIES := libjpeg libstlport libf2fs_sparseblock
LOCAL_SHARED_LIBRARIES := libcutils

include $(BUILD_EXECUTABLE)
