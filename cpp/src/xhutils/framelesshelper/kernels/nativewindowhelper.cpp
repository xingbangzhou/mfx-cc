﻿#include "stable.h"
#include "NativeWindowHelper.h"
#include "NativeWindowHelper_p.h"
#include "NativeWindowFilter.h"

#include <dwmapi.h>
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>

#include <QScreen>
#include <QEvent>
#include <QOperatingSystemVersion>
#include <QOperatingSystemVersion>

// class NativeWindowHelper

bool isCompositionEnabled()
{
    BOOL enabled = FALSE;
    DwmIsCompositionEnabled(&enabled);
    return static_cast<bool>(enabled);
}

void extendFrameIntoClientArea(QWindow* window, int left, int top, int right, int bottom)
{
    MARGINS margins = { left, right, top, bottom };
    DwmExtendFrameIntoClientArea(reinterpret_cast<HWND>(window->winId()), &margins);
}

NativeWindowHelper::NativeWindowHelper(QWindow *window, NativeWindowTester *tester)
    : QObject(window)
    , d_ptr(new NativeWindowHelperPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(NativeWindowHelper);

    Q_CHECK_PTR(window);
    Q_CHECK_PTR(tester);

    d->window = window;
    d->tester = tester;

    if (d->window) {
        d->scaleFactor = d->window->screen()->devicePixelRatio();

        if (d->window->flags() & Qt::FramelessWindowHint) {
            d->window->installEventFilter(this);
            d->updateWindowStyle();
        }
    }
}

NativeWindowHelper::NativeWindowHelper(QWindow *window)
    : QObject(window)
    , d_ptr(new NativeWindowHelperPrivate())
{
    d_ptr->q_ptr = this;

    Q_D(NativeWindowHelper);

    Q_CHECK_PTR(window);
    d->window = window;

    if (d->window) {
        d->scaleFactor = d->window->screen()->devicePixelRatio();

        if (d->window->flags() & Qt::FramelessWindowHint) {
            d->window->installEventFilter(this);
            d->updateWindowStyle();
        }
    }
}

NativeWindowHelper::~NativeWindowHelper()
{
}

bool NativeWindowHelper::nativeEventFilter(void* msg, qintptr* result)
{
    Q_D(NativeWindowHelper);

    Q_CHECK_PTR(d->window);

    LPMSG lpMsg = reinterpret_cast<LPMSG>(msg);
    WPARAM wParam = lpMsg->wParam;
    LPARAM lParam = lpMsg->lParam;

    if (WM_NCHITTEST == lpMsg->message) {
        *result = d->hitTest(GET_X_LPARAM(lParam),
                             GET_Y_LPARAM(lParam));
        return true;
    } else if (WM_NCACTIVATE == lpMsg->message) {
        if (!isCompositionEnabled()) {
            if (result) *result = 1;
            return true;
        }
    } else if (WM_NCCALCSIZE == lpMsg->message) {
        if (TRUE == wParam) {
            if (d->isMaximized()) {
                NCCALCSIZE_PARAMS &params = *reinterpret_cast<NCCALCSIZE_PARAMS *>(lParam);
                RECT g = reinterpret_cast<const NCCALCSIZE_PARAMS*>(lParam)->rgrc[0];
                QMargins m = { 8, 8, 8, 8 };

                params.rgrc[0].top = g.top + m.top();
                params.rgrc[0].left = g.left + m.left();
                params.rgrc[0].right = g.right - m.right();
                params.rgrc[0].bottom = g.bottom - m.bottom();
            }
            
            if (result) *result = 0;
            return true;
        }
    } else if (WM_GETMINMAXINFO == lpMsg->message) {
        //LPMINMAXINFO lpMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lParam);

        //QRect g = d->availableGeometry();
        //QMargins m = d->maximizedMargins();

        //lpMinMaxInfo->ptMaxPosition.x = - m.left();
        //lpMinMaxInfo->ptMaxPosition.y =  - m.top();
        //lpMinMaxInfo->ptMaxSize.x = g.right() - g.left() + 1 + m.left() + m.right();
        //lpMinMaxInfo->ptMaxSize.y = g.bottom() - g.top() + 1 + m.top() + m.bottom();

        //lpMinMaxInfo->ptMinTrackSize.x = d->window->minimumWidth();
        //lpMinMaxInfo->ptMinTrackSize.y = d->window->minimumHeight();
        //lpMinMaxInfo->ptMaxTrackSize.x = d->window->maximumWidth();
        //lpMinMaxInfo->ptMaxTrackSize.y = d->window->maximumHeight();

        if (result) *result = 0;
        return true;
    } else if (WM_NCLBUTTONDBLCLK == lpMsg->message) {
        auto minimumSize = d->window->minimumSize();
        auto maximumSize = d->window->maximumSize();
        if ((minimumSize.width() >= maximumSize.width())
                || (minimumSize.height() >= maximumSize.height())) {
            if (result) *result = 0;
            return true;
        }
    } else if (WM_DPICHANGED == lpMsg->message) {
        qreal old = d->scaleFactor;
        if (HIWORD(wParam) < 144) {
            d->scaleFactor = 1.0;
        } else {
            d->scaleFactor = 2.0;
        }

        if (!qFuzzyCompare(old, d->scaleFactor)) {
            emit scaleFactorChanged(d->scaleFactor);
        }

        auto hWnd = reinterpret_cast<HWND>(d->window->winId());
        auto rect = reinterpret_cast<LPRECT>(lParam);
        SetWindowPos(hWnd,
                     NULL,
                     rect->left,
                     rect->top,
                     rect->right - rect->left,
                     rect->bottom - rect->top,
                     SWP_NOZORDER | SWP_NOACTIVATE);
    }

    return false;
}

bool NativeWindowHelper::eventFilter(QObject *obj, QEvent *ev)
{
    Q_D(NativeWindowHelper);

    if (ev->type() == QEvent::WinIdChange) {
        d->updateWindowStyle();
    } else if (ev->type() == QEvent::Show) {
        d->updateWindowStyle();
    }

    return QObject::eventFilter(obj, ev);
}

qreal NativeWindowHelper::scaleFactor() const
{
    Q_D(const NativeWindowHelper);

    return d->scaleFactor;
}

// class NativeWindowHelperPrivate

NativeWindowHelperPrivate::NativeWindowHelperPrivate()
    : q_ptr(nullptr)
    , window(nullptr)
    , tester(nullptr)
    , oldWindow(NULL)
    , scaleFactor(1.0)
{
}

NativeWindowHelperPrivate::~NativeWindowHelperPrivate()
{
    if (window)
        NativeWindowFilter::deliver(window, nullptr);
}

void NativeWindowHelperPrivate::updateWindowStyle()
{
    Q_Q(NativeWindowHelper);

    Q_CHECK_PTR(window);

    HWND hWnd = reinterpret_cast<HWND>(window->winId());
    if (NULL == hWnd)
        return;
    else if (oldWindow == hWnd) {
        return;
    }
    oldWindow = hWnd;

    NativeWindowFilter::deliver(window, q);

    QOperatingSystemVersion currentVersion = QOperatingSystemVersion::current();
    if (currentVersion < QOperatingSystemVersion::Windows8) {
        return;
    }

    LONG oldStyle = WS_OVERLAPPEDWINDOW | WS_THICKFRAME
            | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;;
    LONG newStyle = WS_POPUP            | WS_THICKFRAME;

    if (isCompositionEnabled())
        newStyle |= WS_CAPTION;

    if (window->flags() & Qt::CustomizeWindowHint) {
        if (window->flags() & Qt::WindowSystemMenuHint)
            newStyle |= WS_SYSMENU;
        if (window->flags() & Qt::WindowMinimizeButtonHint)
            newStyle |= WS_MINIMIZEBOX;
        if (window->flags() & Qt::WindowMaximizeButtonHint)
            newStyle |= WS_MAXIMIZEBOX;
    } else {
        newStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    }

    LONG currentStyle = GetWindowLong(hWnd, GWL_STYLE);
    SetWindowLong(hWnd, GWL_STYLE, (currentStyle & ~oldStyle) | newStyle);

    SetWindowPos(hWnd, NULL, 0, 0, 0 , 0,
                 SWP_NOOWNERZORDER | SWP_NOZORDER |
                 SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

    if (isCompositionEnabled())
        extendFrameIntoClientArea(window, 1, 1, 1, 1);
}

int NativeWindowHelperPrivate::hitTest(int x, int y) const
{
    Q_CHECK_PTR(window);

    enum RegionMask {
        Client = 0x0000,
        Top    = 0x0001,
        Left   = 0x0010,
        Right  = 0x0100,
        Bottom = 0x1000,
    };

    auto fmgeo = window->frameGeometry();
    QMargins margins = draggableMargins();

    int top = margins.top();
    int left = margins.left();
    int right = margins.right();
    int bottom = margins.bottom();

    if (top <= 0)
        top = GetSystemMetrics(SM_CYFRAME);
    if (left <= 0)
        left = GetSystemMetrics(SM_CXFRAME);
    if (right <= 0)
        right = GetSystemMetrics(SM_CXFRAME);
    if (bottom <= 0)
        bottom = GetSystemMetrics(SM_CYFRAME);

    int result = 0;
    if (y < (fmgeo.top() + top))
        result |= Top;
    if (x < (fmgeo.left() + left))
        result |= Left;
    if (x > (fmgeo.right() - right))
        result |= Right;
    if (y > (fmgeo.bottom() - bottom))
        result |= Bottom;

    bool wResizable = window->minimumWidth() < window->maximumWidth();
    bool hResizable = window->minimumHeight() < window->maximumHeight();

    switch (result) {
    case Top | Left    : return wResizable && hResizable ? HTTOPLEFT     : HTCLIENT;
    case Top           : return hResizable               ? HTTOP         : HTCLIENT;
    case Top | Right   : return wResizable && hResizable ? HTTOPRIGHT    : HTCLIENT;
    case Right         : return wResizable               ? HTRIGHT       : HTCLIENT;
    case Bottom | Right: return wResizable && hResizable ? HTBOTTOMRIGHT : HTCLIENT;
    case Bottom        : return hResizable               ? HTBOTTOM      : HTCLIENT;
    case Bottom | Left : return wResizable && hResizable ? HTBOTTOMLEFT  : HTCLIENT;
    case Left          : return wResizable               ? HTLEFT        : HTCLIENT;
    }

    auto pos = window->mapFromGlobal(QPoint(x, y));
    return ((nullptr != tester) && !tester->hitTest(pos)) ? HTCLIENT : HTCAPTION;
}

bool NativeWindowHelperPrivate::isMaximized() const
{
    Q_CHECK_PTR(window);

    HWND hWnd = reinterpret_cast<HWND>(window->winId());
    if (NULL == hWnd)
        return false;

    WINDOWPLACEMENT windowPlacement;
    if (!GetWindowPlacement(hWnd, &windowPlacement))
        return false;

    return (SW_MAXIMIZE == windowPlacement.showCmd);
}

QMargins NativeWindowHelperPrivate::draggableMargins() const
{
    return tester ? tester->draggableMargins() * scaleFactor : QMargins();
}

QMargins NativeWindowHelperPrivate::maximizedMargins() const
{
    return tester ? tester->maximizedMargins() * scaleFactor : QMargins();
}

QRect NativeWindowHelperPrivate::availableGeometry() const
{
    MONITORINFO mi{0};
    mi.cbSize = sizeof(MONITORINFO);

    auto hWnd = reinterpret_cast<HWND>(window->winId());
    auto hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    if (!hMonitor || !GetMonitorInfoW(hMonitor, &mi)) {
        Q_ASSERT(NULL != hMonitor);
        return window->screen()->availableGeometry();
    }

    return QRect(mi.rcWork.left, mi.rcWork.top, mi.rcWork.right - mi.rcWork.left, mi.rcWork.bottom - mi.rcWork.top);
}
