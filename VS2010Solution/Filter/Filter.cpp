#include <windows.h> 

HWND	g_hwnd = NULL;		// 对话框全局句柄，用于向对话框传递截取的消息
//HHOOK	g_hMouse = NULL;
HHOOK	g_hKeyboard = NULL;

/*
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* Mouse_Info = (MOUSEHOOKSTRUCT*)lParam;
	if (HC_ACTION == nCode)
		if (WM_LBUTTONDOWN == wParam)
			return 1;
	return CallNextHookEx(g_hMouse, nCode, wParam, lParam);	// 回调
}
*/

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT*)lParam;
	if (HC_ACTION == nCode)
	{
		if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam
			/*|| WM_KEYUP == wParam || WM_SYSKEYUP ==wParam*/)	// 不可加上UP，否者键名不对
		{
			switch(Key_Info->vkCode)
			{
			case VK_LWIN:		// 防止弹出系统菜单
			case VK_RWIN:
			case VK_SNAPSHOT:	// 如果被系统截取，则只有Keyup，没有Keydown，无法变色
			// 屏蔽指示灯
			/*
			case VK_CAPITAL:
			case VK_SCROLL:
			case VK_NUMLOCK:
			*/
			// 屏蔽特殊功能键
			case 0xAD:
			case 0xAE:
			case 0xAF:
			case 0xB0:
			case 0xB1:
			case 0xB2:
			case 0xB3:
			case 0xB5:
			case 0xFF:
				//PostMessage(g_hwnd, WM_KEYDOWN, Key_Info->vkCode, 0);
				PostMessage(g_hwnd, wParam, Key_Info->vkCode, 0);	// 仅把消息传给对话框
				return 1;
			/*
			case VK_INSERT:
				if (Key_Info->flags != KF_EXTENDED)
				{
					PostMessage(g_hwnd, wParam, VK_NUMPAD0, 1);	// 仅把消息传给对话框
					return 1;
				}
				break;
			*/
			}

			/*
			MSG msg;
			//GetMessage(&msg, NULL, 0, 0);
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			PostMessage(g_hwnd, msg.message, msg.wParam, msg.lParam);	// 仅把消息传给对话框
			return 1;
			*/

			/*
			PostMessage(g_hwnd, wParam, Key_Info->vkCode, 0);	// 仅把消息传给对话框
			return 1;
			*/
		}
		/*
		switch (wParam)
		{
		case VK_MENU:
			PostMessage(g_hwnd, WM_KEYDOWN, wParam, 0);	// 仅把消息传给对话框
			return 1;

		}
		*/
	}
	return CallNextHookEx(g_hKeyboard, nCode, wParam, lParam);		// 回调
}

void SetKeyFilter(HWND hwnd)
{
	g_hwnd = hwnd;
	//g_hMouse = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle("Filter"), 0);
	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle("Filter"), 0);
}