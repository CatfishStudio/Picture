/*2012(c)����� ������� ��������*/
#include "picture.h"

/*=================================================
��������� ���� ����������:                        /
1. ������� ���� ���������� (FormProgramm)         /
2. ���� ������ � ������������ (FormJob)           /
3. ���� ������������ (FormPanelJob)               /
4. ���������� ���� "������� ����"                 /
5. ���������� ���� "��������� ����"               /
6. ���������� ���� "� ���������"                  /
=================================================*/

//==������� ������� ����������=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hwnd;
    WNDCLASSEX wc;
    
   // ����������� ��������� ������ ���� ����������.
   //............................................
   wc.style         = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc   = (WNDPROC)Event_Form_Programm;
   wc.cbClsExtra    = 0;
   wc.cbWndExtra    = 0;
   wc.hInstance     = hInstance;
   wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
   wc.lpszMenuName  = szClassFormProgram;
   wc.lpszClassName = szClassFormProgram;
   wc.cbSize        = sizeof( WNDCLASSEX );
   wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

   //����������� ������ ����
   if ( !RegisterClassEx( &wc ) )
      return( FALSE );

   // ���������������� ����� ���� ���������.
   //.....................................................
   wc.style         = CS_CLASSDC;
   wc.lpfnWndProc   = (WNDPROC)Event_Form_Job;
   wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wc.lpszMenuName  = NULL;
   wc.lpszClassName = szClassFormJob;
   wc.cbSize        = sizeof( WNDCLASSEX );
   wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

   //����������� ������ ����
   if ( !RegisterClassEx( &wc ) )
      return( FALSE );
      
   // ���������������� ����� ���� ������������.
   //.....................................................
   wc.lpfnWndProc   = (WNDPROC)Event_Form_Panel_Job;
   wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
   wc.lpszMenuName  = NULL;
   wc.lpszClassName = szClassFormPanelJob;
   wc.cbSize        = sizeof( WNDCLASSEX );
   wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

   //����������� ������ ����
   if ( !RegisterClassEx( &wc ) )
      return( FALSE );
   
   //.....................................................
   hInst = hInstance;

   //�������� �������� ���� ���������
   hwnd = CreateWindow(szClassFormProgram,
						szTitleFormProgram,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						0,
						CW_USEDEFAULT,
						0,
						NULL,
						NULL,
						hInstance,
						NULL);

	if(!hwnd) return FALSE;

    ShowWindow(hwnd, nCmdShow); //���������� ����
    UpdateWindow(hwnd); //������������(��������) ����

    while( GetMessage( &msg, NULL, 0, 0) )
    {
      if ( hWndClient && TranslateMDISysAccel( hWndClient, &msg ) )
         continue;

      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
    return msg.wParam;
}
//=============================================================================
//�������� ������� �������� ����-----------------------------------------------
LRESULT CALLBACK Event_Form_Programm(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hToolbar; //������ ������������.
    switch(msg) //��������� ��������� ����
	{
        case WM_CREATE: //������� ����������� ��� ������ �������� ����
        {
             //������� �������� ���� ��������� -------------------------
             CreateProgramMenu(hwnd);
             //�������� ������ ������������.----------------------------
             DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_DLGFRAME;
             hToolbar = Panel.CreateToolBar(hwnd, dwStyle, ID_TOOLBAR);
             
             //��������� ���� ����--------------------------------------
             CLIENTCREATESTRUCT ccs;
             ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 4); //2-���� � ���� ���
             ccs.idFirstChild = ID_CHILDWINDOW;
             
             //�������� ����������� ���� MDI ---------------------------
             hWndClient = CreateWindowEx(WS_EX_CLIENTEDGE,
                                          "MDICLIENT", NULL,
                                          WS_CHILD | WS_CLIPSIBLINGS,
                                          0,
                                          0,
                                          0,
                                          0,
                                          hwnd, (HMENU)0xCA0, hInst, &ccs);

             ShowWindow(hWndClient, SW_SHOW); //�������� ����
             UpdateWindow(hWndClient); //�������� (������������) ����
             //--------------------------------------------------------
             //������� ���� ������ ������������ ��� ���������.---------
             hPanelJob = CreateMDIWindow((LPTSTR)szClassFormPanelJob,
                                         szTitleFormPanelJob, 0L,
                                         5,
                                         50, 
                                         100,
                                         410,
                                         hWndClient, hInst, 0L);
             
             ShowWindow(hPanelJob, SW_SHOW); //�������� ����
             UpdateWindow(hPanelJob); //�������� (������������) ����
             //--������ � ���� ������������ ���������------------------
             CreateWindow("button", "�����������:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,5,110,200, hPanelJob, (HMENU)0, hInst, NULL);
             hButton1 = CreateWindow("button", "����",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,30,90,30, hPanelJob,(HMENU)ID_BUTTON1,
                          hInst, NULL);
             hButton2 = CreateWindow("button", "����",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,65,90,30, hPanelJob,(HMENU)ID_BUTTON2,
                          hInst, NULL);
             hButton3 = CreateWindow("button", "�������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,100,90,30, hPanelJob,(HMENU)ID_BUTTON3,
                          hInst, NULL);
             hButton4 = CreateWindow("button", "��������.",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,135,90,30, hPanelJob,(HMENU)ID_BUTTON4,
                          hInst, NULL);
             hButton5 = CreateWindow("button", "˳��.",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,170,90,30, hPanelJob,(HMENU)ID_BUTTON5,
                          hInst, NULL);
             CreateWindow("button", "����:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,200,110,170, hPanelJob, (HMENU)0, hInst, NULL);
             hButtonBlack = CreateWindow("button", "������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,220,90,25, hPanelJob,(HMENU)ID_BUTTON6,
                          hInst, NULL);
             hButtonRed = CreateWindow("button", "��������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,250,90,25, hPanelJob,(HMENU)ID_BUTTON7,
                          hInst, NULL);
             hButtonCyan = CreateWindow("button", "����",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,280,90,25, hPanelJob,(HMENU)ID_BUTTON8,
                          hInst, NULL);
             hButtonGreen = CreateWindow("button", "�������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,310,90,25, hPanelJob,(HMENU)ID_BUTTON9,
                          hInst, NULL);
             hButtonYellow = CreateWindow("button", "������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,340,90,25, hPanelJob,(HMENU)ID_BUTTON10,
                          hInst, NULL);
             //����������� ������ "�������������"
             SendMessage(hButton4, BM_SETSTATE, TRUE, 0L);
             SendMessage(hButtonBlack, BM_SETSTATE, TRUE, 0L);
             ActionRectangle = TRUE;//�������� �� ��������� "�������������"
             ActionBlack = TRUE;    //�������� �� ��������� "������"
             //���� ������������ ������� 
             ActionWndPanelJob = TRUE; //���� �������
             //--------------------------------------------------------
             //�������� ���� ������� ----------------------------------
             hWndJob = CreateMDIWindow((LPTSTR)szClassFormJob,
                                         szTitleFormJob, 0L,
                                         150,
                                         50,
                                         500,
                                         400,
                                         hWndClient, hInst, 0L);
            
             ShowWindow(hWndJob, SW_SHOW); //�������� ����
             UpdateWindow(hWndJob); //�������� (������������) ����
             InitGraphics(hWndJob); //������������� ����������� �����������
             ActionWndJob = TRUE;   //���� �������
             //---------------------------------------------------------
             return 0;
        }
        //��� ��������� ������� ���� ----
        case WM_SIZE:
        {
            //������ ������� ���� �������� ������� ������� �������� ���� ���������.
            MoveWindow(hWndClient, 0, 0, LOWORD(lParam),
                                            HIWORD(lParam), TRUE );
            //��������� �������� ������ ������������.
            MoveWindow(hToolbar, 0, 0, LOWORD(lParam),
                                            HIWORD(lParam), TRUE );
            return 0;
            
        }
        //--��������� ���� --------------
        case WM_COMMAND:
        {
             switch (LOWORD(wParam))
             {
                    case CM_FILE_OPEN: //������� �����������
                    {
                         LoadFile(hWndJob);
                         return 0;
                    }
                    case CM_FILE_SAVE: //��������� �����������
                    {
                         SaveFile(hwnd);
                         return 0;
                    }
                    case CM_FILE_QUIT: //����� �� ���������
                    {
                         DestroyWindow( hwnd );
                         return 0;
                    }
                    case CM_TOOLS_WINTOOLS: //���� ������������
                    {
                        //�������� �� ��� ��������� ����
                        if(ActionWndPanelJob == TRUE){
                           return 0;
                         } 
                         //������� ���� ������ ������������ ��� ���������.---------
                         hPanelJob = CreateMDIWindow((LPTSTR)szClassFormPanelJob,
                                         szTitleFormPanelJob, 0L,
                                         5,
                                         50,
                                         100,
                                         410,
                                         hWndClient, hInst, 0L);

                         ShowWindow(hPanelJob, SW_SHOW);
                         UpdateWindow(hPanelJob);
                         //--������ � ���� ������������ ���������------------------
                         CreateWindow("button", "�����������:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,5,110,200, hPanelJob, (HMENU)0, hInst, NULL);
                         hButton1 = CreateWindow("button", "����",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,30,90,30, hPanelJob,(HMENU)ID_BUTTON1,
                          hInst, NULL);
                         hButton2 = CreateWindow("button", "����",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,65,90,30, hPanelJob,(HMENU)ID_BUTTON2,
                          hInst, NULL);
                         hButton3 = CreateWindow("button", "�������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,100,90,30, hPanelJob,(HMENU)ID_BUTTON3,
                          hInst, NULL);
                         hButton4 = CreateWindow("button", "��������.",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,135,90,30, hPanelJob,(HMENU)ID_BUTTON4,
                          hInst, NULL);
                         hButton5 = CreateWindow("button", "˳��",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,170,90,30, hPanelJob,(HMENU)ID_BUTTON5,
                          hInst, NULL);
                         CreateWindow("button", "����:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,200,110,170, hPanelJob, (HMENU)0, hInst, NULL);
                        hButtonBlack = CreateWindow("button", "������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,220,90,25, hPanelJob,(HMENU)ID_BUTTON6,
                          hInst, NULL);
                        hButtonRed = CreateWindow("button", "��������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,250,90,25, hPanelJob,(HMENU)ID_BUTTON7,
                          hInst, NULL);
                        hButtonCyan = CreateWindow("button", "����",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,280,90,25, hPanelJob,(HMENU)ID_BUTTON8,
                          hInst, NULL);
                        hButtonGreen = CreateWindow("button", "�������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,310,90,25, hPanelJob,(HMENU)ID_BUTTON9,
                          hInst, NULL);
                        hButtonYellow = CreateWindow("button", "������",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,340,90,25, hPanelJob,(HMENU)ID_BUTTON10,
                          hInst, NULL);
                        //����������� ������ "�������������"
                        SendMessage(hButton4, BM_SETSTATE, TRUE, 0L);
                        SendMessage(hButtonBlack, BM_SETSTATE, TRUE, 0L);
                        ActionRectangle = TRUE;
                        ActionBlack = TRUE;
                        //���� ������������ �������
                        ActionWndPanelJob = TRUE;
                        return 0;    
                    }
                    case CM_TOOLS_NEWJOB: //����� ���� �������������� �����������
                    {
                         //�������� �� ��� ��������� ����
                         if(ActionWndJob == TRUE){
                            MessageBox(hwnd, 
                                "³��� ����������� ���������� ��� �������, �������� ���� ��������!",
                                "�����������:", MB_OK | MB_ICONSTOP);
                            return 0;
                         }
                         //�������� ������ ���� ���������
                         hWndJob = CreateMDIWindow( (LPTSTR)szClassFormJob,
                                         szTitleFormJob, 0L,
                                         150, 50, 500, 400,
                                         hWndClient, hInst, 0L);
                    
                         ShowWindow(hWndJob, SW_SHOW);
                         UpdateWindow(hWndJob);
                         InitGraphics(hWndJob);
                         ActionWndJob = TRUE;
                         return 0;
                    }
                    case IDM_CASCADE: //������
                    {
                        CascadeWindows( hWndClient, MDITILE_SKIPDISABLED,
                                        NULL, 0, NULL );
                        return 0;
                    }
                    case IDM_TILEHORZ: //�������������� ������
                    {
                        TileWindows( hWndClient, MDITILE_HORIZONTAL,
                                     NULL, 0, NULL );
                    return 0;
                    }
                    case IDM_TILEVERT: //������������ ������
                    {
                        TileWindows( hWndClient, MDITILE_VERTICAL,
                                     NULL, 0, NULL );
                        return 0;
                    }
                    case CM_ABOUT: //���� "� ���������"
                    {
                         DialogBox( hInst, "AboutBox", hwnd, (DLGPROC)About );
                         return 0;
                    }
                    case CM_CIRCLE: //����
                    {
                        ActionCircle = TRUE;
                        ActionEllipse = FALSE;
                        ActionSquare = FALSE;
                        ActionRectangle = FALSE;
                        ActionLine = FALSE;
                        return 0;   
                    }
                    case CM_ELLIPSE: //������
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = TRUE;
                        ActionSquare = FALSE;
                        ActionRectangle = FALSE;
                        ActionLine = FALSE;
                        return 0;
                    }
                    case CM_SQUARE: //�������
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = FALSE;
                        ActionSquare = TRUE;
                        ActionRectangle = FALSE;
                        ActionLine = FALSE;
                        return 0;
                    }
                    case CM_RECTANGLE: //������������
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = FALSE;
                        ActionSquare = FALSE;
                        ActionRectangle = TRUE;
                        ActionLine = FALSE;
                        return 0;
                    }
                    case CM_LINE: //�������� �����
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = FALSE;
                        ActionSquare = FALSE;
                        ActionRectangle = FALSE;
                        ActionLine = TRUE;
                        return 0;
                    }
                    case CM_BLACK: //������ ���� ������
                    {
                        ActionBlack = TRUE;
                        ActionRed = FALSE;
                        ActionCyan = FALSE;
                        ActionGreen = FALSE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_RED: //������� ���� ������
                    {
                        ActionBlack = FALSE;
                        ActionRed = TRUE;
                        ActionCyan = FALSE;
                        ActionGreen = FALSE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_CYAN: //����� ���� ������
                    {
                        ActionBlack = FALSE;
                        ActionRed = FALSE;
                        ActionCyan = TRUE;
                        ActionGreen = FALSE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_GREEN: //������� ���� ������
                    {
                        ActionBlack = FALSE;
                        ActionRed = FALSE;
                        ActionCyan = FALSE;
                        ActionGreen = TRUE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_YELLOW: //������ ���� ������
                    {
                        ActionBlack = FALSE;
                        ActionRed = FALSE;
                        ActionCyan = FALSE;
                        ActionGreen = FALSE;
                        ActionYellow = TRUE;
                        return 0;
                    }
                    case CM_CLEARJOB: //������� ������� �����������
                    {
                        ClearGraphics();
                        InitGraphics(hWndJob);
                        UpdateWindow(hWndJob); //������������(��������) ����
		                return 0;
                    }
                    default :
                        return( DefFrameProc( hwnd, hWndClient, msg, wParam, lParam ) );
             }
             return 0;
        }
        //-------------------------------
		case WM_DESTROY:
		{
            //����������� ������ ������� ���� ������
            DeleteObject(winDC);
            DeleteObject(cwinDC);
            DeleteObject(fonDC);
            DeleteObject(bmpFon);
            DeleteObject(bmpMem);
            DeleteObject(bmpTemp);
			PostQuitMessage(0);
			return 0;
		}
		default :
            return( DefFrameProc( hwnd, hWndClient, msg, wParam, lParam ) );
	}
	return( 0L );

}
//�������� ������� ���� ��������� ----------------------------------------------
LRESULT CALLBACK Event_Form_Job( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch(uMsg)
   {
    //---------------------------------------------------
    case WM_PAINT: {
		//����������� �� ���� �� ��������� � ������ (������)
		//����� ������������ ��������� ��� �������� ������� ���������� (��� ������� � ��� ��� �������� ���� ���)
        winDC = BeginPaint (hWndJob, &paintStruct);
			     StretchBlt(winDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom,
				    cwinDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, SRCCOPY);
		EndPaint (hWndJob, &paintStruct);
		UpdateWindow(hWndJob); //������������(��������) ����
		return 0;
    }
    //---------------------------------------------------
    case WM_LBUTTONDOWN:
    {
        //�������� ���������� ������� ��� ������� ����� ������ ����
        xPosDown = LOWORD(lParam);
        yPosDown = HIWORD(lParam);
        return 0; 
    }
    //---------------------------------------------------
    case WM_LBUTTONUP:
    {
        //�������� ���������� ������� ��� ������� ����� ������ ����
        //GetCursorPos(&UpCursor); 
        xPosUp = LOWORD(lParam);
        yPosUp = HIWORD(lParam);
        //������ ������� �����������
        winDC = BeginPaint (hWndJob, &paintStruct);
		StretchBlt(winDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom,
			cwinDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, SRCCOPY);
        
        //������������ � ������ ���� -------------------
        if(ActionBlack == TRUE){
            hPenBlack = CreatePen(PS_SOLID,1,RGB(0,0,0));
            SelectObject(cwinDC, hPenBlack); 
        }
        if(ActionRed == TRUE){
            hPenRed = CreatePen(PS_SOLID,1,RGB(255,0,0));
            SelectObject(cwinDC, hPenRed);
        }
        if(ActionCyan == TRUE){
            hPenCyan = CreatePen(PS_SOLID,1,RGB(0,50,150));
            SelectObject(cwinDC, hPenCyan);
        }
        if(ActionGreen == TRUE){
            hPenGreen = CreatePen(PS_SOLID,1,RGB(0,255,0));
            SelectObject(cwinDC, hPenGreen);
        }
        if(ActionYellow == TRUE){
            hPenYellow = CreatePen(PS_SOLID,1,RGB(255,255,0));
            SelectObject(cwinDC, hPenYellow);
        }
        //----------------------------------------------
        //������ �������������
        if(ActionRectangle == TRUE){
            Rectangle(cwinDC,xPosDown,yPosDown,xPosUp,yPosUp);
        }
        //������ �������
        if(ActionSquare == TRUE){
            Rectangle(cwinDC,xPosDown,yPosDown,xPosDown+100,yPosDown+100);   
        }
        //������ ������ �����
        if(ActionLine == TRUE){
            MoveToEx(cwinDC,xPosDown,yPosDown,NULL);
            LineTo(cwinDC,xPosUp,yPosUp);
        }
        //������ ������
        if(ActionEllipse){
            Ellipse(cwinDC, xPosDown, yPosDown, xPosUp, yPosUp);    
        }
        //������ ����
        if(ActionCircle == TRUE)
        {
            Ellipse(cwinDC, xPosDown, yPosDown, xPosDown+100, yPosDown+100);    
        }
        //----------------------------------------------
        DeleteObject(hPenBlack);
        DeleteObject(hPenRed);
        DeleteObject(hPenCyan);
        DeleteObject(hPenGreen);
        DeleteObject(hPenYellow);
        //���������� �������� �����������
        EndPaint (hWndJob, &paintStruct);
        InvalidateRect (hWndJob, NULL, false);
        
        return 0;
    }
    //---------------------------------------------------
    case WM_DESTROY:
	{
	    ActionWndJob = FALSE;
	    ClearGraphics(); //������� ����������
		return 0;
	}        
      default :
            return( DefMDIChildProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}
//�������� ������� ���� ������������ -------------------------------------------
LRESULT CALLBACK Event_Form_Panel_Job( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch( uMsg )
   {
    case WM_CREATE:
    {
        return 0;      
    }    
    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
          case ID_BUTTON1:
          {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButton2, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton3, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton4, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton5, BM_SETSTATE, FALSE, 0L);
                    ActionCircle = TRUE;
                    ActionEllipse = FALSE;
                    ActionSquare = FALSE;
                    ActionRectangle = FALSE;
                    ActionLine = FALSE;
                    return 0;
           }
           case ID_BUTTON2:
           {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButton1, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton3, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton4, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton5, BM_SETSTATE, FALSE, 0L);
                    ActionCircle = FALSE;
                    ActionEllipse = TRUE;
                    ActionSquare = FALSE;
                    ActionRectangle = FALSE;
                    ActionLine = FALSE;
                    return 0;
            }
            case ID_BUTTON3:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButton1, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton2, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton4, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton5, BM_SETSTATE, FALSE, 0L);
                    ActionCircle = FALSE;
                    ActionEllipse = FALSE;
                    ActionSquare = TRUE;
                    ActionRectangle = FALSE;
                    ActionLine = FALSE;
                    return 0;
            }
            case ID_BUTTON4:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButton1, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton3, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton2, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton5, BM_SETSTATE, FALSE, 0L);
                    ActionCircle = FALSE;
                    ActionEllipse = FALSE;
                    ActionSquare = FALSE;
                    ActionRectangle = TRUE;
                    ActionLine = FALSE;
                    return 0;
            }
            case ID_BUTTON5:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButton1, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton3, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton4, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButton2, BM_SETSTATE, FALSE, 0L);
                    ActionCircle = FALSE;
                    ActionEllipse = FALSE;
                    ActionSquare = FALSE;
                    ActionRectangle = FALSE;
                    ActionLine = TRUE;
                    return 0;
            }
            case ID_BUTTON6:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButtonRed, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonCyan, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonGreen, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonYellow, BM_SETSTATE, FALSE, 0L);
                    ActionBlack = TRUE;
                    ActionRed = FALSE;
                    ActionCyan = FALSE;
                    ActionGreen = FALSE;
                    ActionYellow = FALSE;
                    return 0;    
            }
            case ID_BUTTON7:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButtonBlack, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonCyan, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonGreen, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonYellow, BM_SETSTATE, FALSE, 0L);
                    ActionBlack = FALSE;
                    ActionRed = TRUE;
                    ActionCyan = FALSE;
                    ActionGreen = FALSE;
                    ActionYellow = FALSE;
                    return 0;
            }
            case ID_BUTTON8:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButtonBlack, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonRed, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonGreen, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonYellow, BM_SETSTATE, FALSE, 0L);
                    ActionBlack = FALSE;
                    ActionRed = FALSE;
                    ActionCyan = TRUE;
                    ActionGreen = FALSE;
                    ActionYellow = FALSE;
                    return 0;
            }
            case ID_BUTTON9:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButtonBlack, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonRed, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonCyan, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonYellow, BM_SETSTATE, FALSE, 0L);
                    ActionBlack = FALSE;
                    ActionRed = FALSE;
                    ActionCyan = FALSE;
                    ActionGreen = TRUE;
                    ActionYellow = FALSE;
                    return 0;
            }
            case ID_BUTTON10:
            {
                    SendMessage((HWND)lParam, BM_SETSTATE, TRUE, 0L);
                    SendMessage(hButtonBlack, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonRed, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonCyan, BM_SETSTATE, FALSE, 0L);
                    SendMessage(hButtonGreen, BM_SETSTATE, FALSE, 0L);
                    ActionBlack = FALSE;
                    ActionRed = FALSE;
                    ActionCyan = FALSE;
                    ActionGreen = FALSE;
                    ActionYellow = TRUE;
                    return 0;
            }
        }
        return 0;
    }
    case WM_DESTROY:
	{
	    ActionWndPanelJob = FALSE;
	    ActionCircle = FALSE;
        ActionEllipse = FALSE;
        ActionSquare = FALSE;
        ActionRectangle = FALSE;
        ActionLine = FALSE;
        ActionBlack = FALSE;
        ActionRed = FALSE;
        ActionCyan = FALSE;
        ActionGreen = FALSE;
        ActionYellow = FALSE;
		return 0;
	}
      default :
            return( DefMDIChildProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}
//�������� ������� ����������� ���� "� ��������"-------------------------------
LRESULT CALLBACK About( HWND hDlg,
                        UINT message,
                        WPARAM wParam,
                        LPARAM lParam)
{
   switch (message)
   {
       case WM_INITDIALOG:
               return (TRUE);

       case WM_COMMAND:
               if (   LOWORD(wParam) == IDOK
                   || LOWORD(wParam) == IDCANCEL)
               {
                       EndDialog(hDlg, TRUE);
                       return (TRUE);
               }
               break;
   }

   return (FALSE);
}

//���������� ���� ��������-----------------------------------------------------
BOOL CreateProgramMenu(HWND hwnd)
{
    static HMENU hMainMenu, hFileMenu, hToolsMenu, hWindowMenu, hAboutMenu; //����.
    //���� ���������-------------------------------------
    hMainMenu = CreateMenu();
    //--������� ��������� ���� ��� ������� "����"
    hFileMenu = CreatePopupMenu();
    int i=0;
    Menu.CreateMenuItem(hFileMenu, "&³������ ���� *.bmp", i++, CM_FILE_OPEN,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hFileMenu, "&�������� � ���� *.bmp", i++, CM_FILE_SAVE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hFileMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hFileMenu, "&�����.", i++, CM_FILE_QUIT,
                                       NULL, FALSE, MFT_STRING);
    //--������� ��������� ���� ��� ������� "�����������"
    hToolsMenu = CreatePopupMenu();
    Menu.CreateMenuItem(hToolsMenu, "&³��� ����������", i++, CM_TOOLS_NEWJOB,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&³��� �����������", i++, CM_TOOLS_WINTOOLS,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hToolsMenu, "&����", i++, CM_CIRCLE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&����", i++, CM_ELLIPSE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&�������", i++, CM_SQUARE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&�����������", i++, CM_RECTANGLE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&˳��", i++, CM_LINE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hToolsMenu, "&����: ������", i++, CM_BLACK,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&����: ��������", i++, CM_RED,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&����: ����", i++, CM_CYAN,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&����: �������", i++, CM_GREEN,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&����: ������", i++, CM_YELLOW,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hToolsMenu, "&�������� �������.", i++, CM_CLEARJOB,
                                       NULL, FALSE, MFT_STRING);
    //--������� ��������� ���� ��� ������� "���"
    hWindowMenu = CreatePopupMenu();
    Menu.CreateMenuItem(hWindowMenu, "&�������� �������� ����.", i++, IDM_CASCADE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hWindowMenu, "&������������� ������", i++, IDM_TILEHORZ,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hWindowMenu, "&����������� ������.", i++, IDM_TILEVERT,
                                       NULL, FALSE, MFT_STRING);
    //--������� ��������� ���� ��� ������� "�������"
    hAboutMenu = CreatePopupMenu();
    Menu.CreateMenuItem(hAboutMenu, "&��� ��������.", i++, CM_ABOUT,
                                       NULL, FALSE, MFT_STRING);
    //--���������� ��������� ���� � �������� ����
    Menu.CreateMenuItem(hMainMenu, "&����", i++, 0, hFileMenu, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hMainMenu, "&�����������", i++, 0, hToolsMenu, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hMainMenu, "&���", i++, 0, hWindowMenu, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hMainMenu, "&������", i++, 0, hAboutMenu, FALSE, MFT_STRING);
    SetMenu(hwnd, hMainMenu);   //��������� ����� ���� ��� ��������� ����.
    DrawMenuBar(hwnd);          //�������������� ������ ���� ��������� ����.
    return 0;
}
