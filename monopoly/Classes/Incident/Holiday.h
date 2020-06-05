#ifndef _HOLIDAY_H_
#define _HOLIDAY_H_

#include "Character/Character.h"
#include "Scene/MapScene.h"

//送去度假
bool GoOnHoliday(Character* character);
//弹出还有几天度假回来或者已度假回来的对话框
void PopUpHolidayDialog(Character* character, MapScene* map_scene);

#endif