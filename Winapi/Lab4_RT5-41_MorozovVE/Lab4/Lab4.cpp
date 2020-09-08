#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <tchar.h>
#include <process.h>

#define MAX_LOADSTRING 100
#define PATH L"C:\\Users\\user\\Documents\\Winapi\\Lab4\\Lab4\\test.txt"

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hWnd, // дескриптор окошка
	UINT, // сообщение, посылаемое ОС
	WPARAM, // параметры
	LPARAM); // сообщений, для последующего обращения

TCHAR WinName[] = _T("Lab4");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы, где хранится информация о нашем окне, указатель на определенную область памяти в ядре
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// струкутра отвечает за характеристики окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));// Заполнение окна цветом


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;
	hInst = This; // Сохранить маркер экземпляра в глобальной переменной
	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Lab4"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		550, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	HMENU hmenu1;
	hmenu1 = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Запуск");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1000, L"Списка");
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Качелей");
	}
	HMENU hPopupMenu1 = CreatePopupMenu();
	AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu1, L"&Выключение");
	{
		AppendMenu(hPopupMenu1, MF_STRING, 1002, L"Списка");
		AppendMenu(hPopupMenu1, MF_STRING, 1003, L"Качелей");
	}
	AppendMenu(hmenu1, MF_STRING, 0, L"&Выход");
	SetMenu(hWnd, hmenu1);
	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);			// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

HANDLE hGroupList;
HANDLE hSwing;
DWORD WINAPI GroupList(LPVOID t);
DWORD WINAPI Swing(LPVOID t);

int a = 0;
BOOL Prov1 = false;
BOOL Prov2 = false;


LPWSTR convertStr(LPCSTR pInStr)//преобразованиеLPCSTR в LPWSTR
{
	int length = strlen(pInStr);
	wchar_t* pwstr = new wchar_t[length];
	int result = MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, pInStr, length,
		pwstr, length
	);
	pwstr[length] = L'\0';
	return LPWSTR(pwstr);
}

std::map<int, int> names = { {1, 9},  {2, 9}, {3, 9}, {4, 10}, {5, 10} }; //, {6, 8}, {7, 15}, {8, 7}, {9, 13}, {10, 13}, {11, 13}, {12, 11}, {13, 9} };

DWORD WINAPI GroupList(LPVOID t)
{
	OVERLAPPED olf = { 0 };//Позиция чтения
	LARGE_INTEGER li = { 0 };
	li.QuadPart = 1;
	olf.Offset = li.LowPart;//Младшее слово позиции в файле
	olf.OffsetHigh = li.HighPart;//Старшее слово

	LPSTR buffer = (CHAR*)calloc(300, sizeof(CHAR));
	DWORD iNumread = 0;

	DWORD dwCounter, dwTemp;
	HANDLE hFile = CreateFile(PATH, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (!ReadFile(hFile, buffer, 300, &iNumread, &olf)) {
		return 1;
	}

	int i = 1;
	int k = 0;

	while (Prov1) 
	{
		RECT rect;
		PAINTSTRUCT ps;
		GetClientRect(HWND(t), &rect);
		std::cout << "p" << std::endl;
		LPCWSTR new_buf = convertStr(buffer);
		HDC hdc = GetDC(HWND(t));
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(255, 255, 255));
		SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
		Rectangle(hdc, 50, 50, 400, 305);
		SetTextColor(hdc, RGB(rand() % 250, rand() % 250, rand() % 250));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 210, 100, new_buf + k, names[i]);
		EndPaint(HWND(t), &ps);
		Sleep(1000);
		k += names[i];
		++i;
		if (i == 6) {
			i = 1;
			k = 0;
		}
	}

	return 0;
}


DWORD WINAPI Swing(LPVOID t)
{
	bool left_side = true;

	while (Prov2) {

		RECT rect;
		PAINTSTRUCT ps;
		GetWindowRect(HWND(t), &rect);
		int width = (int)(rect.right - rect.left);
		int height = (int)(rect.bottom - rect.top);
		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
		hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(38, 201, 255));

		if (left_side) {
			HPEN hPen1;
			hPen1 = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
			::MoveToEx(hdc, 250, 400, NULL);
			SelectObject(hdc, hPen1);
			::LineTo(hdc, 250, 450);
			::MoveToEx(hdc, 150, 350, NULL);
			SelectObject(hdc, hPen1);
			::LineTo(hdc, 350, 450);
			Sleep(500);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(255, 255, 255));
			SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
			Rectangle(hdc, 110, 470, 360, 340);
			ReleaseDC(HWND(t), hdc);

			::SelectObject(hdc, (HGDIOBJ)hBrush);
			::DeleteObject(hBrush);
			left_side = false;


		}
		else 
		{

			HPEN hPen2;
			hPen2 = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
			::MoveToEx(hdc, 250, 400, NULL);
			SelectObject(hdc, hPen2);
			::LineTo(hdc, 250, 450);
			::MoveToEx(hdc, 350, 350, NULL);
			SelectObject(hdc, hPen2);
			::LineTo(hdc, 150, 450);
			Sleep(500);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(255, 255, 255));
			SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
			Rectangle(hdc, 110, 470, 360, 340);
			ReleaseDC(HWND(t), hdc);
			left_side = true;
		}
	}
	return 0;
}





LRESULT CALLBACK WndProc(HWND hWnd,//Дескриптор окна
	UINT message,//Код сообщения
	WPARAM wParam,//Указатели, где хранится информация для сообщения
	LPARAM lParam)//Указатели, где хранится информация для сообщения
{
	switch (message)		 // Обработчик сообщений
	{
	

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case 1000:
		{
			Prov1 = true;
			hGroupList = CreateThread(NULL, 0, GroupList, hWnd, 0, NULL);
			break;
		}
		case 1001:
		{
			Prov2 = true;
			hSwing = CreateThread(NULL, 0, Swing, hWnd, 0, NULL);
			break;
		}
		case 1002:
		{
			TerminateThread(hGroupList, 0);
			_endthread;
	
			Prov1 = false;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		case 1003:
		{

			TerminateThread(hSwing, 0);
			Prov2 = false;
	
			break;

		}
		case 0:
		{
			DestroyWindow(hWnd);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);//Если сообщение никак не обрабатывается
	}

	return 0;
}