#include "HD44780.hpp"

#include <util/delay.h>

#include "../defines.hpp"
#include "../bitops.hpp"

/* macros, used for data path */
#define ASSIGN_(what, p, m, v) GLUE(what, p) = v
#define READ_(what, p, m) GLUE(what, p)
#define ASSIGN(what, x, v) ASSIGN_(what, x, v)
#define READ(what, x) READ_(what, x)

#define HD44780_BUSYFLAG 0x80

HD44780::HD44780() {
  init();
  reset();
}

void HD44780::init() {
  SET(DDR, HD44780_RS);
  SET(DDR, HD44780_RW);
  SET(DDR, HD44780_E);
  ASSIGN(DDR, HD44780_D, 0xff);

  _delay_ms(15);
  cmd_out(HD44780_FNSET(1, 0, 0));
  _delay_ms(4.1);
  cmd_out(HD44780_FNSET(1, 0, 0));
  _delay_ms(0.1);
  cmd_out(HD44780_FNSET(1, 0, 0));
  _delay_us(37);

  cmd_out(HD44780_FNSET(1, 1, 0));
  wait_ready(false);
}

void HD44780::reset() {
  /*
   * Clear the display.
   */
  cmd_out(HD44780_CLR);
  wait_ready(true);

  /*
   * Entry mode: auto-increment address counter, no display shift in
   * effect.
   */
  cmd_out(HD44780_ENTMODE(1, 0));
  wait_ready(false);

  /*
   * Enable display.
   */
  cmd_out(HD44780_DISPCTL(1, 0, 0));
  wait_ready(false);
}

void HD44780::print(const char *str) {
  while(*str++) putchar(*(str - 1));
}

uint8_t HD44780::byte_in(bool rs) {
  uint8_t x;

  SET(PORT, HD44780_RW);
  ASSIGN(DDR, HD44780_D, 0x00);
  if (rs)
    SET(PORT, HD44780_RS);
  else
    CLR(PORT, HD44780_RS);
  x = pulse(true);
  ASSIGN(DDR, HD44780_D, 0xff);
  CLR(PORT, HD44780_RW);

  return x;
}

void HD44780::byte_out(uint8_t b, bool rs) {
  CLR(PORT, HD44780_RW);
  if (rs)
    SET(PORT, HD44780_RS);
  else
    CLR(PORT, HD44780_RS);
  ASSIGN(PORT, HD44780_D, b);
  pulse(false);
}

uint8_t HD44780::cmd_in() {
  return byte_in(false);
}

void HD44780::cmd_out(uint8_t cmd) {
  byte_out(cmd, false);
}

uint8_t HD44780::data_in() {
  return byte_in(true);
}

void HD44780::data_out(uint8_t data) {
  byte_out(data, true);
}

uint8_t HD44780::pulse(bool readback) {
  uint8_t x;

  SET(PORT, HD44780_E);
  /*
   * Guarantee at least 500 ns of pulse width.  For high CPU
   * frequencies, a delay loop is used.  For lower frequencies, NOPs
   * are used, and at or below 1 MHz, the native pulse width will
   * already be 1 us or more so no additional delays are needed.
   */
#if F_CPU > 4000000UL
  _delay_us(0.5);
#else
  /*
   * When reading back, we need one additional NOP, as the value read
   * back from the input pin is sampled close to the beginning of a
   * CPU clock cycle, while the previous edge on the output pin is
   * generated towards the end of a CPU clock cycle.
   */
  if (readback)
    __asm__ volatile("nop");
#  if F_CPU > 1000000UL
  __asm__ volatile("nop");
#    if F_CPU > 2000000UL
  __asm__ volatile("nop");
  __asm__ volatile("nop");
#    endif /* F_CPU > 2000000UL */
#  endif /* F_CPU > 1000000UL */
#endif
  if (readback)
    x = READ(PIN, HD44780_D);
  else
    x = 0;
  CLR(PORT, HD44780_E);

  return x;
}

void HD44780::wait_ready(bool long_wait) {
#if USE_BUSY_BIT
  while (cmd_in() & HD44780_BUSYFLAG) ;
#else
  if (long_wait)
    _delay_ms(1.52);
  else
    _delay_us(37);
#endif
}

void HD44780::putchar(char c) {
  static int line;
  static bool nl_seen;

  if (c == '\n') {
    nl_seen = true;
    return;
  }
  if (nl_seen) {
    if (line == 0) {
      newline();
      line = 1;
    } else {
      /*
       * First character after newline, clear display and home cursor.
       */
      wait_ready(false);
      cmd_out(HD44780_CLR);
      wait_ready(false);
      cmd_out(HD44780_HOME);
      wait_ready(true);
      cmd_out(HD44780_DDADDR(0));

      line = 0;
    }
    nl_seen = false;
  }

  wait_ready(false);
  data_out(c);
}

void HD44780::newline() {
  wait_ready(false);
  cmd_out(HD44780_DDADDR(0x40));
}
