#include <afxwin.h>

// Định nghĩa ID cho button
#define IDC_MY_BUTTON  1001
#define IDC_MY_BUTTON2  1002

class MyFrameWnd : public CFrameWnd {
private:
    HBRUSH m_hBackgroundBrush;  // Brush để vẽ nền
    int    m_nBackgroundColor;  // 0: xám, 1: xanh, 2: đỏ

public:
    int nWindowWidth = 1024;
    int nWindowHeight = (int)(nWindowWidth / 1.618);

    // Button control
    CButton m_btnClickMe;
    CButton m_btnDemo;

    MyFrameWnd() : m_hBackgroundBrush(NULL), m_nBackgroundColor(0) {
        // Đăng ký class với background mặc định
        CString strMyClass = AfxRegisterWndClass(
            CS_HREDRAW | CS_VREDRAW,
            AfxGetApp()->LoadStandardCursor(IDC_ARROW),
            (HBRUSH)::GetStockObject(LTGRAY_BRUSH),
            AfxGetApp()->LoadStandardIcon(IDI_EXCLAMATION)
        );

        // Tạo window
        Create(strMyClass,
            L"First MFC Program",
            WS_OVERLAPPEDWINDOW,
            CRect(100, 100, 100 + nWindowWidth, 100 + nWindowHeight),
            NULL,
            NULL);

        // Tạo button
        m_btnClickMe.Create(L"Change Background",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            CRect(10, 10, 200, 50),
            this,
            IDC_MY_BUTTON);

        m_btnDemo.Create(L"Hung Handsome",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            CRect(10, 60, 200, 100),
            this,
            IDC_MY_BUTTON2);
    }

    ~MyFrameWnd() {
        // Dọn dẹp brush
        if (m_hBackgroundBrush != NULL) {
            DeleteObject(m_hBackgroundBrush);
        }
    }

    // Hàm thay đổi màu nền
    void SetBackgroundColor(int nColor) {
        m_nBackgroundColor = nColor;

        // Xóa brush cũ nếu có
        if (m_hBackgroundBrush != NULL) {
            DeleteObject(m_hBackgroundBrush);
            m_hBackgroundBrush = NULL;
        }

        // Tạo brush mới theo màu được chọn
        switch (nColor) {
        case 1:  // Màu xanh lá
            m_hBackgroundBrush = ::CreateSolidBrush(RGB(144, 238, 144));  // LightGreen
            break;
        case 2:  // Màu đỏ
            m_hBackgroundBrush = ::CreateSolidBrush(RGB(255, 182, 193));  // LightPink
            break;
        default: // Màu xám (0)
            m_hBackgroundBrush = ::CreateSolidBrush(RGB(211, 211, 211));  // LightGray
            break;
        }

        // Yêu cầu vẽ lại cửa sổ
        Invalidate();
        UpdateWindow();
    }

    // Xử lý vẽ nền (để thay đổi màu)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC) {
        CRect rect;
        GetClientRect(&rect);

        // Tô nền bằng brush hiện tại
        if (m_hBackgroundBrush != NULL) {
            CBrush* pOldBrush = pDC->SelectObject(CBrush::FromHandle(m_hBackgroundBrush));
            pDC->FillRect(&rect, CBrush::FromHandle(m_hBackgroundBrush));
            pDC->SelectObject(pOldBrush);
        }
        else {
            // Mặc định nền xám
            pDC->FillSolidRect(&rect, RGB(211, 211, 211));
        }

        return TRUE;  // Đã xử lý, không cần xử lý mặc định
    }

    // Xử lý vẽ (text)
    afx_msg void OnPaint() {
        CPaintDC dc(this);

        // Hiển thị màu nền hiện tại
        CString strColor;
        switch (m_nBackgroundColor) {
        case 1: strColor = L"Green (You pressed OK)"; break;
        case 2: strColor = L"Red (You pressed Cancel)"; break;
        default: strColor = L"Gray (Default)"; break;
        }

        CRect rect;
        GetClientRect(&rect);

        // Vẽ text ở giữa cửa sổ
        CString strText;
        strText.Format(L"Current Background: %s\nClick button to change!", strColor);

        dc.SetBkMode(TRANSPARENT);  // Nền text trong suốt
        dc.TextOut(50, 50, strText);
    }

    // Xử lý khi click button
    afx_msg void OnBnClickedButton() {
        // Hiển thị message box với OK và Cancel
        int nResult = MessageBox(L"Do you want to change background color?",
            L"Confirmation",
            MB_OKCANCEL | MB_ICONQUESTION);

        // Dựa vào lựa chọn của người dùng để thay đổi màu nền
        if (nResult == IDOK) {
            SetBackgroundColor(1);  // Màu xanh lá
        }
        else if (nResult == IDCANCEL) {
            SetBackgroundColor(2);  // Màu đỏ
        }
    }

    // Xử lý resize (tự động căn chỉnh button)
    afx_msg void OnSize(UINT nType, int cx, int cy) {
        CFrameWnd::OnSize(nType, cx, cy);

        // Cập nhật vị trí button (góc dưới bên phải)
        if (m_btnClickMe.m_hWnd != NULL) {
            int btnWidth = 180, btnHeight = 35;
            int nX = cx - btnWidth - 20;
            int nY = cy - btnHeight - 20;
            m_btnClickMe.SetWindowPos(NULL, nX, nY, btnWidth, btnHeight, SWP_NOZORDER);
        }

        // Yêu cầu vẽ lại (cập nhật text)
        Invalidate();
    }

    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_BN_CLICKED(IDC_MY_BUTTON, &MyFrameWnd::OnBnClickedButton)
    ON_BN_CLICKED(IDC_MY_BUTTON2, &MyFrameWnd::OnBnClickedButton)
END_MESSAGE_MAP()

class MyWinApp : public CWinApp {
public:
    BOOL InitInstance() {
        MyFrameWnd* wndPtr = new MyFrameWnd();
        m_pMainWnd = wndPtr;

        wndPtr->ShowWindow(SW_SHOW);
        wndPtr->UpdateWindow();
        return TRUE;
    }
};

MyWinApp theApp;