#include "Joystick.h"
#include "Modules.h"

static uint16_t duration_count = 0;
static uint8_t is_synced = 0;

static uint8_t SyncController(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	case 0 ... 49:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_L | SWITCH_R;
		break;
	case 50 ... 99:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 100:
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
#elif defined(LOOP_BATTLE_TOWER)
	LoopBattleTower_Module(ReportData);
#else
	HatchEggs_Module(ReportData);
#endif
}
