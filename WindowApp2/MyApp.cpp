#include "MyApp.h"
#include "MyFrameWnd.h"

// Global application object (bắt buộc với MFC)
MyWinApp theApp;

BOOL MyWinApp::InitInstance()
{
    MyFrameWnd* wndPtr = new MyFrameWnd();          
    m_pMainWnd = wndPtr;

    wndPtr->ShowWindow(SW_SHOW);
    wndPtr->UpdateWindow();

    return TRUE;
}
