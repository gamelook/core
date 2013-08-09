#ifndef CORE_CORE_FILEDB_H__
#define CORE_CORE_FILEDB_H__


extern "C" {
#include "sqlite3.h"
}

#include "typedef.hpp"

//typedef long long i64;
//typedef i64 ID;

struct sqlite3;
struct sqlite3_stmt;

namespace core{

class FileDB
{
public:

	FileDB();
	~FileDB();

	bool open(const char * filename);
	bool load(const char * filename);
	void close();

	bool GetData(const char* pszTable, ID id, const char* pszField, int64_t& value);
	bool SetData(const char* pszTable, ID id, const char* pszField, int64_t value);

	bool GetStr(const char* pszTable, ID id, const char* pszField, String& value);
	bool SetStr(const char* pszTable, ID id, const char* pszField, const char* value);

	bool GetIDSet(const char *pszTable, const char* cond, Vector<ID> & idset);

	bool GetData(const char* pszTable, const char* id, const char* pszField, int64_t& value);
	bool SetData(const char* pszTable, const char* id, const char* pszField, int64_t value);

	bool GetStr(const char* pszTable, const char* id, const char* pszField, String& value);
	bool SetStr(const char* pszTable, const char* id, const char* pszField, const char* value);

	bool GetIDSet(const char *pszTable, const char* cond, Vector<String> & idset);

	bool exec(const char* pszSql);

	bool insertRow(const char* pszTable, ID id);
	bool deleteRow(const char* pszTable, ID id);

private:

	typedef Map<String, sqlite3_stmt*> FIELD_MAP;
	typedef Map<String, FIELD_MAP> TABLE_MAP;

	sqlite3* m_sqlite;
	TABLE_MAP m_writeStmts;
	TABLE_MAP m_readStmts;


};

}

#endif //CORE_CORE_FILEDB_H__

