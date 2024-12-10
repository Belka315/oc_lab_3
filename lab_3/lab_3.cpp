#include <windows.h>

// Глобальные переменные
int win_count = 2;   // количество окон, если=0 => завершение программы

// Прототипы функций
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

// Основная функция
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t* szClassName = L"lab3";
    const wchar_t* szClassName1 = L"lab31";
    WNDCLASSEX wndClass, wndClass1;
    HWND hWnd, hWnd1;
    MSG msg;

    // Заполнение описания оконного класса первого окна
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = szClassName;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wndClass);

    // Заполнение описания оконного класса второго окна
    wndClass1.cbSize = sizeof(WNDCLASSEX);
    wndClass1.style = CS_HREDRAW | CS_VREDRAW;
    wndClass1.lpfnWndProc = WndProc;
    wndClass1.cbClsExtra = 0;
    wndClass1.cbWndExtra = 0;
    wndClass1.hInstance = hInstance;
    wndClass1.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass1.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass1.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass1.lpszMenuName = NULL;
    wndClass1.lpszClassName = szClassName1;
    wndClass1.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wndClass1);

    // Создание окон
    hWnd = CreateWindow(
        szClassName,
        L"",
        WS_POPUP | WS_DLGFRAME,
        200, 50, 300, 300,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, SW_SHOW);

    hWnd1 = CreateWindow(
        szClassName1,
        L"",
        WS_POPUP | WS_DLGFRAME,
        600, 50, 300, 300,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd1, SW_SHOW);

    // Основной цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Оконная процедура
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    switch (Msg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);
        // Рисование клиентской области
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        win_count--;
        if (win_count <= 0) {
            PostQuitMessage(0);
        }
        break;

    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    return 0;
}