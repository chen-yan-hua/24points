LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := getCards
LOCAL_SRC_FILES := getCards.c
include $(BUILD_SHARED_LIBRARY)
