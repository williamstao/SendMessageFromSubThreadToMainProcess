#include<stdlib.h>
#include<stdio.h>
#include<io.h>
#include<windows.h>
#include"msg_wnd.h"
#include"message_engine.h"
#include"main.h"
#include"task.h"

MSG msg;
MainDisPatcher md;
int initialize()
{
	std::shared_ptr<MsgWnd> msgWnd(new MsgWnd());
	if (!msgWnd->Create())
	{
		printf("Init app create message window error");
		return -1;
	}
	ClientEngine::GetInstance()->InitApp(msgWnd);

	return 0;
}

void genTask(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			const char* path = argv[i];
			if (_access(path, 0) != 0)
			{
				continue;
			}
			Task* task = new Task(std::string(path));
			task->RetrieveRequest();
		}
	}
	else
	{
		printf("please input filePath\n");
	}
}

int main(int argc, char* argv[])
{
	int err = initialize();
	if (err != 0)
	{
		return -1;
	}

	genTask(argc, argv);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	system("pause");
	return 0;
}