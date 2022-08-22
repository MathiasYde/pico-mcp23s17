# pico-mcp23s17
Raspberry Pi library to communicate with MCP23S17 16-bit I/O expander

## Limitations
While this library is fairly barebones, it still provides the barebone code to communicate with the MCP23S17 chip.
It's enough for my personal needs for another project, others are welcome to contribute with furthur revisions that could implement more advanced features such as interrupts.

## Usage
Add this repository as a submodule
```bash
git submodule add https://github.com/MathiasYde/pico-mcp23s17
```
Include it in your project's CMakeLists.txt
```CMakeLists.txt
add_subdirectory(pico-mcp23s17)

target_link_libraries( ... pico_mcp23s17)
```

Example code
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
  
  	// configure register B to enable pull ups to reduce noise
	mcp23s17_write_byte(SPI_PORT, PIN_DATA_PORT, MCP23S17_PULLUP_B, MCP23S17_PULLUP_ENABLE);

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
  		 printf("read %d\n", in_data);
   		 sleep_ms(100);
	}
}
```

## License
See LICENSE file
