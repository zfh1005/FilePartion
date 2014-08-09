#include "stdafx.h"
#include "FileOP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONGLONG FileOP::bGetFileSize(char * pFileName)
	{
		ULONGLONG iReturnValue = 0;
		HANDLE hFile = CreateFile(
			pFileName , 
			GENERIC_READ, 
			FILE_SHARE_READ,
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
		if(INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(_T("File not exit,please check!"));
		}
		else
		{
			CFile cMyFile(hFile);
			iReturnValue = cMyFile.GetLength();
			cMyFile.Close();
		}		
		return iReturnValue;
	}