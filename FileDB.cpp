#include "FileDB.hpp"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

namespace core {

FileDB::FileDB():
	m_sqlite(NULL)
{

}

FileDB::~FileDB()
{

}

bool FileDB::open(const char * filename)
{
	sqlite3* db = NULL;
	if(sqlite3_open(filename, &m_sqlite) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	return true;
}

bool FileDB::load(const char * filename)
{
	sqlite3* db = NULL;
	if(sqlite3_open(filename, &db) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(db),__FILE__, __LINE__);
		return false;
	}

	if(sqlite3_open(":memory:", &m_sqlite) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	sqlite3_backup * backup = sqlite3_backup_init(m_sqlite,"main",db, "main");
	if(backup == NULL)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	if(sqlite3_backup_step(backup, -1) != SQLITE_DONE)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	if(sqlite3_backup_finish(backup) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	sqlite3_close(db);

	return true;
}

void FileDB::close()
{
	{
		TABLE_MAP::iterator it = m_writeStmts.begin();
		TABLE_MAP::iterator end = m_writeStmts.end();
		for(; it != end; ++it)
		{
			FIELD_MAP::iterator stmtIt = it->second.begin();
			FIELD_MAP::iterator stmtEnd = it->second.end();
			for(; stmtIt != stmtEnd; ++stmtIt)
			{
				if(stmtIt->second != NULL)
				{
					sqlite3_finalize(stmtIt->second);
				}
			}
		}
	}


	{
		TABLE_MAP::iterator it = m_readStmts.begin();
		TABLE_MAP::iterator end = m_readStmts.end();
		for(; it != end; ++it)
		{
			FIELD_MAP::iterator stmtIt = it->second.begin();
			FIELD_MAP::iterator stmtEnd = it->second.end();
			for(; stmtIt != stmtEnd; ++stmtIt)
			{
				if(stmtIt->second != NULL)
				{
					sqlite3_finalize(stmtIt->second);
				}
			}
		}
	}

	sqlite3_close(m_sqlite);
}

bool FileDB::GetData(const char* pszTable, ID id, const char* pszField, int64_t& value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_readStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "select %s from %s where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszField, pszTable);
#else
		snprintf(buff, 512, sql, pszField, pszTable);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL) ;
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_readStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_int64(stmt, 1, id);
	if( ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	value = sqlite3_column_int64(stmt, 0);

	if(sqlite3_errcode(m_sqlite) == SQLITE_NOMEM)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
	}

	sqlite3_reset(stmt);

	return true;
}

bool FileDB::SetData(const char* pszTable, ID id, const char* pszField, int64_t value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_writeStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "update %s set %s = ?  where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszTable, pszField);
#else
		snprintf(buff, 512, sql, pszTable, pszField);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_writeStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_int64(stmt, 1, value) ;
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_bind_int64(stmt, 2, id);
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	sqlite3_reset(stmt);

	return true;
}

bool FileDB::GetStr(const char* pszTable, ID id, const char* pszField, String& value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_readStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "select %s from %s where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszField, pszTable);
#else
		snprintf(buff, 512, sql, pszField, pszTable);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_readStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_int64(stmt, 1, id);
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	char * v  = (char *)sqlite3_column_text(stmt, 0);

	if(v == NULL && sqlite3_errcode(m_sqlite) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}
	
	value = v;
	sqlite3_reset(stmt);
	return true;
}

bool FileDB::SetStr(const char* pszTable, ID id, const char* pszField, const char* value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_writeStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "update %s set %s = ?  where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszTable, pszField);
#else
		snprintf(buff, 512, sql, pszTable, pszField);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_writeStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_text(stmt, 1, value, strlen(value), SQLITE_STATIC);
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_bind_int64(stmt, 2, id);

	ret = sqlite3_step(stmt);

	sqlite3_reset(stmt);

	return true;
}

bool FileDB::GetIDSet(const char *pszTable, const char* cond, Vector<ID>& idset)
{
	char * sql = "select id from %s where %s";
	char buff[512];
	if(strlen(cond)==0)
#ifdef WIN32
		sprintf_s(buff, "select id from %s", pszTable);
#else
		snprintf(buff, 512, "select id from %s", pszTable);
#endif
	else
#ifdef WIN32
		sprintf_s(buff, sql, pszTable, cond);
#else
		snprintf(buff, 512, sql, pszTable, cond);
#endif
	char ** pResult = NULL;
	int row;
	int column;
	if(sqlite3_get_table(m_sqlite,  buff, &pResult, &row, &column, NULL) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	for(int i = 1; i <= row; ++i)
	{
		idset.push_back(atol(pResult[i]));
	}

	sqlite3_free_table(pResult);
	return true;
}

bool FileDB::GetData(const char* pszTable, const char* id, const char* pszField, int64_t& value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_readStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "select %s from %s where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszField, pszTable);
#else
		snprintf(buff, 512, sql, pszField, pszTable);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL) ;
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_readStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_text(stmt, 1, id, strlen(id), SQLITE_STATIC);
	if( ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	value = sqlite3_column_int64(stmt, 0);

	if(sqlite3_errcode(m_sqlite) == SQLITE_NOMEM)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
	}

	sqlite3_reset(stmt);

	return true;
}

bool FileDB::SetData(const char* pszTable, const char* id, const char* pszField, int64_t value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_writeStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "update %s set %s = ?  where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszTable, pszField);
#else
		snprintf(buff, 512, sql, pszTable, pszField);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_writeStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_int64(stmt, 1, value) ;
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_bind_text(stmt, 2, id, strlen(id), SQLITE_STATIC);
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	sqlite3_reset(stmt);

	return true;
}

bool FileDB::GetStr(const char* pszTable, const char* id, const char* pszField, String& value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_readStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "select %s from %s where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszField, pszTable);
#else
		snprintf(buff, 512, sql, pszField, pszTable);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_readStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_text(stmt, 1, id, strlen(id), SQLITE_STATIC);
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	char * v  = (char *)sqlite3_column_text(stmt, 0);

	if(v == NULL && sqlite3_errcode(m_sqlite) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	value = v;
	sqlite3_reset(stmt);
	return true;
}

bool FileDB::SetStr(const char* pszTable, const char* id, const char* pszField, const char* value)
{
	int ret = 0;
	sqlite3_stmt * stmt = m_writeStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "update %s set %s = ?  where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszTable, pszField);
#else
		snprintf(buff, 512, sql, pszTable, pszField);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_writeStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_text(stmt, 1, value, strlen(value), SQLITE_STATIC);
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_bind_text(stmt, 2, id, strlen(id), SQLITE_STATIC);

	ret = sqlite3_step(stmt);

	sqlite3_reset(stmt);

	return true;
}

bool FileDB::GetIDSet(const char *pszTable, const char* cond, Vector<String>& idset)
{
	char * sql = "select id from %s where %s";
	char buff[512];
	if(strlen(cond)==0)
#ifdef WIN32
		sprintf_s(buff, "select id from %s", pszTable);
#else
		snprintf(buff, 512, "select id from %s", pszTable);
#endif
	else
#ifdef WIN32
		sprintf_s(buff, sql, pszTable, cond);
#else
		snprintf(buff, 512, sql, pszTable, cond);
#endif
	char ** pResult = NULL;
	int row;
	int column;
	if(sqlite3_get_table(m_sqlite,  buff, &pResult, &row, &column, NULL) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	for(int i = 1; i <= row; ++i)
	{
		idset.push_back(String(pResult[i]));
	}

	sqlite3_free_table(pResult);
	return true;
}




bool FileDB::exec(const char* pszSql)
{
	if(sqlite3_exec(m_sqlite, pszSql,NULL,NULL,NULL) != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}
	return true;
}

bool FileDB::insertRow(const char* pszTable, ID id)
{
	int ret = 0;
	char * pszField = "insert";
	sqlite3_stmt * stmt = m_writeStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "insert into %s(id) values(?)";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszTable);
#else
		snprintf(buff, 512, sql, pszTable);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_writeStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_int64(stmt, 1, id) ;
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	sqlite3_reset(stmt);

	return true;

}

bool FileDB::deleteRow(const char* pszTable, ID id)
{
	int ret = 0;
	char * pszField = "delete";
	sqlite3_stmt * stmt = m_writeStmts[pszTable][pszField];
	if(stmt == NULL)
	{
		char* sql = "delete from %s where id = ?";
		char buff[512];
#ifdef WIN32
		sprintf_s(buff, sql, pszTable);
#else
		snprintf(buff, 512, sql, pszTable);
#endif
		ret = sqlite3_prepare_v2(m_sqlite, buff, -1, &stmt, NULL);
		if(ret != SQLITE_OK || stmt == NULL)
		{
			printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
			return false;
		}
		m_writeStmts[pszTable][pszField] = stmt;
	}

	ret = sqlite3_bind_int64(stmt, 1, id) ;
	if(ret != SQLITE_OK)
	{
		printf("sqlite error:%s,%s,%d",sqlite3_errmsg(m_sqlite),__FILE__, __LINE__);
		return false;
	}

	ret = sqlite3_step(stmt);

	sqlite3_reset(stmt);

	return true;
}

}

