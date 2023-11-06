LOCAL_PATH := $(call my-dir)



include $(CLEAR_VARS)

LOCAL_MODULE := bin_to_c
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -std=c99
LOCAL_SRC_FILES := src/bin_to_c.c src/file_utils.c
LOCAL_MODULE_CLASS := EXECUTABLES

include $(BUILD_HOST_EXECUTABLE)



include $(CLEAR_VARS)

LOCAL_MODULE := oor
LOCAL_MODULE_DEPENDS := bin_to_c
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/bin
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_STATIC_LIBRARIES := libc
LOCAL_FORCE_STATIC_EXECUTABLE := true

INTERMEDIATES := $(call local-intermediates-dir)

GEN := $(INTERMEDIATES)/gen/patch_code.c_gen
LOCAL_SRC_FILES := src/aboot_image.c src/boot_image.c src/cmd_patch.c src/cmd_verify.c \
		src/file_utils.c src/asm.c src/cmd_crc.c src/cmd_redirect.c src/config.c \
		src/little_endian.c src/cmd_list.c src/cmd_undo.c src/crc.c src/main.c
LOCAL_SRC_PATH := $(LOCAL_PATH)/src

$(GEN):
	mkdir -p $(dir $@)
	arm-linux-androideabi-gcc -c -o $(@:%.c_gen=%.o) $(LOCAL_SRC_PATH)/$(notdir $(@:%.c_gen=%.S))
	arm-linux-androideabi-objcopy -O binary $(@:%.c_gen=%.o) $(@:%.c_gen=%.bin)
	bin_to_c $(@:%.c_gen=%.bin) $(notdir $(@:%.c_gen=%)) $@

LOCAL_GENERATED_SOURCES += $(GEN)
LOCAL_C_INCLUDES := $(INTERMEDIATES)/gen
LOCAL_CFLAGS := -std=c99

include $(BUILD_EXECUTABLE)
