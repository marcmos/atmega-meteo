#include "lcd/lcd.h"
#include "serial/uart.h"
#include "blink.h"

FILE uart_str;
FILE lcd_str;

static void ioinit(void) {
  lcd_init();
  uart_init();
  blink_init();
}

int main(void) {
  ioinit();

  fdev_setup_stream(&uart_str, uart_putchar, uart_getchar, _FDEV_SETUP_RW);
  fdev_setup_stream(&lcd_str, lcd_putchar, NULL, _FDEV_SETUP_WRITE);

  stdout = stdin = &uart_str;
  stderr = &lcd_str;

  while(1) {
    char c = getchar();
    lcd_putchar(c, NULL);
  }

  return 0;
}
