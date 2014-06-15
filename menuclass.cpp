/*2012(c)Сомов Евгений Павлович*/
#include <windows.h>
#include "menuclass.h" // заголовочный файл класса

//Создание меню---------------------------------------------------
BOOL MenuClass::CreateMenuItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, HMENU hSubMenu,
                          BOOL flag, UINT fType)
{
     MENUITEMINFO mii;
     //Размер структуры, в байтах.
     mii.cbSize = sizeof(MENUITEMINFO);
     //Извлекает или устанавливает члены.
     mii.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
     //Тип пункта меню.
     mii.fType = fType;
     //Состояние пункта меню.
     mii.fState = MFS_ENABLED;
     //Содержание пункта меню.
     mii.dwTypeData = str;
     //Длина текста пункта меню.
     mii.cch = sizeof(str);
     //16-битовое значение, которое идентифицирует пункт меню.
     mii.wID = uCom;
     //Дескриптор точечного рисунка
     mii.hSubMenu = hSubMenu;
     //вставляет новый пункт меню в заданной позиции в меню.
     return InsertMenuItem(hMenu, uIns, flag, &mii);
}

