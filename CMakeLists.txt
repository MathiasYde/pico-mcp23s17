add_library(pico_mcp23s17 INTERFACE)

target_sources(
	pico_mcp23s17
	INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/src/mcp23s17.cpp
)

target_include_directories(pico_mcp23s17 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(pico_mcp23s17 INTERFACE pico_stdlib hardware_gpio)