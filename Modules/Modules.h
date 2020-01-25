#ifndef _MODULES_H_
#define _MODULES_H_

#ifndef BOX_NUMBER
	/* Default 1 box (30 pokemons) */
	#define BOX_NUMBER 1
#endif
#define	MAX_EGG_COUNT		(BOX_NUMBER * 30)
#define LIMIT_BOX_NUMBER	32
#define LIMIT_EGG_COUNT		(LIMIT_BOX_NUMBER * 30)

extern void HatchEggs_Module(USB_JoystickReport_Input_t* const ReportData);
extern void LoopTournament_Module(USB_JoystickReport_Input_t* const ReportData);
extern void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData);
extern void ReleasePokemons_Module(USB_JoystickReport_Input_t* const ReportData);
extern void LoopBattleTower_Module(USB_JoystickReport_Input_t* const ReportData);
extern void MagicalTrade_Module(USB_JoystickReport_Input_t* const ReportData);

#endif
