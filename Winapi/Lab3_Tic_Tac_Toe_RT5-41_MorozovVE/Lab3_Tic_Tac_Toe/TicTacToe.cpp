#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, // ���������� ������
						 UINT, // ���������, ���������� ��
						 WPARAM, // ���������
						 LPARAM); // ���������, ��� ������������ ���������
HWND hwndMain;

int WINAPI WinMain(HINSTANCE hInstance,/// ���������� ���������� ����������
	HINSTANCE hPrevInstance, //�� ������������ � 32� ������ ������
	PSTR szCmdLine, //����� ��� ������� ���� � ������ ��������� ������
	int iCmdShow) //����� ����������� ����	
{
	static TCHAR szAppName[] = _T("X-O");
	MSG msg;
	WNDCLASSEX wc;

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);
	//Okno
	hwndMain = CreateWindowEx(0,
		szAppName,
		_T("��������-������"),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		366,
		382,
		NULL,
		NULL,
		hInstance,
		NULL);
	HMENU hmenu1;
	hmenu1 = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&����");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1000, L"�����");
		AppendMenu(hPopupMenu, MF_SEPARATOR, 1000, L"");
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"�����");
	}
	AppendMenu(hmenu1, MF_STRING, 0, L"&������");

	SetMenu(hwndMain, hmenu1);
	ShowWindow(hwndMain, iCmdShow);
	UpdateWindow(hwndMain);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

#define EX 1
#define OH 2

const RECT m_rcSquares[9] = {
		{ 16, 16,112,112},
		{128, 16,224,112},
		{240, 16,336,112},
		{ 16,128,112,224},
		{128,128,224,224},
		{240,128,336,224},
		{ 16,240,112,336},
		{128,240,224,336},
		{240,240,336,336}
};

int m_nNextChar = EX, m_nGameGrid[9];

int GetRectID(int x, int y)
{
	for (int i = 0; i < 9; i++)
	{
		if (x > m_rcSquares[i].left && x < m_rcSquares[i].right &&
			y > m_rcSquares[i].top && y < m_rcSquares[i].bottom)
			return i;
	}
	return -1;
}

void DrawX(HDC hdc, int nPos)
{
	HPEN pen = ::CreatePen(PS_SOLID, 16, RGB(255, 0, 0));
	void* oldPen = ::SelectObject(hdc, pen);

	RECT rect = m_rcSquares[nPos];

	rect.top += 10;
	rect.bottom -= 10;
	rect.left += 10;
	rect.right -= 10;

	::MoveToEx(hdc, rect.left, rect.top, NULL);
	::LineTo(hdc, rect.right, rect.bottom);
	::MoveToEx(hdc, rect.left, rect.bottom, NULL);
	::LineTo(hdc, rect.right, rect.top);

	::SelectObject(hdc, (HGDIOBJ)oldPen);
	::DeleteObject(pen);
}

void DrawO(HDC hdc, int nPos)
{
	HPEN pen = ::CreatePen(PS_SOLID, 16, RGB(0, 0, 255));
	void* oldPen = ::SelectObject(hdc, pen);
	void* oldBr = ::SelectObject(hdc, GetStockObject(NULL_BRUSH));

	RECT rect = m_rcSquares[nPos];

	rect.top += 10;
	rect.bottom -= 10;
	rect.left += 10;
	rect.right -= 10;

	::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
	::SelectObject(hdc, (HGDIOBJ)oldBr);
	::SelectObject(hdc, (HGDIOBJ)oldPen);
	::DeleteObject(pen);
}

void DrawBoard(HDC hdc)
{
	// draw the lines
	HPEN pen = ::CreatePen(PS_SOLID, 16, RGB(0, 0, 0));
	void* oldPen = ::SelectObject(hdc, pen);
	//������������
	::MoveToEx(hdc, 120, 16, NULL);
	::LineTo(hdc, 120, 336);
	//������������
	::MoveToEx(hdc, 232, 16, NULL);
	::LineTo(hdc, 232, 336);
	//������� ��������������
	::MoveToEx(hdc, 16, 120, NULL);
	::LineTo(hdc, 336, 120);
	//������ ��������������
	::MoveToEx(hdc, 16, 232, NULL);
	::LineTo(hdc, 336, 232);

	::SelectObject(hdc, (HGDIOBJ)oldPen);
	::DeleteObject(pen);
}

int IsWinner()
{
	static int nPattern[8][3] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		0, 3, 6,
		1, 4, 7,
		2, 5, 8,
		0, 4, 8,
		2, 4, 6
	};

	for (int i = 0; i < 8; i++)
	{
		if ((m_nGameGrid[nPattern[i][0]] == EX) &&
			(m_nGameGrid[nPattern[i][1]] == EX) &&
			(m_nGameGrid[nPattern[i][2]] == EX))
			return EX;
		if ((m_nGameGrid[nPattern[i][0]] == OH) &&
			(m_nGameGrid[nPattern[i][1]] == OH) &&
			(m_nGameGrid[nPattern[i][2]] == OH))
			return OH;
	}
	return 0;
}

BOOL IsDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i] == 0)
			return FALSE;
	}
	return TRUE;
}

void ResetGame()
{
	RECT rect;

	m_nNextChar = EX;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	::GetClientRect(hwndMain, &rect);
	::InvalidateRect(hwndMain, &rect, TRUE);
}

void CheckForGameOver()
{
	int nWinner;

	//������ ������ ��� �����
	if (nWinner = IsWinner())
	{
		MessageBox(hwndMain, ((nWinner == EX) ? _T("�������� ��������!") : _T("�������� ������!")),
			_T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
		ResetGame();
	}
	else if (IsDraw())
	{
		MessageBox(hwndMain, _T("�����!"), _T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
		ResetGame();
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int nPos;

	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		if (m_nNextChar != EX){
		MessageBox(hwnd, TEXT("������ ��� �������"), TEXT("��������!"), 0);	
		return 0;
		}
		nPos = GetRectID(LOWORD(lParam), HIWORD(lParam));
		if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
			return 0;
		m_nGameGrid[nPos] = EX;
		m_nNextChar = OH;
		hdc = ::GetDC(hwndMain);
		DrawX(hdc, nPos);
		CheckForGameOver();
		return 0;

	case WM_RBUTTONDOWN:
		if (m_nNextChar != OH){
			MessageBox(hwnd, TEXT("������ ��� ���������"), TEXT("��������!"), 0);
		return 0;
		}
		nPos = GetRectID(LOWORD(lParam), HIWORD(lParam));
		if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
			return 0;
		m_nGameGrid[nPos] = OH;
		m_nNextChar = EX;
		hdc = ::GetDC(hwndMain);
		DrawO(hdc, nPos);
		CheckForGameOver();
		return 0;

	case WM_MBUTTONDOWN:
		ResetGame();
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);//����� ����
		DrawBoard(hdc);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case 0:
			MessageBox(hwnd, TEXT("������ �� ������� ������ �� ��������� ������ ���� 3�3 ����� (���� ������ ��������, ������ ������ ������). ������, ����������� � ��� 3 ����� ������ �� ���������, ����������� ��� ���������, ����������. ������ ��� ������ �����, �������� ��������. ������� ����� ������ ����, ����� ������ ������ ����"), TEXT("������"), 0);
			break;
		case 1000:
			ResetGame();
			return 0;
		case 1001:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, iMsg, wParam, lParam);
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}


	return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}