/*2012(c)����� ������� ��������*/
#include "panelclass.h" // ������������ ���� ������

// �������� ������ ������������
HWND PanelClass::CreateToolBar(HWND hwnd, DWORD dwStyle, UINT uCom)
{
    static TBBUTTON but[7];             //�������� ������
    //������ �� ���� ������
    but[0].fsStyle = TBSTYLE_SEP;       //����� ������
    
    //������ ���� ������������
    but[1].iBitmap = STD_PROPERTIES;    //����� ������ � �������
    but[1].idCommand=CM_TOOLS_WINTOOLS; //������������� �������
    but[1].fsState=TBSTATE_ENABLED;     //���� ��������� ���������
    but[1].fsStyle=TBSTYLE_GROUP;       //����� ������
    
    //������ ���� �����������
    but[2].iBitmap = STD_FILENEW;
    but[2].idCommand=CM_TOOLS_NEWJOB;
    but[2].fsState=TBSTATE_ENABLED;
    but[2].fsStyle=TBSTYLE_GROUP;
    
    //������
    but[3].fsStyle = TBSTYLE_SEP;
    
    //������ �������� �����
    but[4].iBitmap = STD_FILEOPEN;
    but[4].idCommand=CM_FILE_OPEN;
    but[4].fsState=TBSTATE_ENABLED;
    but[4].fsStyle=TBSTYLE_GROUP;

    //������ ���������� � ����
    but[5].iBitmap = STD_FILESAVE;
    but[5].idCommand=CM_FILE_SAVE;
    but[5].fsState=TBSTATE_ENABLED;
    but[5].fsStyle=TBSTYLE_GROUP;
    
    //������ � ���������    
    but[6].iBitmap = STD_HELP;
    but[6].idCommand=CM_ABOUT;
    but[6].fsState=TBSTATE_ENABLED;
    but[6].fsStyle=TBSTYLE_GROUP;
    
    //�������� ������ ������������
    return CreateToolbarEx(hwnd,        //���������� ������������� ���� ������
                 dwStyle,               //����� ������
                 uCom,                  //������������� ������
                 0,                     //���������� ����������� ������ � ����������
                 HINST_COMMCTRL,        //���������� ���������� ����������
                 IDB_STD_SMALL_COLOR,   //������������� �������������� ������� ������
                 but,                   //��������� �� ������ ��������� ���� TBBUTTON
                 7,                     //���������� ������ ������ ������������
                 0,                     //������ ������ � ��������
                 0,                     //������ ������ � ��������
                 0,                     //������ ����������� ������ � ��������
                 0,                     //������ ����������� � ��������
                 sizeof(TBBUTTON));     //������ ��������� TBBUTTON	
}


