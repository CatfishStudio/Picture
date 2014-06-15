/*2012(c)Сомов Евгений Павлович*/
#ifndef MENUCLASS_H
#define MENUCLASS_H

#define CM_FILE_OPEN 1001       //константа меню открытие
#define CM_FILE_SAVE 1002       //константа меню сохранение
#define CM_FILE_QUIT 1003       //константа меню выход
#define CM_TOOLS_NEWJOB 2001    //константа меню окно изображения
#define CM_TOOLS_WINTOOLS 2002  //константа меню окно инструментов
#define CM_ABOUT 2003           //константа меню о программе


#define CM_CIRCLE 2004          //константа меню круг
#define CM_ELLIPSE 2005         //константа меню эллипс
#define CM_SQUARE 2006          //константа меню квадрат
#define CM_RECTANGLE 2007       //константа меню прямоугольник
#define CM_LINE 2008            //константа меню линия

#define CM_BLACK 2011           //константа меню цвет черный
#define CM_RED 2012             //константа меню цвет красный
#define CM_CYAN 2013            //константа меню цвет синий
#define CM_GREEN 2014           //константа меню цвет зеленый
#define CM_YELLOW 2015          //константа меню цвет желтый

#define CM_CLEARJOB 2016        //константа меню очистить область

#define IDM_CASCADE 3001        //константа меню вид: каскад
#define IDM_TILEHORZ 3002       //константа меню вид: горизонтальная плитка
#define IDM_TILEVERT 3003       //константа меню вид: вертикальная плитка

class MenuClass
{
	public:
		// Описание функции класса
		BOOL CreateMenuItem(HMENU hMenu, char *str, UINT uIns, UINT uCom, HMENU hSubMenu,
                          BOOL flag, UINT fType);
		
};

#endif // MENUCLASS_H
