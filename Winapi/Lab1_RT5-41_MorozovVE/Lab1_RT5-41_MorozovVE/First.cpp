#include <Windows.h>
#include <tchar.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
int i=0, j=0;

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 255)); 	// ������ ����� ��� ���������� ���� ������ ����� � ������� ��� 


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("�������������� ������� 1"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		450,				// x 
		200, 				// y	 ������� ���� 
		400, 				// width 
		400, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 


	ShowWindow(hWnd, mode); 				// �������� ����
	UpdateWindow(hWnd);
	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return msg.wParam;
}


// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC dc = GetDC(hWnd); //��������� � ����������� ����
	HBRUSH brush; //���������� brush - ��� �����, ��� ����� �������������� ��� ������������
	HPEN pen;    //������ ����
	static int i, j;
	PAINTSTRUCT ps;

	switch (message)		 // ���������� ���������
	{
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		brush = CreateSolidBrush(RGB(255, 255, 0)); //������ ����� ������������ ����� � �����
		pen = CreatePen(5, 0, RGB(255, 255, 0));
		SelectObject(dc, pen);//�������� ����
		SelectObject(dc, brush);//�������� �����
		Ellipse(dc, 90, 90, 290, 290);//������ ������ ����
		DeleteObject(brush); //������� ������ �� ���������, �� ��� �������� �����
		DeleteObject(pen);//������� ������ �� ���������, �� ��� ��������� ����
		
		brush = CreateSolidBrush(RGB(0, 0, 255)); //������ ����� ������������ ����� � �����
		pen = CreatePen(5, 0, RGB(255, 255, 0));
		SelectObject(dc, pen);//�������� ����
		SelectObject(dc, brush);//�������� �����
		Ellipse(dc, -200 + 90 + i, 90, -200 + 290 + i, 290);//������ ����� ���� �����

		Ellipse(dc, 200 + 90 - j, 90, 200 + 290 - j, 290);//������ ����� ���� ������
		DeleteObject(brush); //������� ������ �� ���������, �� ��� �������� �����
		DeleteObject(pen);//������� ������ �� ���������, �� ��� ��������� ����
	
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONUP:
		if (i == 180){
			i = i + 20;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			if (MessageBox(NULL,
				L"������ ������� ���������!!!",
				L"��������!!!", MB_ICONASTERISK | MB_OK) == IDOK) {
				PostQuitMessage(0);
				break; 			// ���������� ��������� 
			}
			else {
				PostQuitMessage(0);
				break; 			// ���������� ��������� 
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
				L"������ ������� ���������!!!",
				L"��������!!!", MB_ICONASTERISK | MB_OK) == IDOK) {
				PostQuitMessage(0);
				break; 			// ���������� ��������� 
			}
			else {
				PostQuitMessage(0);
				break; 			// ���������� ��������� 
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
			break; 			// ���������� ��������� 
			default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}
