/*
 * Commands:
 *   Button: AA ... AAB
 *   Stick:  Slightly Upper Right
 * Reference:
 *   http://niwaka-syndrome.blog.jp/archives/20509394.html
 */

#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;

void LoopTournament_Module(USB_JoystickReport_Input_t* const ReportData)
{
	if (duration_count % 400 < 25)
		ReportData->Button |= SWITCH_B;
	else if (duration_count % 50 < 25)
		ReportData->Button |= SWITCH_A;

	/* Move a little upper right */
	ReportData->LY = STICK_MIN;
	ReportData->LX = STICK_CENTER + 30;
	duration_count++;
}
