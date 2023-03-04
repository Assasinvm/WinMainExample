#include <windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow){

    try {
        WNDCLASSEX wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
        wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wcex.lpszClassName = TEXT("MyWndClass");

        if(!RegisterClassEx(&wcex)){
            throw std::runtime_error("ERROR: Can't register window Class!!!");
        }

        HWND hWnd = CreateWindow(
                TEXT("MyWndClass"),
                TEXT("Title"),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                1920,
                1080,
                NULL,
                NULL,
                hInstance,
                NULL
                );

        if(!hWnd){
            throw std::runtime_error("ERROR: Can't create window!!!");
        }

        ShowWindow(hWnd, SW_SHOWNORMAL);

        MSG msg = {};

        while (true){
            if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
				
				//loop
				
                if(msg.message == WM_QUIT){
                    break;
                }
            }
        }

    } catch (std::exception const &e) {
        printf(e.what());
        system("pause");
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message) {
        case WM_DESTROY:
			//close programm
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}