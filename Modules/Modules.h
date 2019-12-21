#ifndef _MODULES_H_
#define _MODULES_H_

extern uint8_t SyncController(USB_JoystickReport_Input_t* const ReportData, uint16_t count);
extern void HatchEggs_Module(USB_JoystickReport_Input_t* const ReportData);
extern void LoopTournament_Module(USB_JoystickReport_Input_t* const ReportData);
extern void RepeatA_Module(USB_JoystickReport_Input_t* const ReportData);

#endif