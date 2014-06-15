/*2012(c)����� ������� ��������*/
#include <windows.h>
#include "menuclass.h"
#include "panelclass.h"

#define ID_CHILDWINDOW 1000

#define DLG_VERFIRST        400
#define DLG_VERLAST         404

#define ID_BUTTON1 501
#define ID_BUTTON2 502
#define ID_BUTTON3 503
#define ID_BUTTON4 504
#define ID_BUTTON5 505

#define ID_BUTTON6 506
#define ID_BUTTON7 507
#define ID_BUTTON8 508
#define ID_BUTTON9 509
#define ID_BUTTON10 510


//�������� �������: ������� ����...................
LRESULT CALLBACK Event_Form_Programm(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Event_Form_Job(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Event_Form_Panel_Job(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
//������� �������� ����............................
BOOL CreateProgramMenu(HWND);
//.................................................

//�������� ����������..............................
HINSTANCE hInst; //������� ���������
//...������� ���� ����������
char szClassFormProgram[ ] = "Form_Programm";
char szTitleFormProgram[ ] = "2012(c)Picture. �������� �������� ��� ��. �.���� ��.: ���-401 ������ �.�.";
//...���� �������..................................
char szClassFormJob[ ] = "Form_Job";
char szTitleFormJob[ ] = "³��� ����������:";
//...���� ������ ������������ ���������............
char szClassFormPanelJob[ ] = "Form_PanelJob";
char szTitleFormPanelJob[ ] = " ";

//����������� ����.................................
HWND hWndClient = NULL; //���������� ������� ��� �������� MDI ����
HWND hWndJob = NULL;    //���������� ���� ������ � ������������
HWND hPanelJob = NULL;  //���������� ���� ������������
//.................................................

//...������� ��������� ���� ����������.............
bool ActionWndJob = FALSE;      //���� ������ � ������������
bool ActionWndPanelJob = FALSE; //���� ������������
//...������� ����������� ������ ������������.......
bool ActionCircle = FALSE;      //������ ����
bool ActionEllipse = FALSE;     //������ ������
bool ActionSquare = FALSE;      //������ �������
bool ActionRectangle = FALSE;   //������ �������������
bool ActionLine = FALSE;        //������ �����
bool ActionBlack = FALSE;       //������ ������ ����
bool ActionRed = FALSE;         //������ ������� ����
bool ActionCyan = FALSE;        //������ ����� ����
bool ActionGreen = FALSE;       //������ ������� ����
bool ActionYellow = FALSE;      //������ ������ ����

//...��������� ������� ���� � ���� ������ � ������������
WORD xPosDown, yPosDown; //���������� ��� ������� ������
WORD xPosUp, yPosUp;     //���������� ��� ������� ������

//...������........................................
HWND hButton1, hButton2, hButton3, hButton4, hButton5;
HWND hButtonBlack, hButtonRed, hButtonCyan, hButtonGreen, hButtonYellow;
//...���� ����.....................................
HPEN hPenBlack, hPenRed, hPenCyan, hPenGreen, hPenYellow;

//���������� ���������� ������.....................
MenuClass Menu;   //��������� ���������� ������ �������� ����
PanelClass Panel; //��������� ���������� ������ �������� ������
//.................................................

//���������� ����: ������� � ��������� ����........
OPENFILENAME ofn;
TCHAR szFile[20000]="";
TCHAR szFileTitle[20000]="";
void OpenDialog(HWND); //����������� ����
void LoadFile(HWND); //���������� ���� �������� �����
void SaveFile(HWND); //���������� ���� ���������� �����
//.................................................

//��������� �����������............................
RECT WindowJobSize; //������ �������� ���� (���� �������������� �����������)
PAINTSTRUCT paintStruct;
HDC winDC,  //�������� ����
	cwinDC, //�������� � ������ (����� ����) - ��������� ����� ���������� ����������� � ����� - �� ��� ����� �������� ��
	fonDC;  //�������� � ������� ��������
HBITMAP bmpFon, //����� ��� �������� ��������-����
    bmpMem, //������, � ������� ����� ��������� ����� ���������� �������
	bmpTemp;//��������� �����
void SaveBMP (HWND); //���������� ������� � ����
void InitGraphics(HWND); //������������� ����������� ������� ����
void ClearGraphics();//�������
//.................................................

//�������� �������� ��������� ���� "�������" � "���������" ---------------
void LoadFile(HWND hwnd)
{
 OpenDialog(hwnd);
 if(GetOpenFileName(&ofn))
  {
       HDC tempDC = GetDC (hwnd); //����������� �������� ���� (����� ������� �� ��� ����� ��� ����)
	   cwinDC = CreateCompatibleDC (tempDC); //��������-��������� ����� ���������� ����������� � �����
	   fonDC = CreateCompatibleDC (tempDC); //��������� �������� ��� �������� ����������� ����
	   
	   //���������� ������ �������� ����.
	   GetWindowRect(hwnd, &WindowJobSize); //& �������� ��������� ��� ������

	   //��������� ��������
	   bmpFon = (HBITMAP)LoadImage (NULL, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	   //������� ������ ������ ��� �������� ���� ������� (�.�. ��� �������� ��� �� ������)
	   //������ � ���� ������� �� ����� ��������
	   bmpMem = CreateCompatibleBitmap (tempDC, WindowJobSize.right, WindowJobSize.bottom);
       ReleaseDC (hwnd, tempDC); //��������� �������� ����
       bmpTemp = (HBITMAP)SelectObject (fonDC, bmpFon); //������������ ������ � ���������
	   if (bmpTemp) DeleteObject (bmpTemp);
	   bmpTemp = (HBITMAP)SelectObject (cwinDC, bmpMem);
       if (bmpTemp) DeleteObject (bmpTemp);
       //��������� ����������� ��������
	   StretchBlt (cwinDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, fonDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, SRCCOPY);
       winDC = BeginPaint (hwnd, &paintStruct);
			StretchBlt (
				winDC,
				WindowJobSize.left,
				WindowJobSize.top,
				WindowJobSize.right,
				WindowJobSize.bottom,
				cwinDC,
				WindowJobSize.left,
				WindowJobSize.top,
				WindowJobSize.right,
				WindowJobSize.bottom,
				SRCCOPY
		);
		EndPaint (hwnd, &paintStruct);
		//�������� ��������� WM_PAINT � � �����������.
		InvalidateRect (hwnd, NULL, false);
		UpdateWindow(hWndJob);
  }
 }
//���������� ���� ���������� --------------------------------------------------
void SaveFile(HWND hwnd)
 {
 OpenDialog(hwnd);
 if(GetSaveFileName(&ofn))
  {
        strcat(szFile, ".bmp"); //������������ �����, � ����� ����� ��������� .bmp
        SaveBMP(hwnd);          //��������� ���������� ����������� � ����
        MessageBox(hwnd, "���� ������ ����������!", "�����������:", MB_OK);
  }
}
//���������� ���� �������� ----------------------------------------------------
void OpenDialog(HWND hwnd1)
{
 ZeroMemory(&ofn, sizeof(ofn));
 ofn.lStructSize = sizeof(ofn);
 ofn.lpstrFile = szFile;
 ofn.lpstrFile[0] = '\0';
 ofn.lpstrFileTitle = szFileTitle;
 ofn.lpstrFileTitle[0] = '\0';
 ofn.hwndOwner = hwnd1;
 ofn.nMaxFile = sizeof(szFile);
 ofn.nMaxFileTitle = sizeof(szFileTitle);
 ofn.lpstrFilter =  "���� ���������� *.bmp\0*.bmp\0\0";
 ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
 ofn.nFilterIndex = 1;
 }
//--���������� � ���� BMP ----------------------------------------------------
void SaveBMP (HWND hwnd) {
	BITMAPFILEHEADER bfh;  //��������� � ���������� �����
	BITMAPINFOHEADER bih;  //��������� � ��������� ������� ��������
	BITMAPINFO bi;	       //�������� ������� ��� ������� GetDIBits ()
	void *pdwBits = NULL;  //��������� �� ����� � ������� ��������
	DWORD dwWB = 0;        //���������� ��� �������� ���������� ���� � ����
	HANDLE hFile = NULL;   //����� ��������� �����

	//������� ������ �����, � ������� ����� ����������� ��������
	pdwBits = (void *)GlobalAlloc (GMEM_FIXED, WindowJobSize.right * WindowJobSize.bottom * 4);

	//�������� ���������
	memset (&bfh, 0, sizeof (BITMAPFILEHEADER));
	memset (&bih, 0, sizeof (BITMAPINFOHEADER));
	memset (&bi, 0, sizeof (BITMAPINFO));

	//��������� ������������ ���������
	bfh.bfType = 0x4D42;                           // ���������, ��� ��� bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
	// ��������� ������ ��������� �����
	bfh.bfSize = bfh.bfOffBits + WindowJobSize.right * WindowJobSize.bottom * 4;

	//��������� �������� ��������
	bih.biSize = sizeof(bih);                      // ��� ��������
	bih.biBitCount = 32;                           // 16 ��� �� �������
	bih.biCompression = BI_RGB;                    // ��� ������
	bih.biHeight = WindowJobSize.bottom;
	bih.biWidth = WindowJobSize.right;
	bih.biPlanes = 1;

	//�������� � ��������� BITMAPINFO
	CopyMemory (&bi, &bih, sizeof (BITMAPINFOHEADER));

	//�������� � ������� ������� ���� �������� �� ��������� � ������
	GetDIBits (cwinDC, bmpMem, 0, WindowJobSize.bottom, pdwBits, 
                                        (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	//������� ���� ��� ������
	hFile = CreateFile (szFile,
											GENERIC_WRITE,
											0,
											NULL,
											CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL,
											(HANDLE)NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
			if (pdwBits) GlobalFree (pdwBits);
			SetWindowText (hwnd, "������� ��� ������� �����");
			return;
		}

	//���������� ��������� � ���������� �����
	if (!WriteFile (hFile, (void *)&bfh, sizeof (BITMAPFILEHEADER), &dwWB, NULL)) {
		SetWindowText (hwnd, "������� ��� ����� BITMAPFILEHEADER");
		if (pdwBits) GlobalFree (pdwBits);
		return;
	}

	//���������� ��������� � ��������� ������� ��������
	if (!WriteFile (hFile, (void *)&bih, sizeof (BITMAPINFOHEADER), &dwWB, NULL)) {
		SetWindowText (hwnd, "������� ��� ����� BITMAPINFOHEADER");
		if (pdwBits) GlobalFree (pdwBits);
		return;
	}

	//���������� ������ ���� �������� ����� ���� ���������� ��������
	if (!WriteFile (hFile, (void *)pdwBits, 
                WindowJobSize.right * WindowJobSize.bottom * 4, &dwWB, NULL)) 
    {
		SetWindowText (hwnd, "������� ��� ����� DIBits");
		if (pdwBits) GlobalFree (pdwBits);
		return;
	}

	//��������� ����� ����� � ������� �����
	CloseHandle (hFile);
	if (pdwBits) GlobalFree (pdwBits);
	return;
}
//--������������� ����������� ����� -------------------------------------------
void InitGraphics(HWND hwnd)
{
       HDC tempDC = GetDC (hwnd); //����������� �������� ���� (����� ������� �� ��� ����� ��� ����)
	   cwinDC = CreateCompatibleDC (tempDC); //��������-��������� ����� ���������� ����������� � �����
	   fonDC = CreateCompatibleDC (tempDC); //��������� �������� ��� �������� ����������� ����

	   //���������� ������ �������� ����.
	   GetWindowRect(hwnd, &WindowJobSize); //& �������� ��������� ��� ������

	   //������� ������ ������ ��� �������� ���� ������� (�.�. ��� �������� ��� �� ������)
	   //������ � ���� ������� �� ����� ��������
	   bmpMem = CreateCompatibleBitmap (tempDC, WindowJobSize.right, WindowJobSize.bottom);
       ReleaseDC (hwnd, tempDC); //��������� �������� ����
       bmpTemp = (HBITMAP)SelectObject (fonDC, bmpFon); //������������ ������ � ���������
	   if (bmpTemp) DeleteObject (bmpTemp);
	   bmpTemp = (HBITMAP)SelectObject (cwinDC, bmpMem);
       if (bmpTemp) DeleteObject (bmpTemp);
       //����������� ������� ������ ����� ������
	   StretchBlt (cwinDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, 
            fonDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, SRCCOPY);
       winDC = BeginPaint (hwnd, &paintStruct);
			StretchBlt (
				winDC,
				WindowJobSize.left,
				WindowJobSize.top,
				WindowJobSize.right,
				WindowJobSize.bottom,
				cwinDC,
				WindowJobSize.left,
				WindowJobSize.top,
				WindowJobSize.right,
				WindowJobSize.bottom,
				SRCCOPY
		);
		RECT lprc;
        lprc.left = 0;
        lprc.top = 0;
        lprc.right = WindowJobSize.right;
        lprc.bottom = WindowJobSize.bottom;
		FillRect(cwinDC, &lprc, (HBRUSH)(RGB(255,255,255)));
		EndPaint (hwnd, &paintStruct);
       //�������� ��������� WM_PAINT � � �����������.
	   InvalidateRect (hwnd, NULL, false);        
}
//--������� -------------------------------------------------------------------
void ClearGraphics()
{
    winDC = NULL;
    cwinDC = NULL;
    fonDC = NULL;
    bmpFon = NULL;
    bmpMem = NULL;
    bmpTemp = NULL;
}
