#include "Joystick.h"
#include "Modules.h"

typedef enum {
	RESET_POSITION,
	NEXT_BOX,
	MOVE_BOTTOM,
	MOVE_RIGHT,
	TRADE_START,
	TRADE_FINISH,
	DONE,
} State_t;

static State_t state = RESET_POSITION;
static uint16_t duration_count = 0;
static uint16_t trade_count = 0;
static uint16_t cursor = 0;

static uint8_t ResetPosition(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Open YY Communication */
		ReportData->Button |= SWITCH_Y;
		break;
	case 200 ... 224:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 250 ... 274:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 500:
		return 1;
	}
	return 0;
}

static uint8_t NextBox(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push R */
		ReportData->Button |= SWITCH_R;
		break;
	case 50:
		return 1;
	}
	return 0;
}

static uint8_t MoveBottom(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Move bottom */
		ReportData->HAT = HAT_BOTTOM;
		break;
	case 50:
		return 1;
	}
	return 0;
}

static uint8_t MoveRight(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Move right */
		ReportData->HAT = HAT_RIGHT;
		break;
	case 50:
		return 1;
	}
	return 0;
}

static uint8_t TradeStart(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 100 ... 124:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 650 ... 674:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 700 ... 724:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 750 ... 774:
		/* Push A */
		ReportData->Button |= SWITCH_A;
		break;
	case 1000 ... 1999:
		if (count % 100 < 25)
			/* Push B (salvage) */
			ReportData->Button |= SWITCH_B;
		break;
	case 4800:
		return 1;
	}
	return 0;
}

static uint8_t TradeFinish(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 25 ... 49:
		/* Push Y */
		ReportData->Button |= SWITCH_Y;
		break;
	case 800 ... 824:
		/* Push Y (salvage) */
		ReportData->Button |= SWITCH_Y;
		break;
	case 1000 ... 1999:
		if (count % 100 < 25)
			/* Push B (salvage) */
			ReportData->Button |= SWITCH_B;
		break;
	case 2850:
		return 1;
	}
	return 0;
}
void MagicalTrade_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case RESET_POSITION:
		if (ResetPosition(ReportData, duration_count)) {
			state = NEXT_BOX;
			duration_count = 0;
			cursor = 0;
		}
		break;
	case NEXT_BOX:
		if ((trade_count / 30 > 0) && (trade_count % 30 == 0)) {
			if (NextBox(ReportData, duration_count)) {
				state = MOVE_BOTTOM;
				duration_count = 0;
			}
			break;
		}
		state = MOVE_BOTTOM;
		cursor = 0;
		break;
	case MOVE_BOTTOM:
		if (!((trade_count % 30) / 6 == cursor)) {
			if (MoveBottom(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		state = MOVE_RIGHT;
		cursor = 0;
		break;
	case MOVE_RIGHT:
		if (!((trade_count % 30) % 6 == cursor)) {
			if (MoveRight(ReportData, duration_count)) {
				cursor++;
				duration_count = 0;
			}
			break;
		}
		state = TRADE_START;
		cursor = 0;
		break;
	case TRADE_START:
		if (TradeStart(ReportData, duration_count)) {
			state = TRADE_FINISH;
			duration_count = 0;
		}
		break;
	case TRADE_FINISH:
		if (TradeFinish(ReportData, duration_count)) {
			trade_count++;
			duration_count = 0;
			if (trade_count == MAX_EGG_COUNT || trade_count == LIMIT_EGG_COUNT)
				state = DONE;
			else
				state = RESET_POSITION;
		}
		break;
	case DONE:
		break;
	}
	duration_count++;
}
