#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;
static uint8_t is_synced = 0;

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

	if (!is_synced) {
		if (SyncController(ReportData, duration_count))
			is_synced = 1;
		duration_count++;
		return;
	}

#if defined(LOOP_TOURNAMENT)
	LoopTournament_Module(ReportData);
#elif defined(REPEAT_A)
	RepeatA_Module(ReportData);
#elif defined(RELEASE_POKEMONS)
	ReleasePokemons_Module(ReportData);
#else
	HatchEggs_Module(ReportData);
#endif
}
