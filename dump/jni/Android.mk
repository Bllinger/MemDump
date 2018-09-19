LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := dump.c
#LOCAL_C_INCLUDES := /$(JNI_H_INCLUDE)
#LOCAL_SHARED_LIBRARIES := libutils    
#LOCAL_PRELINK_MODULE := false
LOCAL_LDLIBS := -L . -llog -lutils
LOCAL_MODULE := dump
include $(BUILD_SHARED_LIBRARY)