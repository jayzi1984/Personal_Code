// CreateTable.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreateTableApp:
// �йش����ʵ�֣������ CreateTable.cpp
//

class CCreateTableApp : public CWinApp
{
public:
	CCreateTableApp();

// ��д
	public:
	virtual BOOL InitInstance();

private:
   ULONG_PTR							m_gdiplusToken ;//Gdiplusϵͳ����

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCreateTableApp theApp;