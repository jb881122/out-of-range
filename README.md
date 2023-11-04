# OutOfRange

This repository contains a tool that can be used to exploit a vulnerability in some bootloaders of Samsung phones from around 2013, in order to boot custom operating systems.

## What to Expect

**WARNING:** While this is unlikely to permanently brick your phone, it may still cause it to be in an unbootable state. In either case, I disclaim all responsibility. By using this tool, I assume you know what you are doing.

Given a bootloader image and a custom boot or recovery image, this tool will output a modified image that can be used on a phone with that specific bootloader. This is similar to what the [Loki tool](https://github.com/djrbliss/loki) does.

There is also a second mode where an image can be created redirecting the bootloader to boot from a different partition. This can be helpful for booting larger images that don't fit within the appropriate partition.

Quirks / Things to keep in mind:

- You will not be able to flash these modified images in Odin, as the bootloader is still locked. To flash them, use `dd` as root.
- The modified images are several hundred kilobytes larger than the original images, since the bootloader code needs to be bundled with the images. If an output image would be too large to flash, the program will error out. To work around this, you can find an unused partition, flash the original image there, and use this tool in redirection mode to boot from that partition.

## How to Use

Either Linux or Windows can be used here.

Prerequisites:

- A supported aboot image from your device
- A boot image to modify (except for redirection mode)

Steps:

- Download the appropriate ZIP file from the [releases page](https://github.com/jb881122/out-of-range/releases)
- Extract the `oor` binary file
- Go to that directory in a command-line shell
- Run either `./oor -p <aboot image> <boot image> <output file>` or `./oor -r <aboot image> <partition name> <output file>` (removing the `./` if running in a cmd.exe shell and replacing the arguments as appropriate)
- If it worked, you should have a new image you can flash. Otherwise, an error will be printed on the screen.

## How to Compile

It is best to do this in Linux, because I have not tested any of this on Windows.

Prerequisites:
- `arm-linux-androideabi-gcc` and `arm-linux-androideabi-objcopy` (the NDK provides these; I used GCC 4.8)
- `gcc` and `strip` for your host and target platforms
- `make`
- `git` (only if you plan on cloning this repository)

Steps:
- Clone or otherwise get the repository's files into a directory.
- Go to that directory
- Set `$HOST_CC`, `$TARGET_CC`, and `$ARM_CC` to the appropriate compilers if you need something other than the default values
- Other variables that can be set for different configurations: `$TARGET_STRIP`, `$ARM_OBJCOPY`, `$TARGET_SUFFIX`, `$HOST_CFLAGS`, `$TARGET_CFLAGS`, and `$ARM_CFLAGS`
- Run `make`

If it came together correctly, the `oor` tool should be found in the `bin/` folder.

## Adding Support for Another Bootloader

The file `src/config.c` contains the configurations for all of the bootloaders supported by this tool. To add support for a bootloader, add another configuration to this list, using one of the existing configurations as a template.

The `src/config.h` file has comments describing each value and how it is obtained. This will require some extensive disassembly of the bootloader in question, for which information can be found on [this article](https://newandroidbook.com/Articles/aboot.html).

Once the configuration is added, compile and test the tool to make sure it works for your device and submit a pull request.

## Room for Improvement

- Adding configurations for more bootloaders and devices
- Allowing this to be built within an Android build environment, so that custom ROMs can be made with this tool integrated

## Licensing

The contents of this repository are hereby released into the public domain.
