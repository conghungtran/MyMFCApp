#include "MyFrameWnd.h"

// -------------------------------------------------------
// Message Map
// -------------------------------------------------------
BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_BN_CLICKED(IDC_MY_BUTTON, &MyFrameWnd::OnBnClickedButton)
END_MESSAGE_MAP()

// -------------------------------------------------------
// Constructor / Destructor
// -------------------------------------------------------
MyFrameWnd::MyFrameWnd()
    : m_hBackgroundBrush(NULL), m_nBackgroundColor(0)
{
    // Đăng ký Window Class
    CString strMyClass = AfxRegisterWndClass(
        CS_HREDRAW | CS_VREDRAW,
        AfxGetApp()->LoadStandardCursor(IDC_ARROW),
        (HBRUSH)::GetStockObject(LTGRAY_BRUSH),
        AfxGetApp()->LoadStandardIcon(IDI_EXCLAMATION)
    );

    // Tạo cửa sổ chính
    Create(strMyClass,
        L"First MFC Program",
        WS_OVERLAPPEDWINDOW,
        CRect(100, 100, 100 + nWindowWidth, 100 + nWindowHeight),
        NULL,
        NULL);

    // Tạo Button 1
    m_btnClickMe.Create(L"Change Background",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(10, 10, 200, 50),
        this,
        IDC_MY_BUTTON);
}

MyFrameWnd::~MyFrameWnd()
{
    if (m_hBackgroundBrush != NULL) {
        DeleteObject(m_hBackgroundBrush);
    }
}

// -------------------------------------------------------
// SetBackgroundColor
// -------------------------------------------------------
void MyFrameWnd::SetBackgroundColor(int nColor)
{
    m_nBackgroundColor = nColor;

    // Giải phóng brush cũ
    if (m_hBackgroundBrush != NULL) {
        DeleteObject(m_hBackgroundBrush);
        m_hBackgroundBrush = NULL;
    }

    // Tạo brush mới
    switch (nColor) {
    case 1:  // Xanh lá
        m_hBackgroundBrush = ::CreateSolidBrush(RGB(144, 238, 144));
        break;
    case 2:  // Đỏ / hồng
        m_hBackgroundBrush = ::CreateSolidBrush(RGB(255, 182, 193));
        break;
    default: // Xám (0)
        m_hBackgroundBrush = ::CreateSolidBrush(RGB(211, 211, 211));
        break;
    }

    Invalidate();
    UpdateWindow();
}

// -------------------------------------------------------
// OnEraseBkgnd – tô màu nền
// -------------------------------------------------------
BOOL MyFrameWnd::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);

    if (m_hBackgroundBrush != NULL) {
        CBrush* pOldBrush = pDC->SelectObject(CBrush::FromHandle(m_hBackgroundBrush));
        pDC->FillRect(&rect, CBrush::FromHandle(m_hBackgroundBrush));
        pDC->SelectObject(pOldBrush);
    }
    else {
        pDC->FillSolidRect(&rect, RGB(211, 211, 211));
    }

    return TRUE;
}

// -------------------------------------------------------
// OnPaint – hiển thị text trạng thái
// -------------------------------------------------------
void MyFrameWnd::OnPaint()
{
    CPaintDC dc(this);

    CString strColor;
    switch (m_nBackgroundColor) {
    case 1:  strColor = L"Green (You pressed OK)";     break;
    case 2:  strColor = L"Red (You pressed Cancel)";   break;
    default: strColor = L"Gray (Default)";             break;
    }

    CString strText;
    strText.Format(L"Current Background: %s\nClick button to change!", strColor);

    dc.SetBkMode(TRANSPARENT);
    dc.TextOut(50, 50, strText);
}

// -------------------------------------------------------
// OnBnClickedButton – xử lý click button
// -------------------------------------------------------
void MyFrameWnd::OnBnClickedButton()
{
    int nResult = MessageBox(
        L"Do you want to change background color?",
        L"Confirmation",
        MB_OKCANCEL | MB_ICONQUESTION);

    if (nResult == IDOK)
        SetBackgroundColor(1);  // Xanh lá
    else if (nResult == IDCANCEL)
        SetBackgroundColor(2);  // Đỏ / hồng
}

// -------------------------------------------------------
// OnSize – căn chỉnh button khi resize
// -------------------------------------------------------
void MyFrameWnd::OnSize(UINT nType, int cx, int cy)
{
    CFrameWnd::OnSize(nType, cx, cy);

    if (m_btnClickMe.m_hWnd != NULL) {
        int btnWidth = 180;
        int btnHeight = 35;
        int nX = cx - btnWidth - 20;
        int nY = cy - btnHeight - 20;
        m_btnClickMe.SetWindowPos(NULL, nX, nY, btnWidth, btnHeight, SWP_NOZORDER);
    }

    Invalidate();
}
