/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * General stdiodemo defines
 *
 * $Id: defines.h 2186 2010-09-22 10:25:15Z aboyapati $
 */
#include <avr/io.h>

/* UART baud rate */
#define UART_BAUD  9600

#define UBRRH UBRR0H
#define UBRRL UBRR0L
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UDR UDR0
#define UDRE UDRE0
#define TXEN TXEN0
#define RXEN RXEN0
#define RXC RXC0
#define FE FE0
#define DOR DOR0

/* HD44780 LCD port connections */
#define HD44780_RS B, 0
#define HD44780_RW B, 1
#define HD44780_E  B, 2
/* The data bits have to be not only in ascending order but also consecutive. */
#define HD44780_D C, 0

/* Whether to read the busy flag, or fall back to
   worst-time delays. */
#define USE_BUSY_BIT 1

/* Blink LED */
#define LED B, 7

/* DHT-11 Humidity & Temperature sensor */
#define DHT11 A, 0
