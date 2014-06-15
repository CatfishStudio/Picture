/*2012(c)����� ������� ��������*/
#include <windows.h>
#include "menuclass.h" // ������������ ���� ������

//�������� ����---------------------------------------------------
BOOL MenuClass::CreateMenuItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, HMENU hSubMenu,
                          BOOL flag, UINT fType)
{
     MENUITEMINFO mii;
     //������ ���������, � ������.
     mii.cbSize = sizeof(MENUITEMINFO);
     //��������� ��� ������������� �����.
     mii.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
     //��� ������ ����.
     mii.fType = fType;
     //��������� ������ ����.
     mii.fState = MFS_ENABLED;
     //���������� ������ ����.
     mii.dwTypeData = str;
     //����� ������ ������ ����.
     mii.cch = sizeof(str);
     //16-������� ��������, ������� �������������� ����� ����.
     mii.wID = uCom;
     //���������� ��������� �������
     mii.hSubMenu = hSubMenu;
     //��������� ����� ����� ���� � �������� ������� � ����.
     return InsertMenuItem(hMenu, uIns, flag, &mii);
}

