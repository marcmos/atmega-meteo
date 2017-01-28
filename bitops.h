/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Bit operation macros, derived from hd44780.c.
 */

#ifndef _BITOPS_H_
#define _BITOPS_H_

#define GLUE(a, b)     a##b

/* single-bit macros, used for control bits */
#define SET_(what, p, m) GLUE(what, p) |= (1 << (m))
#define CLR_(what, p, m) GLUE(what, p) &= ~(1 << (m))
#define TOGGLE_(what, p, m) GLUE(what, p) ^= (1 << (m))
#define GET_(/* PIN, */ p, m) GLUE(PIN, p) & (1 << (m))
#define SET(what, x) SET_(what, x)
#define CLR(what, x) CLR_(what, x)
#define TOGGLE(what, x) TOGGLE_(what, x)
#define GET(/* PIN, */ x) GET_(x)

#endif
