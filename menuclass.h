/*2012(c)����� ������� ��������*/
#ifndef MENUCLASS_H
#define MENUCLASS_H

#define CM_FILE_OPEN 1001       //��������� ���� ��������
#define CM_FILE_SAVE 1002       //��������� ���� ����������
#define CM_FILE_QUIT 1003       //��������� ���� �����
#define CM_TOOLS_NEWJOB 2001    //��������� ���� ���� �����������
#define CM_TOOLS_WINTOOLS 2002  //��������� ���� ���� ������������
#define CM_ABOUT 2003           //��������� ���� � ���������


#define CM_CIRCLE 2004          //��������� ���� ����
#define CM_ELLIPSE 2005         //��������� ���� ������
#define CM_SQUARE 2006          //��������� ���� �������
#define CM_RECTANGLE 2007       //��������� ���� �������������
#define CM_LINE 2008            //��������� ���� �����

#define CM_BLACK 2011           //��������� ���� ���� ������
#define CM_RED 2012             //��������� ���� ���� �������
#define CM_CYAN 2013            //��������� ���� ���� �����
#define CM_GREEN 2014           //��������� ���� ���� �������
#define CM_YELLOW 2015          //��������� ���� ���� ������

#define CM_CLEARJOB 2016        //��������� ���� �������� �������

#define IDM_CASCADE 3001        //��������� ���� ���: ������
#define IDM_TILEHORZ 3002       //��������� ���� ���: �������������� ������
#define IDM_TILEVERT 3003       //��������� ���� ���: ������������ ������

class MenuClass
{
	public:
		// �������� ������� ������
		BOOL CreateMenuItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, HMENU hSubMenu,
                          BOOL flag, UINT fType);
		
};

#endif // MENUCLASS_H
