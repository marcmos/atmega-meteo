#include "lcd.h"
#include "uart.h"
#include "blink.h"

FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

const uint8_t glyphs[][8] = {
  { 0,    0,    0,    0x1f, 0x1f, 0x18, 0x18, 0x18 },
  { 0,    0x03, 0x03, 0x1f, 0x1f, 0x03, 0x03, 0x03 },
  { 0x1f, 0x1a, 0x1f, 0x1a, 0x1f, 0x1a, 0x1f, 0x1f },
  { 0x1f, 0x0b, 0x1f, 0x0b, 0x1f, 0x0b, 0x1f, 0x1f }
};

static void ioinit(void) {
  lcd_init();
  uart_init();
  blink_init();
}

int main(void) {
  ioinit();

  stdout = stdin = &uart_str;
  stderr = &lcd_str;

  lcd_setglyphs(glyphs, sizeof(glyphs) / sizeof(glyphs[0]));

  while(1) {
    char c = getchar();
    lcd_putchar(c, NULL);
  }

  return 0;
}
