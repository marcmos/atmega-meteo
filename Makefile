CC = avr-gcc
OBJCOPY = avr-objcopy

MCU = atmega2560
F_CPU = 16000000

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)L -Wall -O2
LDFLAGS = -mmcu=$(MCU)

MAIN = atmega-meteo
SRCS = hd44780.c lcd.c uart.c blink.c $(MAIN).c

OBJS = $(SRCS:.c=.o)

all: $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(MAIN)
	$(OBJCOPY) -O ihex $(MAIN) $(MAIN).hex

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(MAIN) $(MAIN).hex
