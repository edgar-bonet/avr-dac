# Makefile for building the test sketch without the Arduino IDE.
#
# This requires the generic Arduino Makefile by Sudar Muthu:
#     https://github.com/sudar/Arduino-Makefile
# On Ubuntu, install it by typing
#
#     sudo apt-get install arduino-mk
#
# To build, type
#
#     make
#
# To upload, type
#
#     make upload

# Set this to match the board you are using.
BOARD_TAG     = uno

# Serial port connected to the Arduino.
MONITOR_PORT  = /dev/ttyACM0

# Rise the warning level.
CXXFLAGS     += -Wextra

# Avoid being overly verbose.
ARDUINO_QUIET = 1

# Include the generic Arduino Makefile.
include /usr/share/arduino/Arduino.mk
