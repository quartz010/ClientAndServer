// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WIN32PROJECT3_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WIN32PROJECT3_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef WIN32PROJECT3_EXPORTS
#define WIN32PROJECT3_API __declspec(dllexport)
#else
#define WIN32PROJECT3_API __declspec(dllimport)
#endif

// �����Ǵ� Win32Project3.dll ������
class WIN32PROJECT3_API CWin32Project3 {
public:
	CWin32Project3(void);
	// TODO:  �ڴ�������ķ�����
};

extern WIN32PROJECT3_API int nWin32Project3;

WIN32PROJECT3_API int fnWin32Project3(void);
