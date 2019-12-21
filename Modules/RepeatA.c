#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;

void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData)
{
	if (duration_count % 50 < 25)
		ReportData->Button |= SWITCH_A;
	duration_count++;
}