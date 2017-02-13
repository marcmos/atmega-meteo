#include "LCD.hpp"

#include <stdint.h>

/* Clear LCD display command. */
#define HD44780_CLR \
	0x01

/* Home cursor command. */
#define HD44780_HOME \
	0x02

/*
 * Select the entry mode.  inc determines whether the address counter
 * auto-increments, shift selects an automatic display shift.
 */
#define HD44780_ENTMODE(inc, shift) \
	(0x04 | ((inc)? 0x02: 0) | ((shift)? 1: 0))

/*
 * Selects disp[lay] on/off, cursor on/off, cursor blink[ing]
 * on/off.
 */
#define HD44780_DISPCTL(disp, cursor, blink) \
	(0x08 | ((disp)? 0x04: 0) | ((cursor)? 0x02: 0) | ((blink)? 1: 0))

/*
 * With shift = 1, shift display right or left.
 * With shift = 0, move cursor right or left.
 */
#define HD44780_SHIFT(shift, right) \
	(0x10 | ((shift)? 0x08: 0) | ((right)? 0x04: 0))

/*
 * Function set.  if8bit selects an 8-bit data path, twoline arranges
 * for a two-line display, font5x10 selects the 5x10 dot font (5x8
 * dots if clear).
 */
#define HD44780_FNSET(if8bit, twoline, font5x10) \
	(0x20 | ((if8bit)? 0x10: 0) | ((twoline)? 0x08: 0) | \
		((font5x10)? 0x04: 0))

/*
 * Set the next character generator address to addr.
 */
#define HD44780_CGADDR(addr) \
	(0x40 | ((addr) & 0x3f))

/*
 * Set the next display address to addr.
 */
#define HD44780_DDADDR(addr) \
	(0x80 | ((addr) & 0x7f))

class HD44780 : public LCD {
public:
  HD44780();

  void init();
  void reset();

  void display(const char *str);

private:
  uint8_t byte_in(bool rs);
  void byte_out(uint8_t b, bool rs);

  uint8_t cmd_in();
  void cmd_out(uint8_t cmd);

  uint8_t data_in();
  void data_out(uint8_t data);

  uint8_t pulse(bool readback);
  void wait_ready(bool long_wait);

  void putchar(char c);
  void newline();
};
