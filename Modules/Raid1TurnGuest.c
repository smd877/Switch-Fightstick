#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;

void Raid1TurnGuest_Module(USB_JoystickReport_Input_t* const ReportData)
{
	uint16_t cycle = duration_count % 20;
	switch (duration_count) {
	case 275 ... 299:
		ReportData->Button |= SWITCH_X;
		break;
	case 800 ... 824:
		ReportData->Button |= SWITCH_B;
		break;
	case 2000 ... 2024:
		ReportData->Button |= SWITCH_Y;
		break;
	case 2100 ... 5599:
		if (cycle >= 10) { ReportData->Button |= SWITCH_X; }
		break;
	case 5700 ... 5724:
		ReportData->HAT = HAT_RIGHT;
		break;
	case 5800 ... 12099:
		if (cycle >= 10) { ReportData->Button |= SWITCH_A; }
		break;
	case 15600 ... 15624:
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 15700 ... 17099:
		if (cycle >= 10) { ReportData->Button |= SWITCH_A; }
		break;
	case 17500:
		duration_count = 0;
	}
	duration_count++;
}