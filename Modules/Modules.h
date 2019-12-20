#ifndef _MODULES_H_
#define _MODULES_H_

#define SYNC_CONTROLLER		0
#define RESET_POSITION_1	1
#define HATCH_EGG			2
#define RESET_POSITION_2	3
#define GET_EGG				4
#define PUT_POKEMON_IN_BOX	5
#define REPEAT				6
#define DONE				7

extern uint8_t SyncController(USB_JoystickReport_Input_t* const ReportData, uint16_t count);
extern void HatchEggs_Module(USB_JoystickReport_Input_t* const ReportData);
extern void LoopTournament_Module(USB_JoystickReport_Input_t* const ReportData);
extern void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData);

#endif