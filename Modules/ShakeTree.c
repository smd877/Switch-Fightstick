#include "Joystick.h"
#include "Modules.h"

typedef enum {
	INIT,
	TOKIWATARI,
	DONE,
} State_t;

static State_t state = INIT;
static uint16_t duration_count = 0;

static uint8_t Initial(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 199:
		if (count % 40 > 20) {
			/* Push A */
			ReportData->Button |= SWITCH_A;
		}
		break;
	case 200 ... 1299:
		if (count % 40 > 20) {
			/* Push B */
			ReportData->Button |= SWITCH_B;
		}
		break;
	case 1300:
		return 1;
	}
	return 0;
}

void ShakeTree_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case INIT:
		if (Initial(ReportData, duration_count)) {
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
