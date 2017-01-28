#include "lcd.h"
#include "uart.h"
#include "blink.h"

FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

static void ioinit(void) {
  lcd_init();
  uart_init();
  blink_init();
}

int main(void) {
  ioinit();

  stdout = stdin = &uart_str;
  stderr = &lcd_str;

  while(1) {
    char c = getchar();
    lcd_putchar(c, NULL);
  }

  return 0;
}
