#include "passive_buzzer.h"
#include "utils/pwm.h"

#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>

struct passive_buzzer_t {
	uint gpio_pin;
	volatile bool is_playing_melody;
	volatile bool should_stop_playing_melody;
};

passive_buzzer_t *passive_buzzer_create(uint gpio_pin) {
	passive_buzzer_t *passive_buzzer = malloc(sizeof(passive_buzzer));

	if (!passive_buzzer) {
		return NULL;
	}

	passive_buzzer->gpio_pin = gpio_pin;
	passive_buzzer->is_playing_melody = false;
	passive_buzzer->should_stop_playing_melody = false;

	gpio_set_function(gpio_pin, GPIO_FUNC_PWM);

	return passive_buzzer;
}

passive_buzzer_note_t *passive_buzzer_note_create(uint frequency, float beats_count, uint volume) {
	passive_buzzer_note_t *note = malloc(sizeof(note));

	if (!note) {
		return NULL;
	}

	note->frequency = frequency;
	note->beats_count = beats_count;
	note->volume_percentage = volume;

	return note;
}

passive_buzzer_melody_t *passive_buzzer_melody_create(
	const passive_buzzer_note_t *notes[],
	size_t notes_count,
	uint tempo
) {
	size_t notes_size = notes_count * sizeof(passive_buzzer_note_t *);
	passive_buzzer_melody_t *melody = malloc(sizeof(passive_buzzer_melody_t) + notes_size);

	if (!melody) {
		return NULL;
	}

	melody->tempo = tempo;
	melody->notes_count = notes_count;

	memcpy(melody->notes, notes, notes_size);

	return melody;
}

void passive_buzzer_melody_clean_up(passive_buzzer_melody_t *melody) {
	for (size_t i = 0; i < melody->notes_count; i++) {
		free((passive_buzzer_note_t *)melody->notes[i]);
	}

	free(melody);

	melody = NULL;
}

void passive_buzzer_play_note(const passive_buzzer_t *passive_buzzer, const passive_buzzer_note_t *note, uint tempo) {
	pwm_configure_gpio_pin(passive_buzzer->gpio_pin, note->frequency * 2, note->volume_percentage);

	pwm_start(passive_buzzer->gpio_pin);
	sleep_ms(((note->beats_count * 60) / tempo) * 1000);
	pwm_stop(passive_buzzer->gpio_pin);
}

void passive_buzzer_play_melody(passive_buzzer_t *passive_buzzer, const passive_buzzer_melody_t *melody) {
	if (melody->notes_count > 0) {
		passive_buzzer->is_playing_melody = true;
	}

	passive_buzzer->should_stop_playing_melody = false;

	for (size_t i = 0; i < melody->notes_count && !passive_buzzer->should_stop_playing_melody; i++) {
		passive_buzzer_play_note(passive_buzzer, melody->notes[i], melody->tempo);
	}

	passive_buzzer->is_playing_melody = false;
	passive_buzzer->should_stop_playing_melody = false;
}

inline void passive_buzzer_stop(passive_buzzer_t *passive_buzzer) {
	passive_buzzer->should_stop_playing_melody = true;
}

inline bool passive_buzzer_is_playing(const passive_buzzer_t *passive_buzzer) {
	return passive_buzzer->is_playing_melody;
}
