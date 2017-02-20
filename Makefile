MCU = atmega2560
F_CPU = 16000000

export CXX = avr-g++
export OBJCOPY = avr-objcopy

export CXXFLAGS = -I. -std=c++11 -mmcu=$(MCU) -DF_CPU=$(F_CPU)L -Wall -pedantic -O2
export LDFLAGS = -mmcu=$(MCU)

all:
	$(MAKE) -C src/ all

clean:
	$(MAKE) -C src/ clean

.DEFAULT:
	$(MAKE) -C src/ $@
