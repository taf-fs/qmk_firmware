#!/bin/sh

avrdude -c usbasp -p m32u4 -U flash:w:util/bootloader_atmega32u4_1.0.0.hex:a -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m
