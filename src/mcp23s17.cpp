#include "mcp23s17.h"

// Initialize GPIO pins for chip select
void mcp23s17_init_gpio(uint8_t pins[]) {
	uint pin_count = sizeof(pins) / sizeof(uint8_t);
	for (uint i = 0; i < pin_count; i++) {
		uint8_t pin = pins[i];
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);
		gpio_put(pin, true);         // set to high, as chip select is active low
	}
}

// todo(mathias): implement polarity and mirroring
void mcp23s17_init(spi_inst_t* spi_inst, uint8_t pin) {
	uint8_t iocon = 0x00;
	mcp23s17_write_byte(spi_inst, pin, MCP23s17_IOCON, iocon);
}

/// Read byte from device on [pin] from [_register], set result to [value]
int mcp23s17_read_byte(spi_inst_t* spi_inst, uint8_t pin, uint8_t _register, uint8_t *value) {
	uint8_t command[] = {0x41, _register};    // opcode, register
	gpio_put(pin, false);                     // select chip, active low
	spi_write_blocking(spi_inst, command, 2); // write what register to read
	spi_read_blocking(spi_inst, 0, value, 1); // read one byte to &value
	gpio_put(pin, true);                      // deselect pin, active low
	return PICO_OK;
}

/// Write [value] to device on [pin] to [_register]
int mcp23s17_write_byte(spi_inst_t* spi_inst, uint8_t pin, uint8_t _register, uint8_t value) {
	uint8_t command[] = { 0x40, _register, value }; // opcode, register, value
	gpio_put(pin, false);                           // select chip, active low
	spi_write_blocking(spi_inst, command, 3);       // write three bytes
	gpio_put(pin, true);                            // deselect pin, active low
	return PICO_OK;
}

/// Read two bytes from device on [pin], set result to [value]
int mcp23s17_read_word(spi_inst_t* spi_inst, uint8_t pin, uint8_t low_register, uint8_t high_register, uint16_t &value) {
	uint8_t low_byte = 0;
	uint8_t high_byte = 0;
	mcp23s17_read_byte(spi_inst, pin, low_register, &low_byte);    // read low byte
	mcp23s17_read_byte(spi_inst, pin, high_register, &high_byte);  // read high byte
	value = (high_byte << 8) + low_byte;                           //shift high byte 8 bits to the left
	return PICO_OK;
}
