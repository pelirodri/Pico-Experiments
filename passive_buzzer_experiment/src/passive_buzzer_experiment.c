#include "passive_buzzer_experiment.h"

static int play_happy_birthday_melody(const passive_buzzer_t *, uint, uint);

int play_melody(const passive_buzzer_t *passive_buzzer, melody_id_t melody_id, uint tempo, uint volume) {
	switch (melody_id) {
		case happy_birthday:
			return play_happy_birthday_melody(passive_buzzer, tempo, volume);
		default:
			return 2;
	}
}

int play_notes(
	const passive_buzzer_t *passive_buzzer,
	const passive_buzzer_note_t *notes[],
	size_t notes_count,
	uint tempo
) {
	const passive_buzzer_melody_t *melody = passive_buzzer_melody_create(notes, notes_count, tempo);

	if (!melody) {
		return 3;
	}

	passive_buzzer_play_melody((passive_buzzer_t *)passive_buzzer, melody);
	passive_buzzer_melody_clean_up((passive_buzzer_melody_t *)melody);

	return 0;
}

int play_happy_birthday_melody(const passive_buzzer_t *passive_buzzer, uint tempo, uint volume) {
	const passive_buzzer_note_t *happy_birthday_notes[] = {
		passive_buzzer_note_create(C3, 1.25, volume),
		passive_buzzer_note_create(C3, 0.75, volume),
		passive_buzzer_note_create(D3, 3, volume),
		passive_buzzer_note_create(C3, 2.5, volume),
		passive_buzzer_note_create(F3, 3, volume),
		passive_buzzer_note_create(E3, 3, volume),
		passive_buzzer_note_create(rest, 1, volume),
		passive_buzzer_note_create(C3, 1.25, volume),
		passive_buzzer_note_create(C3, 0.75, volume),
		passive_buzzer_note_create(D3, 3, volume),
		passive_buzzer_note_create(C3, 2.5, volume),
		passive_buzzer_note_create(G3, 3, volume),
		passive_buzzer_note_create(F3, 3, volume),
		passive_buzzer_note_create(rest, 1, volume),
		passive_buzzer_note_create(C3, 1.25, volume),
		passive_buzzer_note_create(C3, 0.75, volume),
		passive_buzzer_note_create(C4, 3, volume),
		passive_buzzer_note_create(A3, 2.5, volume),
		passive_buzzer_note_create(F3, 3, volume),
		passive_buzzer_note_create(E3, 3, volume),
		passive_buzzer_note_create(D3, 3, volume),
		passive_buzzer_note_create(rest, 1, volume),
		passive_buzzer_note_create(C4, 1.25, volume),
		passive_buzzer_note_create(C4, 0.75, volume),
		passive_buzzer_note_create(A3, 3, volume),
		passive_buzzer_note_create(F3, 2.5, volume),
		passive_buzzer_note_create(G3, 3, volume),
		passive_buzzer_note_create(F3, 3, volume)
	};

	size_t happy_birthday_notes_count = sizeof(happy_birthday_notes) / sizeof(happy_birthday_notes[0]);

	return play_notes(passive_buzzer, happy_birthday_notes, happy_birthday_notes_count, tempo);
}
