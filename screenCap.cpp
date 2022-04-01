#include <atlsafe.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <atlimage.h>
#include <ctime>
#include "Console.h"
#include "Patch.h"

namespace screenCap {

    void sendKeyDown(unsigned char keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;

        input.ki.wVk = keyCode;
        input.ki.dwFlags = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;

        SendInput(1, &input, sizeof(INPUT));
    }

    void sendKeyUp(unsigned char keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;

        input.ki.wVk = keyCode;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;

        SendInput(1, &input, sizeof(INPUT));
    }

    void TakeScreenShot()
    {
        //Printscreen 1 screen
        sendKeyDown(VK_MENU);
        sendKeyDown(VK_SNAPSHOT);
        sendKeyUp(VK_MENU);
        sendKeyUp(VK_SNAPSHOT);

        Sleep(100);
        //
        OpenClipboard(NULL);
        //Copy the clipboard to the bitmap handler
        HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);

        TCHAR szName[MAX_PATH] = { 0 };
        SYSTEMTIME st = { 0 };
        ::GetLocalTime(&st);
        _stprintf(szName, _T("./temp/%02d-%02d-%02d-%02d-%02d-%02d.bmp"), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
        CImage image;
        image.Attach(hBitmap);
        image.Save(szName, Gdiplus::ImageFormatBMP);
        CloseClipboard();
    }

    BuiltInFunction("screenshot", _scrnshot) {
        TakeScreenShot();
        return "true";
    }
}