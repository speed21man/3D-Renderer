#include "Parser.h"

Parser::Parser(void)
{
}

Parser::Parser(FILE *pFile)
{
	this->m_pStream = pFile; 
}

Parser::~Parser(void)
{
}

bool Parser::FileOpen(LPCTSTR filename)
{
	if((m_pStream = fopen(filename, "rt")) == NULL)
	{
		return false;
	}

	return true;
}

bool Parser::FileClose(void)
{
	fclose(m_pStream);
	return true;
}

bool Parser::GetDataFromString(char* pString, VOID* pData, int DATA_TYPE)
{
	fpos_t  FilePos; 

	//if( fgetpos( m_pStream, &FilePos ) )
	//{
	//	return false;
	//	//ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
	//}

	while(!feof(m_pStream))
	{
		fgets(this->m_pBuffer, 256, this->m_pStream);
		sscanf(this->m_pBuffer, "%s", this->m_pString);

		if( !strcmp(pString, this->m_pString) )
		{
			return GetDataFromFile(pData, DATA_TYPE);
		}
		//else
		//{
		//	if( fsetpos( m_pStream, &FilePos ) )
		//	{
		//		return false;
		//	}
		//}
	}
	return false;
}

bool Parser::GetDataFromFile(VOID* pData, int DATA_TYPE)
{
	if(pData != NULL)
	{
		switch(DATA_TYPE)
		{
		case TYPE_INT:
			sscanf( this->m_pBuffer, "%s %d", this->m_pString, pData );
			break;
		case TYPE_FLOAT:
			sscanf( this->m_pBuffer, "%s %f", this->m_pString, pData );
			break;
		case TYPE_ASEVERTEX:
			sscanf( this->m_pBuffer, "%s %f %f %f", this->m_pString, 
				&((D3DXVECTOR3*)pData)->x, &((D3DXVECTOR3*)pData)->y, &((D3DXVECTOR3*)pData)->z);
			break;
		case TYPE_VERTEX:
			sscanf( this->m_pBuffer, "%s %f %f %f", this->m_pString, 
				&((D3DXVECTOR3*)pData)->x, &((D3DXVECTOR3*)pData)->z, &((D3DXVECTOR3*)pData)->y);
			break;

		case TYPE_STRING:
			char szTexPath[256] = TEXT("");
			sscanf( this->m_pBuffer, "%s %s", this->m_pString, szTexPath );
			
			if(szTexPath[0] == '"')
			{
				strcpy( szTexPath, strstr( this->m_pBuffer, "\"") );

				size_t filelen = strlen(szTexPath);
				szTexPath[filelen - 2] = 0;
				strcpy( (char*)pData, &szTexPath[1] );
			}
			else
			{
				strcpy( (char*)pData, &szTexPath[0] );
			}
			break;
		}
	}
	return true;
}

bool Parser::CheckString(char* pString, char* pEndString)
{
	fpos_t  FilePos; 

	if( fgetpos( m_pStream, &FilePos ) )
	{
		return false;
		//ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
	}

	while(!feof(m_pStream))
	{
		//fgets(this->m_pBuffer, 256, this->m_pStream);
		fscanf(m_pStream, "%s", this->m_pString);

		if( !strcmp(pString, this->m_pString) )
		{
			if( fsetpos( m_pStream, &FilePos ) )
			{
				return false;
			}

			return true;
		}
		else if(!strcmp(pEndString, this->m_pString))
		{
			if( fsetpos( m_pStream, &FilePos ) )
			{
				return false;
			}

			return false;
		}
	}

	return false;
}

bool Parser::GetDataFromNext(char* pString)
{
	fpos_t  FilePos; 
	bool bStirng = false;

	if( fgetpos( m_pStream, &FilePos ) )
	{
		return false;
		//ErrorCloseStream( "작업도중 파일포인터를 잃어 버렸습니다.");
	}

	fgets(this->m_pBuffer, 256, this->m_pStream);
	sscanf(this->m_pBuffer, "%s", this->m_pString);

	if( !strcmp(pString, this->m_pString) )
	{
		bStirng = true;
	}

	if( fsetpos( m_pStream, &FilePos ) )
	{
		return false;
	}

	return bStirng;
}