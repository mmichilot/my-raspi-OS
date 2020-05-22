# myRaspiOS

A custom Raspberry Pi OS that I'm slowly making.  Mainly just for me to learn about OSes. Based off the tutorial from https://jsandler18.github.io/. Highly recommend checking it out if you want to learn about OSes and build your own OS for the Raspberry Pi.

# Current Progress

Currently it just builds for either QEMU or Raspberry Pi 2.

UART works fine, just connect to pin 14 (TXD) and pin 15 (RXD). Default UART settings are: 115000 baud, no parity, 8 bits, and 1 stop bit.

Some basic library functions, mainly just to make writing and reading from UART a lot easier.

# Future Goals

Get memory management working

Use the Raspberry Pi's framebuffer to output to a display

Get peripherals like USB working

and so much more...

# Building on Linux

Go into the **build** directory:

```bash
# cd ./build
```

Download the ARM toolchain (can be found here: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). 

Extract the file:

```bash
# tar -xf file_you_just_downloaded
```

Since we are building for an ARM system and not x86, we need tools (gcc, objcopy, objdump, etc...) specifically to build for ARM.


## Building for QEMU

Ensure that you have QEMU installed. Specifically *qemu-system-arm* as that emulates ARM processors.

If you don't, then assuming you are running Ubuntu/Debian, just run:

```bash
# sudo apt install qemu-system-arm
```

Once you have QEMU installed, just run:

```bash
# make run
```

This will build the kernel image, then boot the kernel image using QEMU. 

If you just want to build the kernel image and use a custom QEMU command, then run:
 
```bash
# make build
```

This is will provide a **kernel.img** that you can use with QEMU

## Building for Raspberry Pi 2

You are going to need a physical Raspberry Pi 2!

First grab Raspbian and load it onto your SD card. There are a bunch of tutorials explaining how to do this so I won't be
going into details here. If Raspbian successfully boots, then the SD card is ready. All you have to do now is just replace
the existing **kernel7.img** that Raspbian uses with your own kernel image that you built.

To build the kernel image:

```bash
# RASPI_MODEL=2 make build
```

To have the Raspberry Pi boot your kernel image, replace the **kernel7.img** on the SD card with the **kernel7.img** you just built.
