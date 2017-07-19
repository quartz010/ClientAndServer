// Win32Project3.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Win32Project3.h"


// 这是导出变量的一个示例
WIN32PROJECT3_API int nWin32Project3=0;

// 这是导出函数的一个示例。
WIN32PROJECT3_API int fnWin32Project3(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Win32Project3.h
CWin32Project3::CWin32Project3()
{
    return;
}
