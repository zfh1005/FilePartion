// FilePartitionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FilePartition.h"
#include "FilePartitionDlg.h"
#include "shlwapi.h"
#include <stdlib.h>
#include <stdio.h>





#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFilePartitionDlg dialog

FileOP cFileOP;


CFilePartitionDlg::CFilePartitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilePartitionDlg::IDD, pParent)
	, iOneToMore(0)
	, iMoreToOne(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFilePartitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDFILEPATH, m_AddFilePath);
	DDX_Control(pDX, IDC_EDSAVEPATH, m_SaveFilePath);
	DDX_Control(pDX, IDC_EDINI, m_SaveINIPath);
	DDX_Control(pDX, IDC_EDSIZE, m_FileSize);
	DDX_Control(pDX, IDC_EDSPEC, m_FileSPEC);
	DDX_Control(pDX, IDC_EDNUM, m_FileNum);
	DDX_Control(pDX, IDC_EDRUNINFO, m_RunInfo);
}

BEGIN_MESSAGE_MAP(CFilePartitionDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTADD, &CFilePartitionDlg::OnBnClickedBtadd)
	ON_BN_CLICKED(IDC_BTSAVE, &CFilePartitionDlg::OnBnClickedBtsave)
	ON_BN_CLICKED(IDC_BTSAVEINI, &CFilePartitionDlg::OnBnClickedBtsaveini)
	ON_BN_CLICKED(IDC_BT_START, &CFilePartitionDlg::OnBnClickedBtStart)
	ON_EN_CHANGE(IDC_EDSPEC, &CFilePartitionDlg::OnEnChangeEdspec)
	ON_BN_CLICKED(IDC_RADIO_OTM, &CFilePartitionDlg::OnBnClickedRadioOtm)
	ON_BN_CLICKED(IDC_RADIO_MTO, &CFilePartitionDlg::OnBnClickedRadioMto)
END_MESSAGE_MAP()


// CFilePartitionDlg message handlers

BOOL CFilePartitionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFilePartitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFilePartitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFilePartitionDlg::OnBnClickedBtadd()
{
	char buf[MAX_PATH];
	ZeroMemory(buf,MAX_PATH);

    BROWSEINFO bi;
	bi.hwndOwner=GetSafeHwnd();
	bi.pidlRoot=NULL;
	bi.lpszTitle="Choose a file";
	bi.ulFlags=BIF_BROWSEINCLUDEFILES;
	bi.lpfn=NULL;
	bi.iImage=0;
	bi.lParam=0;
	bi.pszDisplayName=buf;

	LPITEMIDLIST plist=NULL;
	if((plist=SHBrowseForFolder(&bi))!=NULL)
	{
		char cPath[MAX_PATH];
		ZeroMemory(cPath,MAX_PATH);
		SHGetPathFromIDList(plist,cPath);
		m_AddFilePath.SetWindowText(cPath);		
		if(PathIsDirectory(cPath))
		{
			AfxMessageBox("You need choose a file, not a path, please check.");	
			return;
		}
		else
		{
			ULONGLONG iFileSize;
			iFileSize = cFileOP.bGetFileSize(cPath);
			char cPathFileSize[MAX_PATH];
			memset(cPathFileSize, 0, MAX_PATH);
			sprintf_s(cPathFileSize, MAX_PATH, "%u", iFileSize);
			m_FileSize.SetWindowText(cPathFileSize);			
		}
		
	}
	return ;
}

void CFilePartitionDlg::OnBnClickedBtsave()
{
	char buf[MAX_PATH];
	ZeroMemory(buf,MAX_PATH);

    BROWSEINFO bi;
	bi.hwndOwner=GetSafeHwnd();
	bi.pidlRoot=NULL;
	bi.lpszTitle="Choose a path";
	bi.ulFlags=BIF_EDITBOX;
	bi.lpfn=NULL;
	bi.iImage=0;
	bi.lParam=0;
	bi.pszDisplayName=buf;

	LPITEMIDLIST plist=NULL;
	if((plist=SHBrowseForFolder(&bi))!=NULL)
	{
		char cPath[MAX_PATH];
		ZeroMemory(cPath,MAX_PATH);
		SHGetPathFromIDList(plist,cPath);
		m_SaveFilePath.SetWindowText(cPath);
		if(!PathIsDirectory(cPath))
		{
			AfxMessageBox("You need choose a path, not a file, please check.");	
			return;
		}
		else
		{
			if(CreateDirectory(cPath, NULL) || (GetLastError() == ERROR_ALREADY_EXISTS))
			{
				
			}
			else
			{
				AfxMessageBox("Created File save directory fail, please check.");	
			}
			
		}
	}

}

void CFilePartitionDlg::OnBnClickedBtsaveini()
{
	char buf[MAX_PATH];
	ZeroMemory(buf,MAX_PATH);

    BROWSEINFO bi;
	bi.hwndOwner=GetSafeHwnd();
	bi.pidlRoot=NULL;
	bi.lpszTitle="Choose a path";
	bi.ulFlags=BIF_EDITBOX;
	bi.lpfn=NULL;
	bi.iImage=0;
	bi.lParam=0;
	bi.pszDisplayName=buf;

	LPITEMIDLIST plist=NULL;
	if((plist=SHBrowseForFolder(&bi))!=NULL)
	{
		char cPath[MAX_PATH];
		ZeroMemory(cPath,MAX_PATH);
		SHGetPathFromIDList(plist,cPath);
		m_SaveINIPath.SetWindowText(cPath);
		if(!PathIsDirectory(cPath))
		{
			AfxMessageBox("You need choose a path, not a file, please check.");	
			return;
		}
		else
		{
			char cSaveFileName[MAX_PATH];
			memset(cSaveFileName, 0, MAX_PATH);
			sprintf_s(cSaveFileName, MAX_PATH, "%s\\%s", cPath, "FilePartitionSaveInformation.ini");			
			if ( !cFileOP.Open( cSaveFileName, CFile::modeCreate |   
							CFile::modeReadWrite, &cFileOP.fileException ) )
			{
				TRACE( "Can't open file %s, error = %u\n",
					cSaveFileName, cFileOP.fileException.m_cause );
			}
			cFileOP.Close();
			m_SaveINIPath.SetWindowText(cSaveFileName);

		}
	}
}

void CFilePartitionDlg::OnBnClickedBtStart()
{
	CFile *cReadFile;
	CFile *cWirteFile;
	DWORD iReadlen;
	DWORD iPostlen;
	DWORD iPartSizeSPEC;
	CString strFileSize;
	CString strFileSizeSPEC;
	CString strFileNum;
	CString strFilePath;
	CString strFileSavePath;
	CString strFileSaveIniPath;
	
	GetDlgItem(IDC_BT_START)->EnableWindow(false);
	GetDlgItem(IDC_BTADD)->EnableWindow(false);
	GetDlgItem(IDC_BTSAVE)->EnableWindow(false);
	GetDlgItem(IDC_BTSAVEINI)->EnableWindow(false);
	GetDlgItem(IDC_EDSPEC)->EnableWindow(false);
	GetDlgItem(IDC_RADIO_OTM)->EnableWindow(false);	
	GetDlgItem(IDC_RADIO_MTO)->EnableWindow(false);
	GetDlgItem(IDC_EDRUNINFO)->EnableWindow(false);
	

	//get file size SPEC
	GetDlgItem(IDC_EDSPEC)->GetWindowText(strFileSizeSPEC);
	if(strFileSizeSPEC.IsEmpty())
	{
		AfxMessageBox("File SPEC is empty, it's must have a value, please check.");
		return;
	}
	iPartSizeSPEC = atol(strFileSizeSPEC);
	
	//get file path
	GetDlgItem(IDC_EDFILEPATH)->GetWindowText(strFilePath);
	if(strFilePath.IsEmpty())
	{
		AfxMessageBox("File path is empty, please check.");
		return;
	}

	//get save file path
	GetDlgItem(IDC_EDSAVEPATH)->GetWindowText(strFileSavePath);
	if(strFileSavePath.IsEmpty())
	{
		AfxMessageBox("File save path is empty, please check.");
		return;
	}

	//get save .ini file path
	GetDlgItem(IDC_EDINI)->GetWindowText(strFileSaveIniPath);
	if(strFileSaveIniPath.IsEmpty())
	{
		AfxMessageBox("Save .ini file path is empty, please check.");
		return;
	}

	if(CFilePartitionDlg::iOneToMore)
	{
		BYTE *b = new BYTE[iPartSizeSPEC];
		cReadFile = new CFile(strFilePath, CFile::modeRead);
		int iMAXFileNum = cReadFile->GetLength() / iPartSizeSPEC ;
		for(int i = 1; i <= iMAXFileNum; i++)
		{
			CString strTempFileName;
			ZeroMemory(b, iPartSizeSPEC);

			strTempFileName.Format("%s\\%s_%d.dat", strFileSavePath, cReadFile->GetFileName(), i );

			HANDLE hFile;
			hFile = CreateFile(TEXT(strTempFileName),    // file to open
                   GENERIC_WRITE,          // open for reading
                   0,			   // share for reading
                   0,                   // default security
                   CREATE_ALWAYS,          // 
                   FILE_ATTRIBUTE_NORMAL,  // normal file
                   NULL);                  // no attr. template
 
			if (hFile == INVALID_HANDLE_VALUE) 
			{ 
				AfxMessageBox("Could not open file.");
				return;
			}
			CloseHandle(hFile);
			cWirteFile = new CFile(strTempFileName, CFile::modeWrite);
			iReadlen = cReadFile->Read(b, iPartSizeSPEC);
			iPostlen = cReadFile->GetPosition();
			cWirteFile->Write(b, iReadlen);
			cWirteFile->Close();

			char szTempBuf[260];
			memset(szTempBuf, 0 , 260);
			sprintf_s(szTempBuf, 260, "Partition File %d...\r\n", i );
			DisRunInfo(szTempBuf);				
	

			FILE *fp = NULL;
			
			if(i==1)
			{
				if(PathFileExists(strFileSaveIniPath))
				{
					DeleteFile(strFileSaveIniPath);
				}
			}

			fopen_s( &fp, strFileSaveIniPath, "a+");
			
			memset(szTempBuf, 0 , 260);
			sprintf_s(szTempBuf, 260, "%s%s", strTempFileName.Trim(), "\n");
			fwrite(szTempBuf, sizeof(char), strlen(szTempBuf), fp);
			fclose(fp);	

			Sleep(50);
		}
		cReadFile->Close();

	}
	else if( CFilePartitionDlg::iMoreToOne )
	{
		
	}
	else if(( CFilePartitionDlg::iOneToMore == 0 ) && ( CFilePartitionDlg::iMoreToOne == 0 ))
	{
		AfxMessageBox("Radio button need choose, please check.");
	}
	
	GetDlgItem(IDC_BT_START)->EnableWindow(true);
	GetDlgItem(IDC_BTADD)->EnableWindow(true);
	GetDlgItem(IDC_BTSAVE)->EnableWindow(true);
	GetDlgItem(IDC_BTSAVEINI)->EnableWindow(true);
	GetDlgItem(IDC_EDSPEC)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_OTM)->EnableWindow(true);	
	GetDlgItem(IDC_RADIO_MTO)->EnableWindow(true);
	GetDlgItem(IDC_EDRUNINFO)->EnableWindow(true);
	
}

void CFilePartitionDlg::OnEnChangeEdspec()
{
	long iFilePartitionSize;	
	long iFileSPECSize;
	long iFilePartitionNum;

	char pFilePartitionSizeBuf[128];	
	char pFileSPECBuf[128];
	char pFilePartitionNumBuf[128];

	ZeroMemory(pFilePartitionSizeBuf, 128);
	ZeroMemory(pFileSPECBuf, 128);	
	ZeroMemory(pFilePartitionNumBuf, 128);


	if(m_FileSize.GetWindowText(pFilePartitionSizeBuf, 128) == 0)
	{
		AfxMessageBox("File Partition size error, please check.");
		return;
	}

	if(m_FileSPEC.GetWindowText(pFileSPECBuf, 128) == 0)
	{
		AfxMessageBox("File Spec size input error, please check.");
		return;
	}
	
	iFilePartitionSize = atol(pFilePartitionSizeBuf);
	iFileSPECSize = atol(pFileSPECBuf);
	Sleep(100);

	iFilePartitionNum = iFilePartitionSize / iFileSPECSize;
	sprintf_s(pFilePartitionNumBuf, 128, "%u", iFilePartitionNum);

	m_FileNum.SetWindowText(pFilePartitionNumBuf);
}

void CFilePartitionDlg::OnBnClickedRadioOtm()
{
	iOneToMore = 1;
	return;
}

void CFilePartitionDlg::OnBnClickedRadioMto()
{
	iMoreToOne = 1;
	return;
}

void CFilePartitionDlg::DisRunInfo(CString strInfo)
{
	int iLen=0;
	CString strTep = strInfo;
	strTep += "\r\n";
	iLen = m_RunInfo.GetWindowTextLength();
	m_RunInfo.SetSel(iLen, iLen);
	m_RunInfo.ReplaceSel(strTep);
	strInfo += strTep;
}
