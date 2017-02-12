CXX = avr-g++
OBJCOPY = avr-objcopy

MCU = atmega2560
F_CPU = 16000000

CXXFLAGS = -I. -std=c++11 -mmcu=$(MCU) -DF_CPU=$(F_CPU)L -Wall -O2
LDFLAGS = -mmcu=$(MCU)

MAIN = atmega-meteo
SRCS = lcd/hd44780.cpp lcd/lcd.cpp serial/uart.cpp blink.cpp $(MAIN).cpp

OBJS = $(SRCS:.cpp=.o)

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(MAIN)
	$(OBJCOPY) -O ihex $(MAIN) $(MAIN).hex

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(MAIN) $(MAIN).hex
