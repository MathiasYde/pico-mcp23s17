#ifndef PICO_MCP23S17_H
#define PICO_MCP23S17_H

#include "hardware/spi.h"
#include "hardware/gpio.h"

// using IOCON.BANK=0
#define MCP23S17_GPIO_A 0x12
#define MCP23S17_GPIO_B 0x13
#define MCP23S17_IODIR_A 0x00
#define MCP23S17_IODIR_B 0x01
#define MCP23S17_PULLUP_A 0x0c
#define MCP23S17_PULLUP_B 0x0d
#define MCP23S17_POLARITY_A 0x02
#define MCP23S17_POLARITY_B 0x03
#define MCP23s17_IOCON 0x0a

#define MCP23S17_MAX_SPEED 10000000

#define MCP23S17_IODIR_INPUT 0xff
#define MCP23S17_IODIR_OUTPUT 0x00
#define MCP23S17_PULLUP_ENABLE 0xff
#define MCP23S17_PULLUP_DISABLE 0x00
#define MCP23S17_POLARITY_NORMAL 0x00
#define MCP23S17_POLARITY_INVERTED 0xff

// Initialize GPIO pins for chip select
void mcp23s17_init_gpio(uint8_t pins[]);

void mcp23s17_init(spi_inst_t* spi_inst, uint8_t pin);

/// Read byte from device on [pin] from [reg], set result to [value]
int mcp23s17_read_byte(spi_inst_t* spi_inst, uint8_t pin, uint8_t reg, uint8_t *value);

/// Read two bytes from device on [pin]
int mcp23s17_read_word(spi_inst_t* spi_inst, uint8_t pin, uint8_t low_register, uint8_t high_register, uint16_t *value);

int mcp23s17_write_byte(spi_inst_t* spi_inst, uint8_t pin, uint8_t _register, uint8_t value);

int mcp23s17_set_io_direction(spi_inst_t* spi_inst, uint8_t pin, uint8_t _register, uint8_t mask);

#endif // PICO_MCP23S17_H