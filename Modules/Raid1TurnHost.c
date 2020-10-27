#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;

void Raid1TurnHost_Module(USB_JoystickReport_Input_t* const ReportData)
{
	uint16_t cycle = duration_count % 20;
	switch (duration_count) {
	case 50 ... 74:
		ReportData->Button |= SWITCH_A;
		break;
	case 275 ... 299:
		ReportData->Button |= SWITCH_A;
		break;
	case 2800 ... 2824:
		ReportData->Button |= SWITCH_A;
		break;
	case 4075 ... 4099:
		ReportData->Button |= SWITCH_A;
		break;
	case 4500 ... 4524:
		ReportData->Button |= SWITCH_A;
		break;
	case 5275 ... 5299:
		ReportData->HAT = HAT_TOP;
		break;
	case 6650 ... 12149:
		if (cycle >= 10) { ReportData->Button |= SWITCH_A; }
		break;
	case 16650 ... 16674:
		ReportData->Button |= SWITCH_HOME;
		break;
	case 16825 ... 16849:
		ReportData->Button |= SWITCH_X;
		break;
	case 17000 ... 17024:
		ReportData->Button |= SWITCH_A;
		break;
	case 17500:
		duration_count = 0;
	}
	duration_count++;
}