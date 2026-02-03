#pragma once

#include "./std.h"

class Parser
{
public:
	FILE *m_pStream;
	char m_pBuffer[256];
	char m_pString[256];

public:
	bool FileOpen(LPCTSTR filename);
	bool FileClose(void);

	FILE* GetFilePointer(void) { return this->m_pStream; }

	bool GetDataFromString(char* pString = 0, VOID* pData = 0, int DATA_TYPE = TYPE_NULL);
	bool GetDataFromFile(VOID* pData = 0, int DATA_TYPE = TYPE_NULL);
	bool CheckString(char* pString, char* pEndString);
	bool GetDataFromNext(char* pString = 0);
	
public:
	Parser(void);
	Parser(FILE *pFile);
	~Parser(void);
};
