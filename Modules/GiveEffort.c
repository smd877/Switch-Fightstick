#include "Joystick.h"
#include "Modules.h"

typedef enum {
	INIT,
	OPEN_POKEJOB_INIT,
	B_RESET_1,
	B_RESET_2,
	OPEN_POKEJOB_MAIN,
	POKEJOB_SETUP,
	TOKIWATARI,
	POKEJOB_FINISH,
	DONE,
} State_t;

static State_t state = INIT;
static uint16_t duration_count = 0;
static uint16_t position = 0;
static uint16_t cursor = 0;

typedef struct {
	uint16_t type;
	uint16_t period;
} data;

static data data_lists[30] = {};

static uint16_t AddAction(uint16_t type, uint16_t inParam, uint16_t limit)
{
	uint16_t divide = 0;
	uint16_t period = 0;
	if (inParam >= limit) {
		switch (limit) {
		case 96: period = 0; break;
		case 48: period = 1; break;
		case 32: period = 2; break;
		case 16: period = 3; break;
		case 12: period = 4; break;
		case 8: period = 5; break;
		case 4: period = 6; break;
		}
		divide = inParam / limit;
		if (limit == 96 && inParam > 250)
			divide = 3;
		for (int i = 0; i < divide; i++) {
			data row;
			row.type = type;
			row.period = period;
			data_lists[position] = row;
			position++;
		}
		if (limit == 96 &&inParam > 250)
			return 0;
		else
			return inParam % limit;
	}
	return inParam;
}

static void AddEffortType(uint16_t type, uint16_t inParam)
{
	uint16_t tmp_param = inParam;
	tmp_param = AddAction(type, tmp_param, 96);
	tmp_param = AddAction(type, tmp_param, 48);
	tmp_param = AddAction(type, tmp_param, 32);
	tmp_param = AddAction(type, tmp_param, 16);
	tmp_param = AddAction(type, tmp_param, 12);
	tmp_param = AddAction(type, tmp_param, 8);
	tmp_param = AddAction(type, tmp_param, 4);
}

static void Initial(void)
{
	AddEffortType(6, EFFORT_H);
	AddEffortType(5, EFFORT_A);
	AddEffortType(4, EFFORT_B);
	AddEffortType(3, EFFORT_C);
	AddEffortType(2, EFFORT_D);
	AddEffortType(1, EFFORT_S);
}

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

static uint8_t BReset(USB_JoystickReport_Input_t* const ReportData, uint16_t count, const uint16_t keep_time)
{
	uint16_t cycle = count % 20;
	if (count >= keep_time) {
		return 1;
	} else if (cycle >= 10) {
		/* Push B (salvage) */
		ReportData->Button |= SWITCH_B;
	}
	return 0;
}

static uint8_t PokeJobSetup(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	uint16_t cycle = count % 20;
	uint16_t limit_type = data_lists[cursor].type * 20;
	uint16_t limit_period = data_lists[cursor].period * 20 + 1300;
	switch (count) {
	case 0 ... 119:
		if (cycle >= 10 && limit_type >= count) {
			/* Move top */
			ReportData->HAT = HAT_TOP;
		}
		break;
	case 170 ... 194:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 295 ... 319:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 420 ... 444:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 645 ... 669:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 695 ... 719:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 745 ... 769:
		/* Push B */
		ReportData->Button |= SWITCH_B;
		break;
	case 870 ... 894:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1145 ... 1169:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1300 ... 1420:
		if (cycle >= 10 && limit_period >= count) {
			/* Move bottom */
			ReportData->HAT = HAT_BOTTOM;
		}
		break;
	case 1600 ... 1625:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1800:
		cursor++;
		return 1;
	}
	return 0;
}

static uint8_t Tokiwatari(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
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

void GiveEffort_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case INIT:
		Initial();
		state = OPEN_POKEJOB_INIT;
		duration_count = 0;
		break;
	case OPEN_POKEJOB_INIT:
		if (OpenPokeJob(ReportData, duration_count)) {
			state = B_RESET_1;
			duration_count = 0;
		}
		break;
	case B_RESET_1:
		if (BReset(ReportData, duration_count, 600)) {
			state = OPEN_POKEJOB_MAIN;
			duration_count = 0;
		}
		break;
	case OPEN_POKEJOB_MAIN:
		if (OpenPokeJob(ReportData, duration_count)) {
			state = POKEJOB_SETUP;
			duration_count = 0;
		}
		break;
	case POKEJOB_SETUP:
		if (PokeJobSetup(ReportData, duration_count)) {
			state = TOKIWATARI;
			duration_count = 0;
		}
		break;
	case TOKIWATARI:
		if (Tokiwatari(ReportData, duration_count)) {
			state = POKEJOB_FINISH;
			duration_count = 0;
		}
		break;
	case POKEJOB_FINISH:
		if (PokeJobFinish(ReportData, duration_count)) {
			state = B_RESET_2;
			duration_count = 0;
		}
		break;
	case B_RESET_2:
		if (BReset(ReportData, duration_count, 2400)) {
			if (data_lists[cursor].type > 0)
				state = OPEN_POKEJOB_INIT;
			else
				state = DONE;
			duration_count = 0;
		}
		break;
	case DONE:
		break;
	}
	duration_count++;
}
