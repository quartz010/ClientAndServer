// Win32Project3.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Win32Project3.h"


// ���ǵ���������һ��ʾ��
WIN32PROJECT3_API int nWin32Project3=0;

// ���ǵ���������һ��ʾ����
WIN32PROJECT3_API int fnWin32Project3(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� Win32Project3.h
CWin32Project3::CWin32Project3()
{
    return;
}
