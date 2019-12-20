#include "Joystick.h"
#include "Modules.h"

uint8_t SyncController(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25:
	case 50:
		ReportData->Button |= SWITCH_L | SWITCH_R;
		break;
	case 75:
	case 100:
		ReportData->Button |= SWITCH_A;
		break;
	case 101:
		return 1;
	}
	return 0;
}

void GetNextReport(USB_JoystickReport_Input_t* const ReportData)
{
	/* Reset Controller */
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;
	ReportData->Button = SWITCH_RELEASE;

#if defined(LOOP_TOURNAMENT)
	LoopTournament_Module(ReportData);
#elif defined(REPEAT_A)
	RepeatA_Module(ReportData);
#else
	HatchEggs_Module(ReportData);
#endif
}