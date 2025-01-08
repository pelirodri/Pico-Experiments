#include "pwm.h"

#include <math.h>
#include <hardware/pwm.h>
#include <hardware/clocks.h>

// https://www.i-programmer.info/programming/hardware/14849-the-pico-in-c-basic-pwm.html
void pwm_configure_gpio_pin(uint gpio_pin, uint32_t freq, float volume) {
	uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

	const uint32_t sys_clock_freq = clock_get_hz(clk_sys);

	float divider = fmax(ceil((double)sys_clock_freq / (4096 * freq)), 1);
	uint16_t wrap = ((sys_clock_freq / divider) / (freq * 2)) - 1; // Double the frequency because of phase correction.
	uint16_t level = ((0.5 * volume) / 100) * wrap; // Max volume is half the period (50% duty cycle).

	pwm_config config = pwm_get_default_config();

	pwm_config_set_clkdiv(&config, divider);
	pwm_config_set_wrap(&config, wrap);
	pwm_config_set_phase_correct(&config, true);

	pwm_init(slice_num, &config, false);

	pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio_pin), level);
}

void pwm_start(uint gpio_pin) {
	pwm_set_enabled(pwm_gpio_to_slice_num(gpio_pin), true);
}

void pwm_stop(uint gpio_pin) {
	pwm_set_enabled(pwm_gpio_to_slice_num(gpio_pin), false);
}
