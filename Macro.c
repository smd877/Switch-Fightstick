#include "Joystick.h"

typedef enum {
	SYNC_CONTROLLER,
	RESET_POSITION_1,
	HATCH_EGG,
	RESET_POSITION_2,
	GET_EGG,
	PUT_POKEMON_IN_BOX,
	DONE,
} State_t;

static State_t state = SYNC_CONTROLLER;
static uint16_t duration_count = 0;
static uint16_t egg_count = 1;

void SyncController(USB_JoystickReport_Input_t* const ReportData)
{
	switch (duration_count) {
	case 25:
	case 50:
		ReportData->Button |= SWITCH_L | SWITCH_R;
		break;
	case 75:
	case 100:
		ReportData->Button |= SWITCH_A;
		break;
	case 101:
		duration_count = 0;
		return;
	}
	duration_count++;
}

void ResetPosition(USB_JoystickReport_Input_t* const ReportData)
{
	switch (duration_count) {
	case 25 ... 49:
		/* Open menu */
		ReportData->Button |= SWITCH_X;
		break;
	case 50 ... 249:
		/* Move to the leftmost position */
		ReportData->HAT = HAT_BOTTOM_LEFT;
		break;
	case 250 ... 999:
		/* Select current position */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 1000:
		duration_count = 0;
		return;
	}
	duration_count++;
}

void HatchEgg(USB_JoystickReport_Input_t* const ReportData)
{
	if (duration_count % 5 == 0)
		ReportData->Button |= SWITCH_A;

	switch (duration_count) {
	case 0 ... 200:
		/* Move right */
		ReportData->LX = STICK_MAX;
		break;
	case 18500:
		duration_count = 0;
		return;
	default:
		/* Turn around */
		ReportData->LX = STICK_MIN;
		ReportData->RX = STICK_MAX;
		break;
	}
	duration_count++;
}

void PutPokemonInBox(USB_JoystickReport_Input_t* const ReportData)
{
	switch (duration_count) {
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
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 500 ... 549:
		/* Enter pokemon box */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_R;
		break;
	case 700 ... 799:
		/* Switch range mode */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_Y;
		break;
	case 800 ... 824:
		/* Move party area */
		ReportData->HAT = HAT_LEFT;
		break;
	case 825 ... 849:
		/* Move to second pokemon position */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 850 ... 899:
		/* Select pokemon */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 900 ... 999:
		/* Move last pokemon */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 1000 ... 1049:
		/* Grab pokemons */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 1050 ... 1149:
		/* Move box list */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 1150 ... 1174:
		ReportData->HAT = HAT_RIGHT;
		break;
	case 1200 ... 1399:
		/* Select box list and put pokemons in current box */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 1400 ... 1799:
		/* Cancel all */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_B;
		break;
	case 1800:
		duration_count = 0;
		return;
	}
	duration_count++;
}

void GetEgg(USB_JoystickReport_Input_t* const ReportData)
{
	switch (duration_count) {
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
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 800 ... 1399:
		/* End a conversation */
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_B;
		break;
	case 1400:
		duration_count = 0;
		return;
	}
	duration_count++;
}

void GetNextReport(USB_JoystickReport_Input_t* const ReportData)
{
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;
	ReportData->Button = SWITCH_RELEASE;

	switch (state) {
	case SYNC_CONTROLLER:
		SyncController(ReportData);
		if (duration_count == 0)
			state = RESET_POSITION_1;
		break;
	case RESET_POSITION_1:
		ResetPosition(ReportData);
		if (duration_count == 0)
			state = HATCH_EGG;
		break;
	case HATCH_EGG:
		HatchEgg(ReportData);
		if (duration_count > 0)
			break;
		if (egg_count % 5 == 0)
			state = PUT_POKEMON_IN_BOX;
		else if (egg_count < 30)
			state = RESET_POSITION_2;
		else
			state = DONE;
		break;
	case PUT_POKEMON_IN_BOX:
		PutPokemonInBox(ReportData);
		if (duration_count == 0)
			state = RESET_POSITION_2;
		break;
	case RESET_POSITION_2:
		ResetPosition(ReportData);
		if (duration_count == 0)
			state = GET_EGG;
		break;
	case GET_EGG:
		GetEgg(ReportData);
		if (duration_count == 0) {
			state = RESET_POSITION_1;
			egg_count++;
		}
		break;
	case DONE:
		break;
	}
}