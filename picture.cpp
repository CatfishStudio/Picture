/*2012(c)Сомов Евгений Павлович*/
#include "picture.h"

/*=================================================
Структура окон приложения:                        /
1. Главное окно приложения (FormProgramm)         /
2. Окно работы с изображением (FormJob)           /
3. Окно инструментов (FormPanelJob)               /
4. Диалоговое окно "Открыть файл"                 /
5. Диалоговое окно "Сохранить файл"               /
6. Диалоговое окно "О программе"                  /
=================================================*/

//==ГЛАВНАЯ ФУНКЦИЯ ПРИЛОЖЕНИЯ=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hwnd;
    WNDCLASSEX wc;
    
   // Регистрация основного класса окна приложения.
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

   //регистрация класса окна
   if ( !RegisterClassEx( &wc ) )
      return( FALSE );

   // Зарегистрировать класс окна рисования.
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

   //регистрация класса окна
   if ( !RegisterClassEx( &wc ) )
      return( FALSE );
      
   // Зарегистрировать класс окна инструментов.
   //.....................................................
   wc.lpfnWndProc   = (WNDPROC)Event_Form_Panel_Job;
   wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
   wc.lpszMenuName  = NULL;
   wc.lpszClassName = szClassFormPanelJob;
   wc.cbSize        = sizeof( WNDCLASSEX );
   wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

   //регистрация класса окна
   if ( !RegisterClassEx( &wc ) )
      return( FALSE );
   
   //.....................................................
   hInst = hInstance;

   //Создание главного окна программы
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

    ShowWindow(hwnd, nCmdShow); //Отобразить окно
    UpdateWindow(hwnd); //Перерисовать(обновить) окно

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
//ОПИСАНИЕ СОБЫТИЙ ГЛАВНОГО ОКНА-----------------------------------------------
LRESULT CALLBACK Event_Form_Programm(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hToolbar; //панель инструментов.
    switch(msg) //Обработка сообщений окна
	{
        case WM_CREATE: //Событие наступающее при начале создании окна
        {
             //Функция создания меню программы -------------------------
             CreateProgramMenu(hwnd);
             //Создание панели инструментов.----------------------------
             DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_DLGFRAME;
             hToolbar = Panel.CreateToolBar(hwnd, dwStyle, ID_TOOLBAR);
             
             //Назначить окно меню--------------------------------------
             CLIENTCREATESTRUCT ccs;
             ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 4); //2-окна в меню ВИД
             ccs.idFirstChild = ID_CHILDWINDOW;
             
             //Создание клиентского окна MDI ---------------------------
             hWndClient = CreateWindowEx(WS_EX_CLIENTEDGE,
                                          "MDICLIENT", NULL,
                                          WS_CHILD | WS_CLIPSIBLINGS,
                                          0,
                                          0,
                                          0,
                                          0,
                                          hwnd, (HMENU)0xCA0, hInst, &ccs);

             ShowWindow(hWndClient, SW_SHOW); //Показать окно
             UpdateWindow(hWndClient); //Обновить (перерисовать) окно
             //--------------------------------------------------------
             //Создаем окно панели инструментов для рисования.---------
             hPanelJob = CreateMDIWindow((LPTSTR)szClassFormPanelJob,
                                         szTitleFormPanelJob, 0L,
                                         5,
                                         50, 
                                         100,
                                         410,
                                         hWndClient, hInst, 0L);
             
             ShowWindow(hPanelJob, SW_SHOW); //Показать окно
             UpdateWindow(hPanelJob); //Обновить (перерисовать) окно
             //--Кнопки в окне инструментов рисования------------------
             CreateWindow("button", "Інструменти:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,5,110,200, hPanelJob, (HMENU)0, hInst, NULL);
             hButton1 = CreateWindow("button", "Коло",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,30,90,30, hPanelJob,(HMENU)ID_BUTTON1,
                          hInst, NULL);
             hButton2 = CreateWindow("button", "Еліпс",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,65,90,30, hPanelJob,(HMENU)ID_BUTTON2,
                          hInst, NULL);
             hButton3 = CreateWindow("button", "Квадрат",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,100,90,30, hPanelJob,(HMENU)ID_BUTTON3,
                          hInst, NULL);
             hButton4 = CreateWindow("button", "Прямокут.",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,135,90,30, hPanelJob,(HMENU)ID_BUTTON4,
                          hInst, NULL);
             hButton5 = CreateWindow("button", "Лінія.",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,170,90,30, hPanelJob,(HMENU)ID_BUTTON5,
                          hInst, NULL);
             CreateWindow("button", "Колір:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,200,110,170, hPanelJob, (HMENU)0, hInst, NULL);
             hButtonBlack = CreateWindow("button", "Чорний",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,220,90,25, hPanelJob,(HMENU)ID_BUTTON6,
                          hInst, NULL);
             hButtonRed = CreateWindow("button", "Червоний",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,250,90,25, hPanelJob,(HMENU)ID_BUTTON7,
                          hInst, NULL);
             hButtonCyan = CreateWindow("button", "Синій",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,280,90,25, hPanelJob,(HMENU)ID_BUTTON8,
                          hInst, NULL);
             hButtonGreen = CreateWindow("button", "Зелений",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,310,90,25, hPanelJob,(HMENU)ID_BUTTON9,
                          hInst, NULL);
             hButtonYellow = CreateWindow("button", "Жовтий",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,340,90,25, hPanelJob,(HMENU)ID_BUTTON10,
                          hInst, NULL);
             //Активизация кнопки "Прямоугольник"
             SendMessage(hButton4, BM_SETSTATE, TRUE, 0L);
             SendMessage(hButtonBlack, BM_SETSTATE, TRUE, 0L);
             ActionRectangle = TRUE;//Значение по умолчанию "Прямоугольник"
             ActionBlack = TRUE;    //Значение по умолчанию "Черный"
             //Окно инструментов открыто 
             ActionWndPanelJob = TRUE; //Окно активно
             //--------------------------------------------------------
             //Создание окна рисунка ----------------------------------
             hWndJob = CreateMDIWindow((LPTSTR)szClassFormJob,
                                         szTitleFormJob, 0L,
                                         150,
                                         50,
                                         500,
                                         400,
                                         hWndClient, hInst, 0L);
            
             ShowWindow(hWndJob, SW_SHOW); //Показать окно
             UpdateWindow(hWndJob); //Обновить (перерисовать) окно
             InitGraphics(hWndJob); //Инициализация графической поверхности
             ActionWndJob = TRUE;   //Окно активно
             //---------------------------------------------------------
             return 0;
        }
        //При изменении размера окна ----
        case WM_SIZE:
        {
            //Размер клиента окна размером рабочей области главного окна программы.
            MoveWindow(hWndClient, 0, 0, LOWORD(lParam),
                                            HIWORD(lParam), TRUE );
            //изменение размеров панели инструментов.
            MoveWindow(hToolbar, 0, 0, LOWORD(lParam),
                                            HIWORD(lParam), TRUE );
            return 0;
            
        }
        //--ОБРАБОТКА МЕНЮ --------------
        case WM_COMMAND:
        {
             switch (LOWORD(wParam))
             {
                    case CM_FILE_OPEN: //Открыть изображение
                    {
                         LoadFile(hWndJob);
                         return 0;
                    }
                    case CM_FILE_SAVE: //Сохранить изображение
                    {
                         SaveFile(hwnd);
                         return 0;
                    }
                    case CM_FILE_QUIT: //Выход из программы
                    {
                         DestroyWindow( hwnd );
                         return 0;
                    }
                    case CM_TOOLS_WINTOOLS: //Окно инструментов
                    {
                        //Проверка на уже созданное окно
                        if(ActionWndPanelJob == TRUE){
                           return 0;
                         } 
                         //Создаем окно панели инструментов для рисования.---------
                         hPanelJob = CreateMDIWindow((LPTSTR)szClassFormPanelJob,
                                         szTitleFormPanelJob, 0L,
                                         5,
                                         50,
                                         100,
                                         410,
                                         hWndClient, hInst, 0L);

                         ShowWindow(hPanelJob, SW_SHOW);
                         UpdateWindow(hPanelJob);
                         //--Кнопки в окне инструментов рисования------------------
                         CreateWindow("button", "Інструменти:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,5,110,200, hPanelJob, (HMENU)0, hInst, NULL);
                         hButton1 = CreateWindow("button", "Коло",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,30,90,30, hPanelJob,(HMENU)ID_BUTTON1,
                          hInst, NULL);
                         hButton2 = CreateWindow("button", "Еліпс",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,65,90,30, hPanelJob,(HMENU)ID_BUTTON2,
                          hInst, NULL);
                         hButton3 = CreateWindow("button", "Квадрат",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,100,90,30, hPanelJob,(HMENU)ID_BUTTON3,
                          hInst, NULL);
                         hButton4 = CreateWindow("button", "Прямокут.",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,135,90,30, hPanelJob,(HMENU)ID_BUTTON4,
                          hInst, NULL);
                         hButton5 = CreateWindow("button", "Лінія",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,170,90,30, hPanelJob,(HMENU)ID_BUTTON5,
                          hInst, NULL);
                         CreateWindow("button", "Колір:",
                          WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                          2,200,110,170, hPanelJob, (HMENU)0, hInst, NULL);
                        hButtonBlack = CreateWindow("button", "Чорний",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,220,90,25, hPanelJob,(HMENU)ID_BUTTON6,
                          hInst, NULL);
                        hButtonRed = CreateWindow("button", "Червоний",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,250,90,25, hPanelJob,(HMENU)ID_BUTTON7,
                          hInst, NULL);
                        hButtonCyan = CreateWindow("button", "Синій",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,280,90,25, hPanelJob,(HMENU)ID_BUTTON8,
                          hInst, NULL);
                        hButtonGreen = CreateWindow("button", "Зелений",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,310,90,25, hPanelJob,(HMENU)ID_BUTTON9,
                          hInst, NULL);
                        hButtonYellow = CreateWindow("button", "Жовтий",
                          WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                          10,340,90,25, hPanelJob,(HMENU)ID_BUTTON10,
                          hInst, NULL);
                        //Активизация кнопки "Прямоугольник"
                        SendMessage(hButton4, BM_SETSTATE, TRUE, 0L);
                        SendMessage(hButtonBlack, BM_SETSTATE, TRUE, 0L);
                        ActionRectangle = TRUE;
                        ActionBlack = TRUE;
                        //Окно инструментов открыто
                        ActionWndPanelJob = TRUE;
                        return 0;    
                    }
                    case CM_TOOLS_NEWJOB: //Новое окно редактирования изображения
                    {
                         //Проверка на уже созданное окно
                         if(ActionWndJob == TRUE){
                            MessageBox(hwnd, 
                                "Вікно редагування зображення вже відкрито, закрийте його спочатку!",
                                "Повідомлення:", MB_OK | MB_ICONSTOP);
                            return 0;
                         }
                         //Создание нового окна рисования
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
                    case IDM_CASCADE: //Каскад
                    {
                        CascadeWindows( hWndClient, MDITILE_SKIPDISABLED,
                                        NULL, 0, NULL );
                        return 0;
                    }
                    case IDM_TILEHORZ: //горизонтальная плитка
                    {
                        TileWindows( hWndClient, MDITILE_HORIZONTAL,
                                     NULL, 0, NULL );
                    return 0;
                    }
                    case IDM_TILEVERT: //вертикальная плитка
                    {
                        TileWindows( hWndClient, MDITILE_VERTICAL,
                                     NULL, 0, NULL );
                        return 0;
                    }
                    case CM_ABOUT: //Окно "О программе"
                    {
                         DialogBox( hInst, "AboutBox", hwnd, (DLGPROC)About );
                         return 0;
                    }
                    case CM_CIRCLE: //Круг
                    {
                        ActionCircle = TRUE;
                        ActionEllipse = FALSE;
                        ActionSquare = FALSE;
                        ActionRectangle = FALSE;
                        ActionLine = FALSE;
                        return 0;   
                    }
                    case CM_ELLIPSE: //Эллипс
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = TRUE;
                        ActionSquare = FALSE;
                        ActionRectangle = FALSE;
                        ActionLine = FALSE;
                        return 0;
                    }
                    case CM_SQUARE: //Квадрат
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = FALSE;
                        ActionSquare = TRUE;
                        ActionRectangle = FALSE;
                        ActionLine = FALSE;
                        return 0;
                    }
                    case CM_RECTANGLE: //Прямоугольнк
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = FALSE;
                        ActionSquare = FALSE;
                        ActionRectangle = TRUE;
                        ActionLine = FALSE;
                        return 0;
                    }
                    case CM_LINE: //Сплошная линия
                    {
                        ActionCircle = FALSE;
                        ActionEllipse = FALSE;
                        ActionSquare = FALSE;
                        ActionRectangle = FALSE;
                        ActionLine = TRUE;
                        return 0;
                    }
                    case CM_BLACK: //Черный цвет граней
                    {
                        ActionBlack = TRUE;
                        ActionRed = FALSE;
                        ActionCyan = FALSE;
                        ActionGreen = FALSE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_RED: //Красный цвет граней
                    {
                        ActionBlack = FALSE;
                        ActionRed = TRUE;
                        ActionCyan = FALSE;
                        ActionGreen = FALSE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_CYAN: //Синий цвет граней
                    {
                        ActionBlack = FALSE;
                        ActionRed = FALSE;
                        ActionCyan = TRUE;
                        ActionGreen = FALSE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_GREEN: //Зеленый цвет граней
                    {
                        ActionBlack = FALSE;
                        ActionRed = FALSE;
                        ActionCyan = FALSE;
                        ActionGreen = TRUE;
                        ActionYellow = FALSE;
                        return 0;
                    }
                    case CM_YELLOW: //Желтый цвет граней
                    {
                        ActionBlack = FALSE;
                        ActionRed = FALSE;
                        ActionCyan = FALSE;
                        ActionGreen = FALSE;
                        ActionYellow = TRUE;
                        return 0;
                    }
                    case CM_CLEARJOB: //Очистка рабочей поверхности
                    {
                        ClearGraphics();
                        InitGraphics(hWndJob);
                        UpdateWindow(hWndJob); //Перерисовать(обновить) окно
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
            //Освобождаем память которая была занята
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
//ОПИСАНИЕ СОБЫТИЙ ОКНА РИСОВАНИЯ ----------------------------------------------
LRESULT CALLBACK Event_Form_Job( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch(uMsg)
   {
    //---------------------------------------------------
    case WM_PAINT: {
		//Копирование на окно из прослойки в памяти (буфера)
		//Здесь используется структура для указания области обновления (для примера у нас она занимает весь фон)
        winDC = BeginPaint (hWndJob, &paintStruct);
			     StretchBlt(winDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom,
				    cwinDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, SRCCOPY);
		EndPaint (hWndJob, &paintStruct);
		UpdateWindow(hWndJob); //Перерисовать(обновить) окно
		return 0;
    }
    //---------------------------------------------------
    case WM_LBUTTONDOWN:
    {
        //Получаем координаты курсора при нажатой левой кнопки мыши
        xPosDown = LOWORD(lParam);
        yPosDown = HIWORD(lParam);
        return 0; 
    }
    //---------------------------------------------------
    case WM_LBUTTONUP:
    {
        //Получаем координаты курсора при отжатой левой кнопки мыши
        //GetCursorPos(&UpCursor); 
        xPosUp = LOWORD(lParam);
        yPosUp = HIWORD(lParam);
        //Начало процеса изображения
        winDC = BeginPaint (hWndJob, &paintStruct);
		StretchBlt(winDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom,
			cwinDC, 0, 0, WindowJobSize.right, WindowJobSize.bottom, SRCCOPY);
        
        //Определяемся с цветом пера -------------------
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
        //Рисуем прямоугольник
        if(ActionRectangle == TRUE){
            Rectangle(cwinDC,xPosDown,yPosDown,xPosUp,yPosUp);
        }
        //Рисуем квадрат
        if(ActionSquare == TRUE){
            Rectangle(cwinDC,xPosDown,yPosDown,xPosDown+100,yPosDown+100);   
        }
        //Рисуем прямую линию
        if(ActionLine == TRUE){
            MoveToEx(cwinDC,xPosDown,yPosDown,NULL);
            LineTo(cwinDC,xPosUp,yPosUp);
        }
        //Рисуем эллипс
        if(ActionEllipse){
            Ellipse(cwinDC, xPosDown, yPosDown, xPosUp, yPosUp);    
        }
        //Рисуем круг
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
        //Завершение процесса изображение
        EndPaint (hWndJob, &paintStruct);
        InvalidateRect (hWndJob, NULL, false);
        
        return 0;
    }
    //---------------------------------------------------
    case WM_DESTROY:
	{
	    ActionWndJob = FALSE;
	    ClearGraphics(); //очистка переменных
		return 0;
	}        
      default :
            return( DefMDIChildProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}
//ОПИСАНИЕ СОБЫТИЙ ОКНА ИНСТРУМЕНТОВ -------------------------------------------
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
//ОПИСАНИЕ СОБЫТИЙ ДИАЛОГОВОГО ОКНА "О прграмме"-------------------------------
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

//ПОСТРОЕНИЕ МЕНЮ ПРГРАММЫ-----------------------------------------------------
BOOL CreateProgramMenu(HWND hwnd)
{
    static HMENU hMainMenu, hFileMenu, hToolsMenu, hWindowMenu, hAboutMenu; //меню.
    //МЕНЮ ПРОГРАММЫ-------------------------------------
    hMainMenu = CreateMenu();
    //--Создаем временное меню для раздела "ФАЙЛ"
    hFileMenu = CreatePopupMenu();
    int i=0;
    Menu.CreateMenuItem(hFileMenu, "&Відкрити файл *.bmp", i++, CM_FILE_OPEN,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hFileMenu, "&Зберегти в файл *.bmp", i++, CM_FILE_SAVE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hFileMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hFileMenu, "&Вихід.", i++, CM_FILE_QUIT,
                                       NULL, FALSE, MFT_STRING);
    //--Создаем временное меню для раздела "ИНСТРУМЕНТЫ"
    hToolsMenu = CreatePopupMenu();
    Menu.CreateMenuItem(hToolsMenu, "&Вікно зображення", i++, CM_TOOLS_NEWJOB,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Вікно інструментів", i++, CM_TOOLS_WINTOOLS,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hToolsMenu, "&Коло", i++, CM_CIRCLE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Еліпс", i++, CM_ELLIPSE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Квадрат", i++, CM_SQUARE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Прямокутник", i++, CM_RECTANGLE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Лінія", i++, CM_LINE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hToolsMenu, "&Колір: Чорний", i++, CM_BLACK,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Колір: Червоний", i++, CM_RED,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Колір: Синій", i++, CM_CYAN,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Колір: Зелений", i++, CM_GREEN,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "&Колір: Жовтий", i++, CM_YELLOW,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hToolsMenu, "", i++, 0, NULL, FALSE, MFT_SEPARATOR);
    Menu.CreateMenuItem(hToolsMenu, "&Очистити область.", i++, CM_CLEARJOB,
                                       NULL, FALSE, MFT_STRING);
    //--Создаем временное меню для раздела "ВИД"
    hWindowMenu = CreatePopupMenu();
    Menu.CreateMenuItem(hWindowMenu, "&Каскадна побудова вікон.", i++, IDM_CASCADE,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hWindowMenu, "&Горизонтальна плитка", i++, IDM_TILEHORZ,
                                       NULL, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hWindowMenu, "&Вертикальна плитка.", i++, IDM_TILEVERT,
                                       NULL, FALSE, MFT_STRING);
    //--Создаем временное меню для раздела "СПРАВКА"
    hAboutMenu = CreatePopupMenu();
    Menu.CreateMenuItem(hAboutMenu, "&Про програму.", i++, CM_ABOUT,
                                       NULL, FALSE, MFT_STRING);
    //--Подключаем временные меню к главному меню
    Menu.CreateMenuItem(hMainMenu, "&Файл", i++, 0, hFileMenu, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hMainMenu, "&Інструменти", i++, 0, hToolsMenu, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hMainMenu, "&Вид", i++, 0, hWindowMenu, FALSE, MFT_STRING);
    Menu.CreateMenuItem(hMainMenu, "&Довідка", i++, 0, hAboutMenu, FALSE, MFT_STRING);
    SetMenu(hwnd, hMainMenu);   //назначает новое меню для заданного окна.
    DrawMenuBar(hwnd);          //перерисовывает строку меню заданного окна.
    return 0;
}
