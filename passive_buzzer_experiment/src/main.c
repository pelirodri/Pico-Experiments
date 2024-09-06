#include "passive_buzzer_experiment.h"
#include "passivebuzzer/passive_buzzer.h"

#include <stdlib.h>
#include <hardware/gpio.h>
#include <pico/time.h>

static const uint passive_buzzer_gpio_pin = 15;
static const uint push_button_gpio_pin = 16;

static const passive_buzzer_t *passive_buzzer = NULL;
static volatile uint8_t button_pressed_history = 0;
static volatile bool should_play_melody = false;

static void set_up_button();
static bool button_check_callback(struct repeating_timer *);
static void update_button_pressed_history(bool);
static bool check_button_pressed_state();
static int check_for_should_play_melody();

int main() {
	passive_buzzer = passive_buzzer_create(passive_buzzer_gpio_pin);

	if (!passive_buzzer) {
		return 1;
	}

	set_up_button();

	struct repeating_timer timer;
	add_repeating_timer_ms(5, button_check_callback, NULL, &timer);
	
	int return_code = 0;

	while (true) {
		return_code = check_for_should_play_melody();

		if (return_code) {
			break;
		}		
	}

	free((passive_buzzer_t *)passive_buzzer);

	return return_code;
}

void set_up_button() {
	gpio_init(push_button_gpio_pin);
	gpio_set_dir(push_button_gpio_pin, GPIO_IN);
}

bool button_check_callback(struct repeating_timer *timer) {
	update_button_pressed_history(gpio_get(push_button_gpio_pin));

	if (!check_button_pressed_state()) {
		return true;
	}

	if (!passive_buzzer_is_playing(passive_buzzer)) {
		should_play_melody = true;
	} else {
		passive_buzzer_stop((passive_buzzer_t *)passive_buzzer);
		should_play_melody = false;
	}

	return true;
}

inline void update_button_pressed_history(bool button_pressed_state) {
	button_pressed_history = (button_pressed_history << 1) | button_pressed_state;
}

bool check_button_pressed_state() {
	if ((button_pressed_history & 0xC7) != 0x7) {
		return false;
	}

	button_pressed_history = 0xFF;

	return true;
}

int check_for_should_play_melody() {
	if (should_play_melody) {
		should_play_melody = false;

		int return_code = play_melody(passive_buzzer, happy_birthday, 250, 100);

		if (return_code) {
			return return_code;
		}
	}

	return 0;
}
