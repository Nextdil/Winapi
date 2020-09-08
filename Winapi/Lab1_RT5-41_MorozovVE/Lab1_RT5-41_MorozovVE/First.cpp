#include <Windows.h>
#include <tchar.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
int i=0, j=0;

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 255)); 	// Создаём кисть для заполнения окна любого цвета в формате ргб 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Индивидуальное задание 1"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		450,				// x 
		200, 				// y	 Размеры окна 
		400, 				// width 
		400, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 


	ShowWindow(hWnd, mode); 				// Показать окно
	UpdateWindow(hWnd);
	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return msg.wParam;
}


// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC dc = GetDC(hWnd); //Цепляемся к консольному окну
	HBRUSH brush; //Переменная brush - это кисть, она будет использоваться для закрашивания
	HPEN pen;    //задаем перо
	static int i, j;
	PAINTSTRUCT ps;

	switch (message)		 // Обработчик сообщений
	{
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		brush = CreateSolidBrush(RGB(255, 255, 0)); //Создаём кисть определённого стиля и цвета
		pen = CreatePen(5, 0, RGB(255, 255, 0));
		SelectObject(dc, pen);//выбираем перо
		SelectObject(dc, brush);//Выбираем кисть
		Ellipse(dc, 90, 90, 290, 290);//Рисуем желтый круг
		DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти
		DeleteObject(pen);//Очищаем память от созданной, но уже ненужного пера
		
		brush = CreateSolidBrush(RGB(0, 0, 255)); //Создаём кисть определённого стиля и цвета
		pen = CreatePen(5, 0, RGB(255, 255, 0));
		SelectObject(dc, pen);//выбираем перо
		SelectObject(dc, brush);//Выбираем кисть
		Ellipse(dc, -200 + 90 + i, 90, -200 + 290 + i, 290);//Рисуем синий круг левый

		Ellipse(dc, 200 + 90 - j, 90, 200 + 290 - j, 290);//Рисуем синий круг правый
		DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти
		DeleteObject(pen);//Очищаем память от созданной, но уже ненужного пера
	
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONUP:
		if (i == 180){
			i = i + 20;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			if (MessageBox(NULL,
				L"Яблоко съедено полностью!!!",
				L"ВНИМАНИЕ!!!", MB_ICONASTERISK | MB_OK) == IDOK) {
				PostQuitMessage(0);
				break; 			// Завершение программы 
			}
			else {
				PostQuitMessage(0);
				break; 			// Завершение программы 
			}
	}
		else {
			i = i + 20;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	break;
	
	case WM_RBUTTONUP:
		if (j == 180) {
			j = j + 20;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			if (MessageBox(NULL,
				L"Яблоко съедено полностьь!!!",
				L"ВНИМАНИЕ!!!", MB_ICONASTERISK | MB_OK) == IDOK) {
				PostQuitMessage(0);
				break; 			// Завершение программы 
			}
			else {
				PostQuitMessage(0);
				break; 			// Завершение программы 
			}
		}
		else {
			j = j + 20;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case WM_DESTROY:
		
			PostQuitMessage(0);
			break; 			// Завершение программы 
			default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}
