/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Stdio demo, upper layer of LCD driver.
 *
 * $Id: lcd.c 2265 2011-12-28 21:28:29Z joerg_wunsch $
 */

#include "../defines.hpp"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>

#include <util/delay.h>

#include "hd44780.hpp"
#include "lcd.hpp"

/*
 * Setup the LCD controller.  First, call the hardware initialization
 * function, then adjust the display attributes we want.
 */
void
lcd_init(void)
{

  hd44780_init();

  /*
   * Clear the display.
   */
  hd44780_outcmd(HD44780_CLR);
  hd44780_wait_ready(true);

  /*
   * Entry mode: auto-increment address counter, no display shift in
   * effect.
   */
  hd44780_outcmd(HD44780_ENTMODE(1, 0));
  hd44780_wait_ready(false);

  /*
   * Enable display.
   */
  hd44780_outcmd(HD44780_DISPCTL(1, 0, 0));
  hd44780_wait_ready(false);
}

/*
 * Send character c to the LCD display.  After a '\n' has been seen,
 * the next character will first clear the display.
 */
int
lcd_putchar(char c, FILE *unused)
{
  static int line;
  static bool nl_seen;

  if (c == '\n') {
    nl_seen = true;
    return 0;
  }
  if (nl_seen) {
    if (line == 0) {
      lcd_newline();
      line = 1;
    } else {
      /*
       * First character after newline, clear display and home cursor.
       */
      hd44780_wait_ready(false);
      hd44780_outcmd(HD44780_CLR);
      hd44780_wait_ready(false);
      hd44780_outcmd(HD44780_HOME);
      hd44780_wait_ready(true);
      hd44780_outcmd(HD44780_DDADDR(0));

      line = 0;
    }
    nl_seen = false;
  }

  hd44780_wait_ready(false);
  hd44780_outdata(c);

  return 0;
}

void lcd_newline() {
  hd44780_wait_ready(false);
  hd44780_outcmd(HD44780_DDADDR(0x40));
}

static
void lcd_setglyph(const uint8_t glyph[]) {
  int row;

  for(row = 0; row < 8; ++row) {
    hd44780_wait_ready(false);
    hd44780_outdata(glyph[row]);
  }

  hd44780_wait_ready(false);
}

void lcd_setglyphs(const uint8_t glyphs[][8], int count) {
  int glyph;

  hd44780_outcmd(HD44780_CGADDR(0));

  for(glyph = 0; glyph < count; ++glyph) {
    lcd_setglyph(glyphs[glyph]);
  }

  hd44780_outcmd(HD44780_HOME);
  hd44780_wait_ready(false);
}
