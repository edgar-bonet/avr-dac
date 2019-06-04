# Makefile for building and uploading avr-dac.
#
# Set the variables below to match you hardware, then type
#
#     make
#     make upload

MCU           = attiny13a
AVRDUDE_FLAGS = -p attiny13 -c usbasp

avr-dac.elf: avr-dac.S
	avr-gcc -mmcu=$(MCU) -nostdlib $< -o $@

upload: avr-dac.elf
	avrdude $(AVRDUDE_FLAGS) -e -U $<

clean:
	rm -f avr-dac.elf

.PHONY: upload clean
