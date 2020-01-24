#include "Joystick.h"
#include "Modules.h"

typedef enum {
	RESET_POSITION_1,
	HATCH_EGG,
	RESET_POSITION_2,
	GET_EGG,
	OPEN_POKEMON_BOX,
	PUT_POKEMON_IN_BOX,
	DONE,
} State_t;

static State_t state = RESET_POSITION_1;
static uint16_t duration_count = 0;
static uint16_t egg_count = 1;

static uint8_t ResetPosition(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 49:
		/* Open menu */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_X;
		break;
	case 50 ... 224:
		/* Move upper left */
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 225 ... 249:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 250 ... 999:
		/* Select current position */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 1000:
		return 1;
	}
	return 0;
}

static uint8_t HatchEgg(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	if (count % 5 == 0)
		ReportData->Button |= SWITCH_A;

	switch (count) {
	case 0 ... 200:
		/* Move right */
		ReportData->LX = STICK_MAX;
		break;
	case 18500:
		/*
		 * 18500 counts(about 148 seconds) is adjusted based on the time until 
		 * Dreepy's egg hatch.
		 * 
		 * Note:
		 *   You can change this value to a smaller value to optimize for other
		 *   Pokemon. However, setting too small this value may cause the player 
		 *   to fail to receive the egg.
		 */
		return 1;
	default:
		/* Turn around */
		ReportData->LX = STICK_MIN;
		ReportData->RX = STICK_MAX;
		break;
	}
	return 0;
}

static uint8_t OpenPokemonBox(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
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

static uint8_t PutPokemonInBox(USB_JoystickReport_Input_t* const ReportData, uint16_t count, uint16_t eggs)
{
	switch (count) {
	case 0 ... 49:
		/* Move next box */
		if ((eggs > 5) && (eggs % 30 == 5) && (count % 50 < 25))
			ReportData->Button |= SWITCH_R;
		break;
	case 50 ... 149:
		/* Switch range mode */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_Y;
		break;
	case 150 ... 174:
		/* Move party area */
		ReportData->HAT = HAT_LEFT;
		break;
	case 175 ... 199:
		/* Move to second pokemon position */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 200 ... 249:
		/* Select pokemon */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 250 ... 349:
		/* Move last pokemon */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 350 ... 399:
		/* Grab pokemons */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 400 ... 499:
		/* Move box list */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 500 ... 524:
		ReportData->HAT = HAT_RIGHT;
		break;
	case 550 ... 749:
		/* Select box list and put pokemons in current box */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 750 ... 1249:
		/* Cancel all */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_B;
		break;
	case 1250:
		return 1;
	}
	return 0;
}

static uint8_t GetEgg(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 99:
		/* Move to breeder */
		ReportData->LY = STICK_MAX - 30;
		break;
	case 100 ... 109:
		/* Move to breeder */
		ReportData->LX = STICK_MAX;
		break;
	case 150 ... 799:
		/* Get egg */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 800 ... 1399:
		/* End a conversation */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_B;
		break;
	case 1400:
		return 1;
	}
	return 0;
}

void HatchEggs_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case RESET_POSITION_1:
		if (ResetPosition(ReportData, duration_count)) {
			state = HATCH_EGG;
			duration_count = 0;
		}
		break;
	case HATCH_EGG:
		if (!HatchEgg(ReportData, duration_count))
			break;
		if (egg_count == MAX_EGG_COUNT || egg_count == LIMIT_EGG_COUNT)
			state = DONE;
		else if (egg_count % 5 == 0)
			state = OPEN_POKEMON_BOX;
		else if (egg_count % 30 < 30)
			state = RESET_POSITION_2;
		duration_count = 0;
		break;
	case OPEN_POKEMON_BOX:
		if (OpenPokemonBox(ReportData, duration_count)) {
			state = PUT_POKEMON_IN_BOX;
			duration_count = 0;
		}
		break;
	case PUT_POKEMON_IN_BOX:
		if (PutPokemonInBox(ReportData, duration_count, egg_count)) {
			state = RESET_POSITION_2;
			duration_count = 0;
		}
		break;
	case RESET_POSITION_2:
		if (ResetPosition(ReportData, duration_count)) {
			state = GET_EGG;
			duration_count = 0;
		}
		break;
	case GET_EGG:
		if (GetEgg(ReportData, duration_count)) {
			state = RESET_POSITION_1;
			duration_count = 0;
			egg_count++;
		}
		break;
	case DONE:
		break;
	}
	duration_count++;
}