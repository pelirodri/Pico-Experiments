add_library(passivebuzzer STATIC)

target_sources(
	passivebuzzer
	PRIVATE src/passive_buzzer.c src/utils/pwm.c
	PUBLIC FILE_SET HEADERS
	BASE_DIRS include
	FILES include/passivebuzzer/passive_buzzer.h
)

target_include_directories(passivebuzzer PRIVATE include/passivebuzzer)
target_link_libraries(passivebuzzer PUBLIC pico_stdlib hardware_pwm hardware_clocks)
