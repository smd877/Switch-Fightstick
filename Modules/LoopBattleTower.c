/*
 * Commands:
 *   AA (wait 17sec) AA UP AA UP AAA (wait 17sec) AABB (wait 0.8sec) UP
 * Rental Team ID:
 *   0000-0006-15Y4-3R
 * References:
 *   - https://twitter.com/satoon_sugar/status/1208248084653674496
 *   - https://twitter.com/satoon_sugar/status/1208253657470226432
 */

#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;

void LoopBattleTower_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (duration_count) {
	case 0 ... 199:
		/* AA */
		if (duration_count % 100 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 200 ... 2299:
		/* wait 17sec */
		break;
	case 2300 ... 2499:
		/* AA */
		if (duration_count % 100 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 2500 ... 2599:
		/* UP */
		if (duration_count % 100 < 25)
			ReportData->HAT = HAT_TOP;
		break;
	case 2600 ... 2799:
		/* AA */
		if (duration_count % 100 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 2800 ... 2899:
		/* UP */
		if (duration_count % 100 < 25)
			ReportData->HAT = HAT_TOP;
		break;
	case 2900 ... 3199:
		/* AAA */
		if (duration_count % 100 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 3200 ... 5299:
		/* wait 17sec */
		break;
	case 5300 ... 5499:
		/* AA */
		if (duration_count % 100 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 5500 ... 5699:
		/* BB */
		if (duration_count % 100 < 25)
			ReportData->Button |= SWITCH_B;
		break;
	case 5700 ... 5799:
		/* wait 0.8sec */
		break;
	case 5800 ... 5899:
		/* UP */
		if (duration_count % 100 < 25)
			ReportData->HAT = HAT_TOP;
		break;
	case 5900:
		duration_count = 0;
		return;
	}
	duration_count++;
}
