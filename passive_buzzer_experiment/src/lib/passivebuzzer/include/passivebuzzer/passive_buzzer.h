#ifndef PASSIVE_BUZZER_H
#define PASSIVE_BUZZER_H
#include <stdbool.h>
#include <sys/types.h>

/// Opaque passive buzzer `struct`.
typedef struct passive_buzzer_t passive_buzzer_t;

/// Single note.
typedef struct passive_buzzer_note_t {
	/// Note frequency.
	uint frequency;
	/// Duration of the note in beats.
	float beats_count;
	// Percentage of the volume to play the note at.
	uint volume_percentage;
} passive_buzzer_note_t;

/// Melody.
typedef struct passive_buzzer_melody_t {
	/// BPM.
	uint tempo;
	/// Number of notes in the notes array.
	size_t notes_count;
	/// Notes of the melody.
	const passive_buzzer_note_t *notes[];
} passive_buzzer_melody_t;

/// Convenience `enum` with frequencies of musical notes.
typedef enum passive_buzzer_musical_note_t {
	/// C0.
	C0 = 16,
	/// C♯0.
	Cs0 = 17,
	/// D♭0.
	Db0 = 17,
	/// D0.
	D0 = 18,
	/// D♯0.
	Ds0 = 19,
	/// E♭0.
	Eb0 = 19,
	/// E0.
	E0 = 21,
	/// F0.
	F0 = 22,
	/// F♯0.
	Fs0 = 23,
	/// G♭0.
	Gb0 = 23,
	/// G0.
	G0 = 25,
	/// G♯0.
	Gs0 = 26,
	/// A♭0.
	Ab0 = 26,
	/// A0.
	A0 = 28,
	/// A♯0.
	As0 = 29,
	/// B♭0.
	Bb0 = 29,
	/// B0.
	B0 = 31,
	/// C1.
	C1 = 33,
	/// C♯1.
	Cs1 = 35,
	/// D♭1.
	Db1 = 35,
	/// D1.
	D1 = 37,
	/// D♯1.
	Ds1 = 39,
	/// E♭1.
	Eb1 = 39,
	/// E1.
	E1 = 41,
	/// F1.
	F1 = 44,
	/// F♯1.
	Fs1 = 46,
	/// G♭1.
	Gb1 = 46,
	/// G1.
	G1 = 49,
	/// G♯1.
	Gs1 = 52,
	/// A♭1.
	Ab1 = 52,
	/// A1.
	A1 = 55,
	/// A♯1.
	As1 = 58,
	/// B♭1.
	Bb1 = 58,
	/// B1.
	B1 = 62,
	/// C2.
	C2 = 65,
	/// C♯2.
	Cs2 = 69,
	/// D♭2.
	Db2 = 69,
	/// D2.
	D2 = 73,
	/// D♯2.
	Ds2 = 78,
	/// E♭2.
	Eb2 = 78,
	/// E2.
	E2 = 82,
	/// F2.
	F2 = 87,
	/// F♯2.
	Fs2 = 93,
	/// G♭2.
	Gb2 = 93,
	/// G2.
	G2 = 98,
	/// G♯2.
	Gs2 = 104,
	/// A♭2.
	Ab2 = 104,
	/// A2.
	A2 = 110,
	/// A♯2.
	As2 = 117,
	/// B♭2.
	Bb2 = 117,
	/// B2.
	B2 = 123,
	/// C3.
	C3 = 131,
	/// C♯3.
	Cs3 = 139,
	/// D♭3.
	Db3 = 139,
	/// D3.
	D3 = 147,
	/// D♯3.
	Ds3 = 156,
	/// E♭3.
	Eb3 = 156,
	/// E3.
	E3 = 165,
	/// F3.
	F3 = 175,
	/// F♯3.
	Fs3 = 185,
	/// G♭3.
	Gb3 = 185,
	/// G3.
	G3 = 196,
	/// G♯3.
	Gs3 = 208,
	/// A♭3.
	Ab3 = 208,
	/// A3.
	A3 = 220,
	/// A♯3.
	As3 = 233,
	/// B♭3.
	Bb3 = 233,
	/// B3.
	B3 = 247,
	/// C4.
	C4 = 262,
	/// C♯4.
	Cs4 = 277,
	/// D♭4.
	Db4 = 277,
	/// D4.
	D4 = 294,
	/// D♯4.
	Ds4 = 311,
	/// E♭4.
	Eb4 = 311,
	/// E4.
	E4 = 330,
	/// F4.
	F4 = 349,
	/// F♯4.
	Fs4 = 370,
	/// G♭4.
	Gb4 = 370,
	/// G4.
	G4 = 392,
	/// G♯4.
	Gs4 = 415,
	/// A♭4.
	Ab4 = 415,
	/// A4.
	A4 = 440,
	/// A♯4.
	As4 = 466,
	/// B♭4.
	Bb4 = 466,
	/// B4.
	B4 = 494,
	/// C5.
	C5 = 523,
	/// C♯5.
	Cs5 = 554,
	/// D♭5.
	Db5 = 554,
	/// D5.
	D5 = 587,
	/// D♯5.
	Ds5 = 622,
	/// E♭5.
	Eb5 = 622,
	/// E5.
	E5 = 659,
	/// F5.
	F5 = 698,
	/// F♯5.
	Fs5 = 740,
	/// G♭5.
	Gb5 = 740,
	/// G5.
	G5 = 784,
	/// G♯5.
	Gs5 = 831,
	/// A♭5.
	Ab5 = 831,
	/// A5.
	A5 = 880,
	/// A♯5.
	As5 = 932,
	/// B♭5.
	Bb5 = 932,
	/// B5.
	B5 = 988,
	/// C6.
	C6 = 1047,
	/// C♯6.
	Cs6 = 1109,
	/// D♭6.
	Db6 = 1109,
	/// D6.
	D6 = 1175,
	/// D♯6.
	Ds6 = 1245,
	/// E♭6.
	Eb6 = 1245,
	/// E6.
	E6 = 1319,
	/// F6.
	F6 = 1397,
	/// F♯6.
	Fs6 = 1480,
	/// G♭6.
	Gb6 = 1480,
	/// G6.
	G6 = 1568,
	/// G♯6.
	Gs6 = 1661,
	/// A♭6.
	Ab6 = 1661,
	/// A6.
	A6 = 1760,
	/// A♯6.
	As6 = 1865,
	/// B♭6.
	Bb6 = 1865,
	/// B6.
	B6 = 1976,
	/// C7.
	C7 = 2093,
	/// C♯7.
	Cs7 = 2217,
	/// D♭7.
	Db7 = 2217,
	/// D7.
	D7 = 2349,
	/// D♯7.
	Ds7 = 2489,
	/// E♭7.
	Eb7 = 2489,
	/// E7.
	E7 = 2637,
	/// F7.
	F7 = 2794,
	/// F♯7.
	Fs7 = 2960,
	/// G♭7.
	Gb7 = 2960,
	/// G7.
	G7 = 3136,
	/// G♯7.
	Gs7 = 3322,
	/// A♭7.
	Ab7 = 3322,
	/// A7.
	A7 = 3520,
	/// A♯7.
	As7 = 3729,
	/// B♭7.
	Bb7 = 3729,
	/// B7.
	B7 = 3951,
	/// C8.
	C8 = 4186,
	/// C♯8.
	Cs8 = 4435,
	/// D♭8.
	Db8 = 4435,
	/// D8.
	D8 = 4699,
	/// D♯8.
	Ds8 = 4978,
	/// E♭8.
	Eb8 = 4978,
	/// E8.
	E8 = 5274,
	/// F8.
	F8 = 5588,
	/// F♯8.
	Fs8 = 5920,
	/// G♭8.
	Gb8 = 5920,
	/// G8.
	G8 = 6272,
	/// G♯8.
	Gs8 = 6645,
	/// A♭8.
	Ab8 = 6645,
	/// A8.
	A8 = 7040,
	/// A♯8.
	As8 = 7459,
	/// B♭8.
	Bb8 = 7459,
	/// B8.
	B8 = 7902,
	/// Rest (silence).
	rest = 0
} passive_buzzer_musical_note_t;

/**
 * Creates an opaque passive buzzer `struct`.
 * @param gpio_pin The GPIO pin connected to the buzzer.
 * @returns The opaque passive buzzer `struct`.
*/
passive_buzzer_t *passive_buzzer_create(uint gpio_pin);

/**
 * Convenience function to create a new note.
 * @param frequency The frequency of the note.
 * @param beats_count The duration of the note in beats.
 * @param volume The volume percentage to play the note at.
 * @returns The created noted.
*/
passive_buzzer_note_t *passive_buzzer_note_create(uint frequency, float beats_count, uint volume);

/**
 * Convenience function to create a new melody.
 * @param notes And array of notes to play.
 * @param notes_count The number of notes in the array.
 * @param tempo The tempo to play the melody at.
 * @returns The created melody.
*/
passive_buzzer_melody_t *passive_buzzer_melody_create(
	const passive_buzzer_note_t *notes[],
	size_t notes_count,
	uint tempo
);

/**
 * Frees up the memory in use by a melody.
 * @param melody The memory whose resources to clean up.
*/
void passive_buzzer_melody_clean_up(passive_buzzer_melody_t *melody);

/**
 * Plays a note.
 * @param passive_buzzer Buzzer to play.
 * @param note Note to play.
*/
void passive_buzzer_play_note(const passive_buzzer_t *passive_buzzer, const passive_buzzer_note_t *note, uint tempo);

/**
 * Plays a melody.
 * @param passive_buzzer Buzzer to play.
 * @param melody The melody to play.
*/
void passive_buzzer_play_melody(passive_buzzer_t *passive_buzzer, const passive_buzzer_melody_t *melody);

/**
 * Stops the buzzer if it was playing a melody.
 * @param passive_buzzer The buzzer to stop.
*/
void passive_buzzer_stop(passive_buzzer_t *passive_buzzer);

/**
 * Checks whether the buzzer is playing a melody.
 * @param passive_buzzer The buzzer to check.
 * @returns Whether the buzzer is playing.
*/
bool passive_buzzer_is_playing(const passive_buzzer_t *passive_buzzer);
#endif
