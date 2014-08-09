// FilePartitionDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "FileOP.h"


// CFilePartitionDlg dialog
class CFilePartitionDlg : public CDialog
{
// Construction
public:
	CFilePartitionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FILEPARTITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtadd();
public:
	CEdit m_AddFilePath;
public:
	CEdit m_SaveFilePath;
public:
	CEdit m_SaveINIPath;
public:
	CEdit m_FileSize;
public:
	CEdit m_FileSPEC;
public:
	CEdit m_FileNum;
public:
	int iOneToMore;
public:
	int iMoreToOne;
public:
	afx_msg void OnBnClickedBtsave();
public:
	afx_msg void OnBnClickedBtsaveini();
public:
	afx_msg void OnBnClickedBtStart();
public:
	afx_msg void OnEnChangeEdspec();
public:
	afx_msg void OnBnClickedRadioOtm();
public:
	afx_msg void OnBnClickedRadioMto();
public:
	void DisRunInfo(CString strInfo);
public:
	CEdit m_RunInfo;
};
