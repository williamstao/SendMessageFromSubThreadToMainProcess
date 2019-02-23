#pragma once
#include "msg_wnd.h"

MsgWnd::MsgWnd() :m_hwnd(NULL)
{

}

MsgWnd::~MsgWnd()
{
	Close();
}

bool MsgWnd::Create()
{
	if (m_hwnd != NULL)
	{
		return true;
	}

	std::string lpClassName = "ClientMsgWndClass";
	std::string lpWindowName = "ClientMsgWnd";

	LPCSTR wc_name = lpClassName.c_str();
	LPCTSTR win_name = lpWindowName.c_str();

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	if (!GetClassInfoEx(GetModuleHandle(NULL), wc_name, &wc))
	{
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = wc_name;
		wc.cbWndExtra = sizeof(void*);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpfnWndProc = &self::_WndProc;
		ATOM atom = RegisterClassEx(&wc);
		if (atom == 0)
		{
			return false;
		}
	}

	HWND hwnd = CreateWindowEx(0, wc.lpszClassName, win_name, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, this);
	if (hwnd == NULL)
	{
		return false;
	}
	m_hwnd = hwnd;
	return true;
}

HWND MsgWnd::GetHwnd() const
{
	return m_hwnd;
}

LRESULT WINAPI MsgWnd::_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)(cs->lpCreateParams));
	}

	self* _this = (self*)GetWindowLongPtr(hwnd, GWL_USERDATA);
	if (_this)
	{
		BOOL handled = FALSE;
		LRESULT ret = _this->OnWindowMessage(msg, wParam, lParam, handled);
		if (handled)
		{
			return ret;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT MsgWnd::OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	if (msg == WM_COPYDATA)
	{
		handled = TRUE;
		PCOPYDATASTRUCT pCD = (PCOPYDATASTRUCT)lParam;
		OnWindowMessage_WM_COPYDATA(pCD->dwData, (const char*)pCD->lpData, pCD->cbData);
		return 0;
	}
	return 0;
}

void MsgWnd::OnWindowMessage_WM_COPYDATA(ULONG_PTR dwNotifyType, const char* pData, DWORD dwDataLen)
{
	if (pData == NULL || dwDataLen == 0) 
	{
		return;
	}

	if (m_handler) 
	{
		m_handler((int)dwNotifyType, (const uint8_t*)pData, (uint32_t)dwDataLen);
	}
}

void MsgWnd::SetHandler(NotifyHandler handler)
{
	m_handler = handler;
}

void MsgWnd::Close()
{
	if (m_hwnd)
	{
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;
	}
}