#include "Joystick.h"
#include "Modules.h"

uint8_t Tokiwatari(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
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
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 1065 ... 1074:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1115 ... 1124:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 1225 ... 1234:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 1385:
		return 1;
	}
	return 0;
}
