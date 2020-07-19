#include "Joystick.h"
#include "Modules.h"

typedef enum {
	INIT,
	COLLECT,
	TOKIWATARI,
	DONE,
} State_t;

static State_t state = INIT;
static uint16_t duration_count = 0;

static uint8_t Initial(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		ReportData->Button |= SWITCH_X;
		break;
	case 200 ... 224:
		ReportData->Button |= SWITCH_A;
		break;
	case 575 ... 579:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MIN;
		break;
	case 630 ... 654:
		ReportData->Button |= SWITCH_A;
		break;
	case 725 ... 749:
		ReportData->Button |= SWITCH_A;
		break;
	case 1200:
		return 1;
	}
	return 0;
}

static uint8_t Collect(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	if (count % 20 > 10) {
		ReportData->Button |= SWITCH_A;
	}
	switch (count) {
	// No.01
	case 25 ... 64:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MAX;
		break;
	case 65 ... 414:
		ReportData->LX = STICK_MAX;
		break;
	// No.02
	case 515 ... 664:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MIN;
		break;
	case 665 ... 774:
		ReportData->LX = STICK_MAX;
		break;
	// No.03
	case 875 ... 1024:
		ReportData->LX = STICK_MAX;
		break;
	case 1025 ... 1074:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MAX;
		break;
	// No.04
	case 1175 ... 1229:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MAX;
		break;
	case 1230 ... 1354:
		ReportData->LX = STICK_MAX;
		break;
	// No.05
	case 1455 ... 1529:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MIN;
		break;
	case 1530 ... 1579:
		ReportData->LX = STICK_MAX;
		break;
	// No.06
	case 1680 ... 1759:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MAX;
		break;
	case 1760 ... 2019:
		ReportData->LX = STICK_MAX;
		break;
	// No.07
	case 2120 ... 2279:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MIN;
		break;
	case 2280 ... 2359:
		ReportData->LX = STICK_MAX;
		break;
	// No.08
	case 2460 ... 2679:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MAX;
		break;
	case 2680 ... 2729:
		ReportData->LX = STICK_MAX;
		break;
	// No.09
	case 2830 ... 2929:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MIN;
		break;
	case 2930 ... 3069:
		ReportData->LX = STICK_MAX;
		break;
	// No.10
	case 3170 ... 3239:
		ReportData->LX = STICK_MAX;
		ReportData->LY = STICK_MAX;
		break;
	case 3240 ... 3294:
		ReportData->LX = STICK_MAX;
		break;
	case 3500:
		return 1;
	}
	return 0;
}

void CollectWing_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case INIT:
		if (Initial(ReportData, duration_count)) {
			state = COLLECT;
			duration_count = 0;
		}
		break;
	case COLLECT:
		if (Collect(ReportData, duration_count)) {
			state = TOKIWATARI;
			duration_count = 0;
		}
		break;
	case TOKIWATARI:
		if (Tokiwatari(ReportData, duration_count)) {
			state = INIT;
			duration_count = 0;
		}
		break;
	case DONE:
		break;
	}
	duration_count++;
}
