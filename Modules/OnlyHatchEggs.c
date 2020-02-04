#include "Joystick.h"
#include "Modules.h"

typedef enum {
	NEXT_BOX,
	MOVE_RIGHT_INIT,
	PICK_UP,
	RESET_POSITION,
	TURN_AROUND,
	OPEN_POKEMON_BOX,
	TAKE_BACK_1,
	MOVE_RIGHT_BACK,
	TAKE_BACK_2,
	DONE,
} State_t;

static State_t state = NEXT_BOX;
static uint16_t duration_count = 0;
static uint16_t hatch_count = 0;
static uint16_t cursor = 0;

static uint8_t NextBox(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push R */
		ReportData->Button |= SWITCH_R;
		break;
	case 50:
		return 1;
	}
	return 0;
}

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
	case 1400 ... 1599:
		/* Move right */
		ReportData->LX = STICK_MAX;
		break;
	case 1600:
		return 1;
	}
	return 0;
}

static uint8_t TurnAround(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	if (count % 5 == 0)
		ReportData->Button |= SWITCH_A;

	switch (count) {
	case 27500:
		/*
		 * Optimize ex.
		 * Cycle 40 => 27500 (about 220 seconds)
		 * Cycle 20 => 20625 (about 165 seconds)
		 * Cycle 05 => 13750 (about 110 seconds)
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

static uint8_t MoveRight(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 50:
		return 1;
	}
	return 0;
}

static uint8_t PickUp(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push Y */
		ReportData->Button |= SWITCH_Y;
		break;
	case 75 ... 99:
		/* Push Y */
		ReportData->Button |= SWITCH_Y;
		break;
	case 125 ... 149:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 175 ... 199:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 225 ... 249:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 275 ... 499:
		/* Move left keep */
		ReportData->HAT = HAT_LEFT;
		break;
	case 525 ... 549:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 575 ... 599:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 600 ... 1599:
		if (count % 50 < 25)
			/* Push B (salvage) */
			ReportData->Button |= SWITCH_B;
		break;
	case 1600:
		return 1;
	}
	return 0;
}

static uint8_t TakeBack1(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push Y */
		ReportData->Button |= SWITCH_Y;
		break;
	case 75 ... 99:
		/* Push Y */
		ReportData->Button |= SWITCH_Y;
		break;
	case 125 ... 149:
		/* Move left */
		ReportData->HAT = HAT_LEFT;
		break;
	case 175 ... 199:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 225 ... 249:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 275 ... 299:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 325 ... 349:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 375 ... 399:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 425 ... 449:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 450:
		return 1;
	}
	return 0;
}

static uint8_t TakeBack2(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 75 ... 99:
		/* Push Y */
		ReportData->Button |= SWITCH_Y;
		break;
	case 125 ... 349:
		/* Move left keep */
		ReportData->HAT = HAT_LEFT;
		break;
	case 375 ... 399:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 400:
		return 1;
	}
	return 0;
}

void OnlyHatchEggs_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case NEXT_BOX:
		if ((hatch_count / 6 > 0) && (hatch_count % 6 == 0)) {
			if (NextBox(ReportData, duration_count)) {
				state = MOVE_RIGHT_INIT;
				duration_count = 0;
			}
			break;
		}
		state = MOVE_RIGHT_INIT;
		cursor = 0;
		break;
	case MOVE_RIGHT_INIT:
		if (!((hatch_count % 6) % 6 == cursor)) {
			if (MoveRight(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		state = PICK_UP;
		cursor = 0;
		break;
	case PICK_UP:
		if (PickUp(ReportData, duration_count)) {
			state = RESET_POSITION;
			duration_count = 0;
		}
		break;
	case RESET_POSITION:
		if (ResetPosition(ReportData, duration_count)) {
			state = TURN_AROUND;
			duration_count = 0;
		}
		break;
	case TURN_AROUND:
		if (TurnAround(ReportData, duration_count)) {
			state = OPEN_POKEMON_BOX;
			duration_count = 0;
		}
		break;
	case OPEN_POKEMON_BOX:
		if (OpenPokemonBox(ReportData, duration_count)) {
			state = TAKE_BACK_1;
			duration_count = 0;
		}
		break;
	case TAKE_BACK_1:
		if (TakeBack1(ReportData, duration_count)) {
			state = MOVE_RIGHT_BACK;
			duration_count = 0;
		}
		break;
	case MOVE_RIGHT_BACK:
		if (!(((hatch_count % 6) % 6) + 1 == cursor)) {
			if (MoveRight(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		state = TAKE_BACK_2;
		cursor = 0;
		break;
	case TAKE_BACK_2:
		if (TakeBack2(ReportData, duration_count)) {
			hatch_count++;
			duration_count = 0;
			if (hatch_count >= (MAX_EGG_COUNT / 5))
				state = DONE;
			else
				state = NEXT_BOX;
		}
		break;
	case DONE:
		break;
	}
	duration_count++;
}
