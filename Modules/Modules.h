#ifndef _MODULES_H_
#define _MODULES_H_

#ifndef BOX_NUMBER
	/* Default 1 box (30 pokemons) */
	#define BOX_NUMBER 1
#endif
#define	MAX_EGG_COUNT		(BOX_NUMBER * 30)
#define LIMIT_BOX_NUMBER	32
#define LIMIT_EGG_COUNT		(LIMIT_BOX_NUMBER * 30)
#ifndef TARGET_NUM
	#define TARGET_NUM 0
#endif
#ifndef EFFORT_H
	#define EFFORT_H 0
#endif
#ifndef EFFORT_A
	#define EFFORT_A 0
#endif
#ifndef EFFORT_B
	#define EFFORT_B 0
#endif
#ifndef EFFORT_C
	#define EFFORT_C 0
#endif
#ifndef EFFORT_D
	#define EFFORT_D 0
#endif
#ifndef EFFORT_S
	#define EFFORT_S 0
#endif

extern void HatchEggs_Module(USB_JoystickReport_Input_t* const ReportData);
extern void LoopTournament_Module(USB_JoystickReport_Input_t* const ReportData);
extern void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData);
extern void ReleasePokemons_Module(USB_JoystickReport_Input_t* const ReportData);
extern void LoopBattleTower_Module(USB_JoystickReport_Input_t* const ReportData);
extern void OnlyHatchEggs_Module(USB_JoystickReport_Input_t* const ReportData);
extern void MagicalTrade_Module(USB_JoystickReport_Input_t* const ReportData);
extern void PokeJob_Module(USB_JoystickReport_Input_t* const ReportData);
extern void GiveEffort_Module(USB_JoystickReport_Input_t* const ReportData);

#endif
