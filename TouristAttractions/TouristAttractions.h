
// TouristAttractions.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTouristAttractionsApp: 
// �йش����ʵ�֣������ TouristAttractions.cpp
//

class CTouristAttractionsApp : public CWinApp
{
public:
	CTouristAttractionsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTouristAttractionsApp theApp;