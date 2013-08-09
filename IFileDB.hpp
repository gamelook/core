#ifndef CORE_CORE_IFILEDB_H__
#define CORE_CORE_IFILEDB_H__

#include <string>

namespace core{

class IFileDB
{
public:
	IFileDB(){}
	virtual ~IFileDB(){}

	virtual int GetData(const char* pszTable, ID id, const char* pszField) = 0;
	virtual String GetStr(const char* pszTable, ID id, const char* pszField) = 0;
	virtual int GetData(const char* pszTable, const char* id, const char* pszField) = 0;
	virtual String GetStr(const char* pszTable, const char* id, const char* pszField) = 0;
};

}
#endif //CORE_CORE_IFILEDB_H__



