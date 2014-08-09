
class FileOP:public CFile
	{
		public:
			CFileException fileException;
		public:
			ULONGLONG	bGetFileSize(char* pFileName);
			int			iOpenFile(char* pFileName );
	
		
	};