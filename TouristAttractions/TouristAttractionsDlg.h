
// TouristAttractionsDlg.h : ͷ�ļ�
//

#pragma once
#include "Graph.h"
#include "afxwin.h"

// CTouristAttractionsDlg �Ի���
class CTouristAttractionsDlg : public CDialogEx
{
// ����
public:
	CTouristAttractionsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOURISTATTRACTIONS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	int nStartVex;
	int nEndVex;
	Graph *graph;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CString m_msg;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_combo1;
	CComboBox m_combo2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
