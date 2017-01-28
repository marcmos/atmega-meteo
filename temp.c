#include "lcd.h"
#include "blink.h"

int main(void) {
  lcd_init();
  blink_init();

  lcd_putchar('H', NULL);
  lcd_putchar('e', NULL);
  lcd_putchar('l', NULL);
  lcd_putchar('l', NULL);
  lcd_putchar('o', NULL);
  lcd_putchar('!', NULL);

  blink_loop();

  return 0;
}
