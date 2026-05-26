#pragma once
#include <afxwin.h>
#include "Resource.h"

class MyFrameWnd : public CFrameWnd {
private:
    HBRUSH m_hBackgroundBrush;
    int    m_nBackgroundColor;


public:
    int nWindowWidth = 1024;
    int nWindowHeight = (int)(nWindowWidth / 1.618);

    // Button controls
    CButton m_btnClickMe;

    MyFrameWnd();
    virtual ~MyFrameWnd();

    void SetBackgroundColor(int nColor);

protected:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg void OnBnClickedButton();
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()
};
