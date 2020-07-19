#include "Joystick.h"
#include "Modules.h"

uint8_t Tokiwatari(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 9:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 70 ... 79:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 80 ... 159:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 160 ... 169:
		/* Move left */
		ReportData->HAT = HAT_LEFT;
		break;
	case 170 ... 179:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 200 ... 439:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 440 ... 449:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 455 ... 464:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 470 ... 479:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 485 ... 494:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 500 ... 509:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 515 ... 524:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 545 ... 554:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 560 ... 569:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 575 ... 584:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 605 ... 614:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 620 ... 629:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 635 ... 644:
		/* Move top */
		ReportData->HAT = HAT_TOP;
		break;
	case 650 ... 659:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 665 ... 674:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 680 ... 689:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 695 ... 704:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 745 ... 754:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 855 ... 864:
		/* Push HOME */
		ReportData->Button |= SWITCH_HOME;
		break;
	case 1000:
		return 1;
	}
	return 0;
}