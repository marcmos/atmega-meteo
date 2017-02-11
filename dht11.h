#ifndef _DHT11_H
#define _DHT11_H

#include <stdint.h>
#include <stdbool.h>

void dht11_init();
bool dht11_read(uint8_t *data);

#endif
