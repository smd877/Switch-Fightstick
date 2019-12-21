#include "Joystick.h"
#include "Modules.h"

typedef enum {
	OPEN_POKEMON_BOX,
	RELEASE_POKEMON,
	SELECT_OTHER_POKEMON,
	DONE,
} State_t;

static State_t state = OPEN_POKEMON_BOX;
static uint16_t duration_count = 0;
static uint8_t release_count = 0;

uint8_t OpenPokemonBox(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Open menu */
		ReportData->Button |= SWITCH_X;
		break;
	case 50 ... 249:
		/* Move pokemon menu */
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 300 ... 349:
		/* Select pokemon menu */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 500 ... 549:
		/* Enter pokemon box */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_R;
		break;
	case 700:
		return 1;
	}
	return 0;
}

uint8_t ReleasePokemon(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 49:
		/* Select a pokemon */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 50 ... 149:
		/* Move until "release" */
		if (count % 50 < 25)
			ReportData->HAT = HAT_TOP;
		break;
	case 150 ... 199:
		/* Select "release" */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 250 ... 299:
		/* Select "yes" */
		if (count % 50 < 25)
			ReportData->HAT = HAT_TOP;
		break;
	case 300 ... 499:
		/* Remove message */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 500:
		return 1;
	}
	return 0;
}

uint8_t SelectOtherPokemon(USB_JoystickReport_Input_t* const ReportData, uint16_t count, uint8_t release_num)
{
	switch (count) {
	case 0 ... 49:
		if (release_num % 6 == 0 && count % 50 < 25)
			ReportData->HAT = HAT_BOTTOM;
		else if (release_num % 12 < 6 && count % 50 < 25)
			ReportData->HAT = HAT_RIGHT;
		else if (count % 50 < 25)
			ReportData->HAT = HAT_LEFT;
		break;
	case 50:
		return 1;
	}
	return 0;
}

void ReleasePokemons_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case OPEN_POKEMON_BOX:
		if (OpenPokemonBox(ReportData, duration_count)) {
			state = RELEASE_POKEMON;
			duration_count = 0;
		}
		break;
	case RELEASE_POKEMON:
		if (ReleasePokemon(ReportData, duration_count)) {
			state = SELECT_OTHER_POKEMON;
			duration_count = 0;
			release_count++;
		}
		break;
	case SELECT_OTHER_POKEMON:
		if (release_count == 30) {
			state = DONE;
		} else if (SelectOtherPokemon(ReportData, duration_count, release_count)) {
			state = RELEASE_POKEMON;
			duration_count = 0;
		}
		break;
	case DONE:
		break;
	}
	duration_count++;
}