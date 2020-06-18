#include "Joystick.h"
#include "Modules.h"

typedef enum {
	OPEN_POKEJOB_INIT,
	B_RESET_1,
	B_RESET_2,
	OPEN_POKEJOB_MAIN,
	MOVE_TOP,
	POKEJOB_SETUP,
	TOKIWATARI,
	POKEJOB_FINISH,
	DONE,
} State_t;

static State_t state = OPEN_POKEJOB_INIT;
static uint16_t duration_count = 0;
static uint16_t try_count = 0;
static uint16_t cursor = 0;

static uint8_t OpenPokeJob(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 75 ... 99:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 125 ... 134:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 145 ... 154:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 165 ... 174:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 525:
		return 1;
	}
	return 0;
}

static uint8_t BReset(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 24:
		/* Push B (salvage) */
		ReportData->Button |= SWITCH_B;
		break;
	case 50:
		return 1;
	}
	return 0;
}

static uint8_t MoveTop(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 10 ... 19:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 20:
		return 1;
	}
	return 0;
}

static uint8_t PokeJobSetup(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 50 ... 74:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 175 ... 199:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 300 ... 324:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 525 ... 549:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 575 ... 599:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 625 ... 649:
		/* Push B */
		ReportData->Button |= SWITCH_B;
		break;
	case 750 ... 774:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1025 ... 1049:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1125 ... 1149:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1300:
		return 1;
	}
	return 0;
}

static uint8_t TokiwatariCustom(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 24:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 100 ... 124:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 125 ... 224:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 225 ... 249:
		/* Move left */
		ReportData->HAT = HAT_LEFT;
		break;
	case 250 ... 274:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 325 ... 574:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 575 ... 599:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 625 ... 634:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 645 ... 654:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 665 ... 674:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 685 ... 694:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 705 ... 714:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 805 ... 814:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 825 ... 834:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 845 ... 854:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 945 ... 954:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 965 ... 974:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 985 ... 994:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 1005 ... 1014:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 1025 ... 1034:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 1045 ... 1054:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 1065 ... 1074:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 1085 ... 1094:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 1105 ... 1114:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1155 ... 1164:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 1265 ... 1274:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 1425:
		return 1;
	}
	return 0;
}

static uint8_t PokeJobFinish(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 125 ... 149:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 225 ... 249:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 325:
		return 1;
	}
	return 0;
}

void PokeJob_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case OPEN_POKEJOB_INIT:
		if (OpenPokeJob(ReportData, duration_count)) {
			state = B_RESET_1;
			duration_count = 0;
			cursor = 0;
		}
		break;
	case B_RESET_1:
		if (cursor != 6) {
			if (BReset(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		state = OPEN_POKEJOB_MAIN;
		duration_count = 0;
		break;
	case OPEN_POKEJOB_MAIN:
		if (OpenPokeJob(ReportData, duration_count)) {
			state = MOVE_TOP;
			duration_count = 0;
			cursor = 0;
		}
		break;
	case MOVE_TOP:
		// 0 : Exp
		// 1 : EV S
		// 2 : EV D
		// 3 : EV C
		// 4 : EV B
		// 5 : EV A
		// 6 : EV H
		if (TARGET_NUM != cursor) {
			if (MoveTop(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		state = POKEJOB_SETUP;
		break;
	case POKEJOB_SETUP:
		if (PokeJobSetup(ReportData, duration_count)) {
			state = TOKIWATARI;
			duration_count = 0;
		}
		break;
	case TOKIWATARI:
		if (TokiwatariCustom(ReportData, duration_count)) {
			state = POKEJOB_FINISH;
			duration_count = 0;
		}
		break;
	case POKEJOB_FINISH:
		if (PokeJobFinish(ReportData, duration_count)) {
			state = B_RESET_2;
			duration_count = 0;
			cursor = 0;
		}
		break;
	case B_RESET_2:
		if (cursor != 45) {
			if (BReset(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		try_count++;
		duration_count = 0;
		if (try_count == 25)
			state = DONE;
		else
			state = OPEN_POKEJOB_INIT;
		break;
	case DONE:
		break;
	}
	duration_count++;
}
