#include "lcd.h"
#include "uart.h"
#include "dht11.h"
#include "blink.h"

#include <util/delay.h>

FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

static
void ioinit(void) {
  lcd_init();
  uart_init();
  dht11_init();
  blink_init();
}

static
void dht11_probe() {
  uint8_t data[5] = {0, 0, 0, 0, 0};
  dht11_read(data);
  printf("%u %u", data[0], data[2]);
}

int main(void) {

  ioinit();

  stdout = stdin = &uart_str;
  stderr = &lcd_str;

  while(1) {
    char c = getchar();
    switch(c) {
    // Triggers DHT11 sensor read
    case 0x11:
      dht11_probe();
      break;
    // Print non-special characters to LCD
    default:
      lcd_putchar(c, NULL);
      break;
    }
  }

  return 0;
}
