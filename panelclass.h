/*2012(c)Сомов Евгений Павлович*/
#ifndef PANELCLASS_H
#define PANELCLASS_H

#include <windows.h>
#include <commctrl.h>
#include "menuclass.h" // заголовочный файл класса меню

#define ID_TOOLBAR 100 // константа панели инструментов

class PanelClass
{
	public:
		// Описание функции класса
		HWND CreateToolBar(HWND hwnd, DWORD dwStyle, UINT uCom);
		
};

#endif // PANELCLASS_H
