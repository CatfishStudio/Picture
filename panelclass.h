/*2012(c)����� ������� ��������*/
#ifndef PANELCLASS_H
#define PANELCLASS_H

#include <windows.h>
#include <commctrl.h>
#include "menuclass.h" // ������������ ���� ������ ����

#define ID_TOOLBAR 100 // ��������� ������ ������������

class PanelClass
{
	public:
		// �������� ������� ������
		HWND CreateToolBar(HWND hwnd, DWORD dwStyle, UINT uCom);
		
};

#endif // PANELCLASS_H
