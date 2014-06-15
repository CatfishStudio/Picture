/*2012(c)Сомов Евгений Павлович*/
#include "panelclass.h" // заголовочный файл класса

// Создание панели инструментов
HWND PanelClass::CreateToolBar(HWND hwnd, DWORD dwStyle, UINT uCom)
{
    static TBBUTTON but[7];             //описание кнопки
    //Отступ от края панели
    but[0].fsStyle = TBSTYLE_SEP;       //стиль кнопки
    
    //Кнопка окна инструментов
    but[1].iBitmap = STD_PROPERTIES;    //номер кнопки в массиве
    but[1].idCommand=CM_TOOLS_WINTOOLS; //идентификатор команды
    but[1].fsState=TBSTATE_ENABLED;     //флаг исходного состояния
    but[1].fsStyle=TBSTYLE_GROUP;       //стиль кнопки
    
    //Кнопка окна изображения
    but[2].iBitmap = STD_FILENEW;
    but[2].idCommand=CM_TOOLS_NEWJOB;
    but[2].fsState=TBSTATE_ENABLED;
    but[2].fsStyle=TBSTYLE_GROUP;
    
    //Отступ
    but[3].fsStyle = TBSTYLE_SEP;
    
    //Кнопка открытия файла
    but[4].iBitmap = STD_FILEOPEN;
    but[4].idCommand=CM_FILE_OPEN;
    but[4].fsState=TBSTATE_ENABLED;
    but[4].fsStyle=TBSTYLE_GROUP;

    //Кнопка сохранения в файл
    but[5].iBitmap = STD_FILESAVE;
    but[5].idCommand=CM_FILE_SAVE;
    but[5].fsState=TBSTATE_ENABLED;
    but[5].fsStyle=TBSTYLE_GROUP;
    
    //Кнопка о программе    
    but[6].iBitmap = STD_HELP;
    but[6].idCommand=CM_ABOUT;
    but[6].fsState=TBSTATE_ENABLED;
    but[6].fsStyle=TBSTYLE_GROUP;
    
    //Создание панели инструментов
    return CreateToolbarEx(hwnd,        //дескриптор родительского окна панели
                 dwStyle,               //стиль панели
                 uCom,                  //идентификатор панели
                 0,                     //количество изображений кнопок в контейнере
                 HINST_COMMCTRL,        //дескриптор экземпляра приложения
                 IDB_STD_SMALL_COLOR,   //идентификатор запрашиваемого формата кнопок
                 but,                   //указатель на массив структуры типа TBBUTTON
                 7,                     //количество кнопок панели инструментов
                 0,                     //ширина кнопок в пикселях
                 0,                     //высота кнопок в пикселях
                 0,                     //ширина изображения кнопки в пикселях
                 0,                     //высота изображения в пикселях
                 sizeof(TBBUTTON));     //размер структуры TBBUTTON	
}


