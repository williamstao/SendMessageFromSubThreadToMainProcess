#pragma once

#include <windows.h>
#include <memory>
#include <stdint.h>
#include <functional>

typedef std::function<void(int notifyType, const uint8_t* data, uint32_t dataLen)> NotifyHandler;

class MsgWnd
{
	typedef MsgWnd self;
public:
	MsgWnd();
	~MsgWnd();
private:
	MsgWnd(const MsgWnd&);
public:
	bool Create();
	void SetHandler(NotifyHandler handler);
	void Close();
	HWND GetHwnd() const;

private:
	static LRESULT WINAPI _WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
	void OnWindowMessage_WM_COPYDATA(ULONG_PTR dwNotifyType, const char* pData, DWORD dwDataLen);
private:
	HWND m_hwnd;
	NotifyHandler m_handler;
};