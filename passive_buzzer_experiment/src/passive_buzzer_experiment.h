#ifndef PASSIVE_BUZZER_EXPERIMENT_H
#define PASSIVE_BUZZER_EXPERIMENT_H
#include "return_code_t.h"
#include "passivebuzzer/passive_buzzer.h"

typedef enum melody_id_t {
	happy_birthday
} melody_id_t;

return_code_t play_melody(const passive_buzzer_t *, melody_id_t, uint, uint);
return_code_t play_notes(const passive_buzzer_t *, const passive_buzzer_note_t *[], size_t, uint);
#endif
