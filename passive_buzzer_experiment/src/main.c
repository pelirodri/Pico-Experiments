#include "passive_buzzer_experiment.h"
#include "passivebuzzer/passive_buzzer.h"

#include <stdlib.h>
#include <hardware/gpio.h>
#include <hardware/timer.h>

static const uint passive_buzzer_gpio_pin = 15;
static const uint push_button_gpio_pin = 16;

static const passive_buzzer_t *passive_buzzer = NULL;
static volatile bool should_play_melody = false;

static uint32_t interrupt_debounce_delay_ms = 20;
static uint32_t last_interrupt_time_ms = 0;

static void set_up_button();
static void button_pressed_handler(uint, uint32_t);
static int check_for_should_play_melody();
static void clean_up();

int main() {
	passive_buzzer = passive_buzzer_create(passive_buzzer_gpio_pin);

	if (!passive_buzzer) {
		return 1;
	}

	set_up_button();
	
	bool return_code = 0;

	while (true) {
		return_code = check_for_should_play_melody();

		if (return_code) {
			break;
		}		
	}

	clean_up();	

	return return_code;
}

void set_up_button() {
	gpio_init(push_button_gpio_pin);
	gpio_set_dir(push_button_gpio_pin, GPIO_IN);
	gpio_pull_up(push_button_gpio_pin);
	gpio_set_irq_enabled_with_callback(push_button_gpio_pin, GPIO_IRQ_EDGE_FALL, true, &button_pressed_handler);
}

void button_pressed_handler(uint gpio, uint32_t events) {
	float current_time_ms = (float)time_us_32() / 1000;

	if (current_time_ms - last_interrupt_time_ms >= interrupt_debounce_delay_ms) {
		if (!passive_buzzer_is_playing(passive_buzzer)) {
			should_play_melody = true;
		} else {
			passive_buzzer_stop((passive_buzzer_t *)passive_buzzer);
			should_play_melody = false;
		}
	}

	last_interrupt_time_ms = current_time_ms;
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

void clean_up() {
	free((passive_buzzer_t *)passive_buzzer);
	gpio_set_irq_enabled_with_callback(push_button_gpio_pin, GPIO_IRQ_EDGE_FALL, false, NULL);
}
