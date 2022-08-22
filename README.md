# pico-mcp23s17
Raspberry Pi library to communicate with MCP23S17 16-bit I/O expander

## Usage
```cpp
#include "mcp23s17.h"

uint8_t PIN_DATA_PORT = 20;
uint8_t PIN_SPI_CLK = 18;
uint8_t PIN_SPI_MOSI = 19;
uint8_t PIN_SPI_MISO = 16;

int main() {
  stdio_init_all();
  // init spi with max speed of the mcp23s17
	spi_init(SPI_PORT, MCP23S17_MAX_SPEED);

  // init the gpio pin for data port by setting it high
	mcp23s17_init_gpio(new uint8_t[1]{PIN_DATA_PORT});

	gpio_set_function(PIN_SPI_MISO, GPIO_FUNC_SPI);
	gpio_set_function(PIN_SPI_CLK, GPIO_FUNC_SPI);
	gpio_set_function(PIN_SPI_MOSI, GPIO_FUNC_SPI);

  // init port by configuring IOCON register
	mcp23s17_init(SPI_PORT, PIN_DATA_PORT);
  
  // configure register A for output
	mcp23s17_write_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_IODIR_A, MCP23S17_IODIR_OUTPUT);
  
  // configure register B for input
	mcp23s17_write_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_IODIR_B, MCP23S17_IODIR_INPUT);
  
  // configure register B to enable pull ups and inverted polarity to reduce noise
	mcp23s17_write_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_PULLUP_B, MCP23S17_PULLUP_ENABLE);
	mcp23s17_write_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_POLARITY_B, MCP23S17_POLARITY_INVERTED);

	while (true) {
    // write out 1 bit on register A, being shifted to the left 8 times
		for (int i = 0; i < 8; i++) {
			uint8_t out_data = 0x01 << i;
			mcp23s17_write_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_GPIO_A, out_data);
      sleep_ms(100);
    }
    
    // read data from register B
    uint8_t in_data;
    mcp23s17_read_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_GPIO_B, &in_data);
    printf("read %d\n", in_data); // these bits are inverted, so 255 is default
    sleep_ms(100);
	}
}
```
