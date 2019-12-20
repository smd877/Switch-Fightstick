#include "Joystick.h"
#include "Modules.h"

static uint8_t state = SYNC_CONTROLLER;
static uint16_t duration_count = 0;
static uint16_t egg_count = 1;

uint8_t ResetPosition(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
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
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 1000:
		return 1;
	}
	return 0;
}

uint8_t HatchEgg(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	if (count % 5 == 0)
		ReportData->Button |= SWITCH_A;

	switch (count) {
	case 0 ... 200:
		/* Move right */
		ReportData->LX = STICK_MAX;
		break;
	case 18500:
		return 1;
	default:
		/* Turn around */
		ReportData->LX = STICK_MIN;
		ReportData->RX = STICK_MAX;
		break;
	}
	return 0;
}

uint8_t PutPokemonInBox(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
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
	case 700 ... 799:
		/* Switch range mode */
		if (count % 50 < 25)
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
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 900 ... 999:
		/* Move last pokemon */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 1000 ... 1049:
		/* Grab pokemons */
		if (count % 50 < 25)
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
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 1400 ... 1799:
		/* Cancel all */
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_B;
		break;
	case 1800:
		return 1;
	}
	return 0;
}

uint8_t GetEgg(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
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
	case SYNC_CONTROLLER:
		if (SyncController(ReportData, duration_count)) {
			state = RESET_POSITION_1;
			duration_count = 0;
		}
		break;
	case RESET_POSITION_1:
		if (ResetPosition(ReportData, duration_count)) {
			state = HATCH_EGG;
			duration_count = 0;
		}
		break;
	case HATCH_EGG:
		if (!HatchEgg(ReportData, duration_count))
			break;
		if (egg_count % 5 == 0)
			state = PUT_POKEMON_IN_BOX;
		else if (egg_count < 30)
			state = RESET_POSITION_2;
		else
			state = DONE;
		duration_count = 0;
		break;
	case PUT_POKEMON_IN_BOX:
		if (PutPokemonInBox(ReportData, duration_count)) {
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