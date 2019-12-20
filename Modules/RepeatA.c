#include "Joystick.h"
#include "Modules.h"

static uint8_t state = SYNC_CONTROLLER;
static uint16_t duration_count = 0;

void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case SYNC_CONTROLLER:
		if (SyncController(ReportData, duration_count)) {
			state = REPEAT;
			duration_count = 0;
		}
		break;
	case REPEAT:
		if (duration_count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	}
	duration_count++;
}