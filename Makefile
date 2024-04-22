HOST_CC ?= gcc
TARGET_CC ?= gcc
TARGET_STRIP ?= $(TARGET_CC:%gcc=%)strip
ARM_CC ?= arm-linux-androideabi-gcc
ARM_OBJCOPY ?= $(ARM_CC:%gcc=%)objcopy

OOR_MODULES := aboot_image asm boot_image cmd_crc cmd_list cmd_patch cmd_redirect \
		cmd_undo cmd_verify config crc file_utils little_endian main
ASM_MODULES := patch_code
BIN_TO_C_MODULES := bin_to_c file_utils

OOR_OBJS := $(addsuffix .o,$(addprefix obj-target/,$(OOR_MODULES)))
ASM_GEN := $(addsuffix .c,$(addprefix gen/,$(ASM_MODULES)))
BIN_TO_C_OBJS := $(addsuffix .o,$(addprefix obj-host/,$(BIN_TO_C_MODULES)))

all: bin/oor$(TARGET_SUFFIX)

bin/oor$(TARGET_SUFFIX): $(OOR_OBJS) $(ASM_GEN) | bin
	$(TARGET_CC) $(TARGET_CFLAGS) -o $@ $(OOR_OBJS) $(ASM_GEN)
	$(TARGET_STRIP) $@

bin:
	mkdir -p $@

obj-target/%.o: src/%.c src/*.h | obj-target
	$(TARGET_CC) $(TARGET_CFLAGS) -std=c99 -c -o $@ $<

obj-target:
	mkdir -p $@

gen/%.c: obj-arm/%.bin tools/bin_to_c | gen
	./tools/bin_to_c $< $(@:gen/%.c=%) $@

gen:
	mkdir -p $@

obj-arm/%.bin: obj-arm/%.o | obj-arm
	$(ARM_OBJCOPY) -O binary $< $@

obj-arm/%.o: src/%.S src/*.h | obj-arm
	$(ARM_CC) $(ARM_CFLAGS) -c -o $@ $<

obj-arm:
	mkdir -p $@

tools/bin_to_c: $(BIN_TO_C_OBJS) | tools
	$(HOST_CC) $(HOST_CFLAGS) -o $@ $(BIN_TO_C_OBJS)

tools:
	mkdir -p $@

obj-host/%.o: src/%.c src/*.h | obj-host
	$(HOST_CC) $(HOST_CFLAGS) -std=c99 -c -o $@ $<

obj-host:
	mkdir -p $@

clean:
	-rm -rf bin obj-target gen obj-arm tools obj-host

.PHONY: all clean
.PRECIOUS: obj-arm/%.o obj-arm/%.bin
