#include <windows.h> 

HWND	g_hwnd = NULL;		// �Ի���ȫ�־����������Ի��򴫵ݽ�ȡ����Ϣ
//HHOOK	g_hMouse = NULL;
HHOOK	g_hKeyboard = NULL;

/*
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* Mouse_Info = (MOUSEHOOKSTRUCT*)lParam;
	if (HC_ACTION == nCode)
		if (WM_LBUTTONDOWN == wParam)
			return 1;
	return CallNextHookEx(g_hMouse, nCode, wParam, lParam);	// �ص�
}
*/

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT*)lParam;
	if (HC_ACTION == nCode)
	{
		if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam
			/*|| WM_KEYUP == wParam || WM_SYSKEYUP ==wParam*/)	// ���ɼ���UP�����߼�������
		{
			switch(Key_Info->vkCode)
			{
			case VK_LWIN:		// ��ֹ����ϵͳ�˵�
			case VK_RWIN:
			case VK_SNAPSHOT:	// �����ϵͳ��ȡ����ֻ��Keyup��û��Keydown���޷���ɫ
			// ����ָʾ��
			/*
			case VK_CAPITAL:
			case VK_SCROLL:
			case VK_NUMLOCK:
			*/
			// �������⹦�ܼ�
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
				PostMessage(g_hwnd, wParam, Key_Info->vkCode, 0);	// ������Ϣ�����Ի���
				return 1;
			/*
			case VK_INSERT:
				if (Key_Info->flags != KF_EXTENDED)
				{
					PostMessage(g_hwnd, wParam, VK_NUMPAD0, 1);	// ������Ϣ�����Ի���
					return 1;
				}
				break;
			*/
			}

			/*
			MSG msg;
			//GetMessage(&msg, NULL, 0, 0);
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			PostMessage(g_hwnd, msg.message, msg.wParam, msg.lParam);	// ������Ϣ�����Ի���
			return 1;
			*/

			/*
			PostMessage(g_hwnd, wParam, Key_Info->vkCode, 0);	// ������Ϣ�����Ի���
			return 1;
			*/
		}
		/*
		switch (wParam)
		{
		case VK_MENU:
			PostMessage(g_hwnd, WM_KEYDOWN, wParam, 0);	// ������Ϣ�����Ի���
			return 1;

		}
		*/
	}
	return CallNextHookEx(g_hKeyboard, nCode, wParam, lParam);		// �ص�
}

void SetKeyFilter(HWND hwnd)
{
	g_hwnd = hwnd;
	//g_hMouse = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle("Filter"), 0);
	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle("Filter"), 0);
}