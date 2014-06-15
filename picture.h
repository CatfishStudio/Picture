/*2012(c)Сомов Евгений Павлович*/
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


//Описание функций: СОБЫТИЯ окон...................
LRESULT CALLBACK Event_Form_Programm(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Event_Form_Job(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Event_Form_Panel_Job(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
//Функция создания меню............................
BOOL CreateProgramMenu(HWND);
//.................................................

//ОПИСАНИЕ ПЕРЕМЕННЫХ..............................
HINSTANCE hInst; //текущий экземпляр
//...Главное окно приложения
char szClassFormProgram[ ] = "Form_Programm";
char szTitleFormProgram[ ] = "2012(c)Picture. Програма студента ВНУ им. В.Даля гр.: МТз-401 Сомова Є.П.";
//...Окно задания..................................
char szClassFormJob[ ] = "Form_Job";
char szTitleFormJob[ ] = "Вікно зображення:";
//...Окно панели инструментов рисования............
char szClassFormPanelJob[ ] = "Form_PanelJob";
char szTitleFormPanelJob[ ] = " ";

//ДЕСКРИПРОРЫ ОКОН.................................
HWND hWndClient = NULL; //клиентская область для дочерних MDI окон
HWND hWndJob = NULL;    //дескриптор окна работы с изображением
HWND hPanelJob = NULL;  //дескриптор окна инструментов
//.................................................

//...Отметки созданных окон приложения.............
bool ActionWndJob = FALSE;      //окно работы с изображением
bool ActionWndPanelJob = FALSE; //окно инструментов
//...Отметки актуального выбора пользователя.......
bool ActionCircle = FALSE;      //кнопка Круг
bool ActionEllipse = FALSE;     //кнопка Эллипс
bool ActionSquare = FALSE;      //кнопка Квадрат
bool ActionRectangle = FALSE;   //кнопка Прямоугольник
bool ActionLine = FALSE;        //кнопка Линия
bool ActionBlack = FALSE;       //кнопка Черный цвет
bool ActionRed = FALSE;         //кнопка Красный цвет
bool ActionCyan = FALSE;        //кнопка Синий цвет
bool ActionGreen = FALSE;       //кнопка Зеленый цвет
bool ActionYellow = FALSE;      //кнопка Желтый цвет

//...Положение курсора мыши в окне работы с изображением
WORD xPosDown, yPosDown; //координаты при нажатой кнопки
WORD xPosUp, yPosUp;     //координаты при отжатой кнопки

//...Кнопки........................................
HWND hButton1, hButton2, hButton3, hButton4, hButton5;
HWND hButtonBlack, hButtonRed, hButtonCyan, hButtonGreen, hButtonYellow;
//...Цвет пера.....................................
HPEN hPenBlack, hPenRed, hPenCyan, hPenGreen, hPenYellow;

//ПЕРЕМЕННЫЕ ВНУТРЕННИХ КЛАСОВ.....................
MenuClass Menu;   //Объявлена переменная класса создания меню
PanelClass Panel; //Объявлена переменная класса создания панели
//.................................................

//ДИАЛОГОВЫЕ ОКНА: Открыть и Сохранить файл........
OPENFILENAME ofn;
TCHAR szFile[20000]="";
TCHAR szFileTitle[20000]="";
void OpenDialog(HWND); //Диалогового окна
void LoadFile(HWND); //Диалоговое окно открытия файла
void SaveFile(HWND); //Диалоговое окно сохранения файла
//.................................................

//ОБРАБОТКА ИЗОБРАЖЕНИЯ............................
RECT WindowJobSize; //Размер рабочего окна (окна редактирования изображения)
PAINTSTRUCT paintStruct;
HDC winDC,  //контекст окна
	cwinDC, //контекст в памяти (копия окна) - прослойка между ресурсными контекстами и окном - на нем будем рисовать всё
	fonDC;  //контекст с фоновым рисунком
HBITMAP bmpFon, //хэндл для хранения картинки-фона
    bmpMem, //битмап, в котором будет храниться копия клиентской области
	bmpTemp;//временный хэндл
void SaveBMP (HWND); //Сохранение рисунка в файл
void InitGraphics(HWND); //инициализация графической области окна
void ClearGraphics();//очистка
//.................................................

//Описание процедур обработки окон "Открыть" и "Сохранить" ---------------
void LoadFile(HWND hwnd)
{
 OpenDialog(hwnd);
 if(GetOpenFileName(&ofn))
  {
       HDC tempDC = GetDC (hwnd); //Захватываем контекст окна (чтобы создать всё что нужно для него)
	   cwinDC = CreateCompatibleDC (tempDC); //Контекст-прослойка между ресурсными контекстами и окном
	   fonDC = CreateCompatibleDC (tempDC); //ресурсный контекст для хранения нетронутого фона
	   
	   //Определяем размер рабочего окна.
	   GetWindowRect(hwnd, &WindowJobSize); //& передача параметра как ссылку

	   //Загружаем картинку
	   bmpFon = (HBITMAP)LoadImage (NULL, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	   //Создаем пустой битмап для хранения всей картины (т.к. сам контекст это не хранит)
	   //Именно в этом битмапе мы будем рисовать
	   bmpMem = CreateCompatibleBitmap (tempDC, WindowJobSize.right, WindowJobSize.bottom);
       ReleaseDC (hwnd, tempDC); //Отпускаем контекст окна
       bmpTemp = (HBITMAP)SelectObject (fonDC, bmpFon); //Прикручиваем битмап к контексту
	   if (bmpTemp) DeleteObject (bmpTemp);
	   bmpTemp = (HBITMAP)SelectObject (cwinDC, bmpMem);
       if (bmpTemp) DeleteObject (bmpTemp);
       //Обновляем загруженную картинку
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
		//Посылаем сообщение WM_PAINT с о перерисовке.
		InvalidateRect (hwnd, NULL, false);
		UpdateWindow(hWndJob);
  }
 }
//Диалоговое окно СОХРАНЕНИЯ --------------------------------------------------
void SaveFile(HWND hwnd)
 {
 OpenDialog(hwnd);
 if(GetSaveFileName(&ofn))
  {
        strcat(szFile, ".bmp"); //конкатенация строк, к имени файла добавляем .bmp
        SaveBMP(hwnd);          //процедура сохранения изображения в файл
        MessageBox(hwnd, "Файл успішно збережений!", "Повідомлення:", MB_OK);
  }
}
//Диалоговое окно ОТКРЫТИЯ ----------------------------------------------------
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
 ofn.lpstrFilter =  "Файл зображення *.bmp\0*.bmp\0\0";
 ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
 ofn.nFilterIndex = 1;
 }
//--СОХРАНЕНИЕ В ФАЙЛ BMP ----------------------------------------------------
void SaveBMP (HWND hwnd) {
	BITMAPFILEHEADER bfh;  //структура с заголовком файла
	BITMAPINFOHEADER bih;  //структура с описанием формата картинки
	BITMAPINFO bi;	       //описание формата для функции GetDIBits ()
	void *pdwBits = NULL;  //указатель на буфер с будущим рисунком
	DWORD dwWB = 0;        //переменная для хранения записанных байт в файл
	HANDLE hFile = NULL;   //хэндл открытого файла

	//Создаем пустой буфер, в который потом скопируется картинка
	pdwBits = (void *)GlobalAlloc (GMEM_FIXED, WindowJobSize.right * WindowJobSize.bottom * 4);

	//Обнуляем структуры
	memset (&bfh, 0, sizeof (BITMAPFILEHEADER));
	memset (&bih, 0, sizeof (BITMAPINFOHEADER));
	memset (&bi, 0, sizeof (BITMAPINFO));

	//Заполняем заголовочную структуру
	bfh.bfType = 0x4D42;                           // Обозначим, что это bmp 'BM'
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
	// Посчитаем размер конечного файла
	bfh.bfSize = bfh.bfOffBits + WindowJobSize.right * WindowJobSize.bottom * 4;

	//Заполняем описание картинки
	bih.biSize = sizeof(bih);                      // Так положено
	bih.biBitCount = 32;                           // 16 бит на пиксель
	bih.biCompression = BI_RGB;                    // Без сжатия
	bih.biHeight = WindowJobSize.bottom;
	bih.biWidth = WindowJobSize.right;
	bih.biPlanes = 1;

	//Копируем в структуру BITMAPINFO
	CopyMemory (&bi, &bih, sizeof (BITMAPINFOHEADER));

	//Получаем с помощью функции саму картинку из контекста в памяти
	GetDIBits (cwinDC, bmpMem, 0, WindowJobSize.bottom, pdwBits, 
                                        (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	//Создаем файл для записи
	hFile = CreateFile (szFile,
											GENERIC_WRITE,
											0,
											NULL,
											CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL,
											(HANDLE)NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
			if (pdwBits) GlobalFree (pdwBits);
			SetWindowText (hwnd, "Помилка при відкретті файлу");
			return;
		}

	//Записываем структуру с заголовком файла
	if (!WriteFile (hFile, (void *)&bfh, sizeof (BITMAPFILEHEADER), &dwWB, NULL)) {
		SetWindowText (hwnd, "Помилка при записі BITMAPFILEHEADER");
		if (pdwBits) GlobalFree (pdwBits);
		return;
	}

	//Записываем структуру с описанием формата картинки
	if (!WriteFile (hFile, (void *)&bih, sizeof (BITMAPINFOHEADER), &dwWB, NULL)) {
		SetWindowText (hwnd, "Помилка при записі BITMAPINFOHEADER");
		if (pdwBits) GlobalFree (pdwBits);
		return;
	}

	//Записываем собсна саму картинку после двух предыдущих структур
	if (!WriteFile (hFile, (void *)pdwBits, 
                WindowJobSize.right * WindowJobSize.bottom * 4, &dwWB, NULL)) 
    {
		SetWindowText (hwnd, "Помилка при записі DIBits");
		if (pdwBits) GlobalFree (pdwBits);
		return;
	}

	//Закрываем хэндл файла и очищаем буфер
	CloseHandle (hFile);
	if (pdwBits) GlobalFree (pdwBits);
	return;
}
//--ИНИЦИАЛИЗАЦИЯ ГРАФИЧЕСКОЙ СРЕДЫ -------------------------------------------
void InitGraphics(HWND hwnd)
{
       HDC tempDC = GetDC (hwnd); //Захватываем контекст окна (чтобы создать всё что нужно для него)
	   cwinDC = CreateCompatibleDC (tempDC); //Контекст-прослойка между ресурсными контекстами и окном
	   fonDC = CreateCompatibleDC (tempDC); //ресурсный контекст для хранения нетронутого фона

	   //Определяем размер рабочего окна.
	   GetWindowRect(hwnd, &WindowJobSize); //& передача параметра как ссылку

	   //Создаем пустой битмап для хранения всей картины (т.к. сам контекст это не хранит)
	   //Именно в этом битмапе мы будем рисовать
	   bmpMem = CreateCompatibleBitmap (tempDC, WindowJobSize.right, WindowJobSize.bottom);
       ReleaseDC (hwnd, tempDC); //Отпускаем контекст окна
       bmpTemp = (HBITMAP)SelectObject (fonDC, bmpFon); //Прикручиваем битмап к контексту
	   if (bmpTemp) DeleteObject (bmpTemp);
	   bmpTemp = (HBITMAP)SelectObject (cwinDC, bmpMem);
       if (bmpTemp) DeleteObject (bmpTemp);
       //Закрашиваем рабочую облать белым цветом
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
       //Посылаем сообщение WM_PAINT с о перерисовке.
	   InvalidateRect (hwnd, NULL, false);        
}
//--ОЧИСТКА -------------------------------------------------------------------
void ClearGraphics()
{
    winDC = NULL;
    cwinDC = NULL;
    fonDC = NULL;
    bmpFon = NULL;
    bmpMem = NULL;
    bmpTemp = NULL;
}
