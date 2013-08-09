#ifndef CORE_CORE_CLASSENTITY_H__
#define CORE_CORE_CLASSENTITY_H__

#include "typedef.hpp"

namespace core{

class Property:
	public Pool
{
public:
	Property(){}

	Property(const Property& prop):
		m_name(prop.m_name),m_type(prop.m_type),m_save(prop.m_save),m_public(prop.m_public),
			m_private(prop.m_private), m_atonce(prop.m_atonce),m_explain(prop.m_explain),m_master(prop.m_master),
			m_callback(-1)
	{

	}

	String m_name;    //属性名
	int            m_type;     //属性类型
	int            m_save;     //是否存盘
	int            m_public;      //是否广播
	int            m_private;        //是否下发
	int            m_atonce;  //是否随对象一起下发
	String m_explain;
	String m_master;
	int            m_callback; //变更回调索引
};

class Record:
	public Pool
{
public:
	Record(){}
	Record(const Record& r):
		m_name(r.m_name), m_private(r.m_private), m_rowMax(r.m_rowMax),m_save(r.m_save),
			m_master(r.m_master),m_explain(r.m_explain),m_key(r.m_key),m_cols(r.m_cols),
			m_columnTypes(r.m_columnTypes), m_columnNames(r.m_columnNames),m_callback(-1)
	{

	}
	String m_name; //表名
	int  m_private;//是否可见
	int  m_rowMax;//最大列数
	int  m_save;//是否保存
	String m_master;
	String m_explain;
	int m_key;
	int m_cols;
	Vector<int> m_columnTypes;//列类型
	Vector<String> m_columnNames; //列类型
	Vector<String> m_columnDescs;//注释
	int m_callback;

};

class ClassEntity:
	public Pool
{
public:
	ClassEntity();
	~ClassEntity();
	const char* getClassName();
	int getClassType();

	const char* getPropertyName(int propIndex);
	int getPropertyType(int propIndex);
	bool getPropertySave(int propIndex);
	bool getPropertyPublic(int propIndex);
	bool getPropertyPrivate(int propIndex);
	bool getPropertyAtonce(int propIndex);
	int getPropertyCount();
	int getPropertySaveCount();
	int getPropertyIndex(const String& propName);

	const char* getRecordName(int recordIndex);
	bool getRecordSave(int recordIndex);
	bool getRecordPrivate(int recordIndex);
	int   getRecordRowMax(int recordIndex);
	int   getColumnType(int recordIndex, int columnIndex);
	const char* getColumnName(int recordIndex, int columnIndex);
	int getColumnIndex(int recordIndex, const String& columnName);
	int getRecordCount();
	int getRecordSaveCount();
	const Vector<int>& getRecordColumnTypes(int recordIndex);
	int getRecordIndex(const String& recordName);

	int getPropertyCallback(int propIndex);
	void setPropertyCallback(int propIndex, int cb);
	int getRecordCallback(int recordIndex);
	void setRecordCallback(int recordIndex, int cb);


	String m_className;
	int m_classType;
	int m_parentIndex;
	String m_explain;
	Vector<int> m_child;
	
	int m_savePropCount;
	int m_saveRecordCount;
	Vector<Property*> m_props;
	Vector<Record*> m_records;
	Map<String, int> m_propIndex;
	Map<String, int> m_recordIndex;

};


inline ClassEntity::ClassEntity():
	m_savePropCount(0),
	m_saveRecordCount(0)
{

}

inline ClassEntity::~ClassEntity()
{
	Vector<Property*>::iterator propIt = m_props.begin();
	for(; propIt != m_props.end(); ++propIt)
	{
		delete (*propIt);
	}

	Vector<Record*>::iterator recIt = m_records.begin();
	for(; recIt != m_records.end(); ++recIt)
	{
		delete (*recIt);
	}
}


inline const char* ClassEntity::getClassName()
{
	return m_className.c_str();
}

inline int ClassEntity::getClassType()
{
	return m_classType;
}

inline const char* ClassEntity::getPropertyName(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_name.c_str();
	}
	return "";
}

inline int ClassEntity::getPropertyType(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_type;
	}
	return -1;
}

inline bool ClassEntity::getPropertySave(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_save == DT_TRUE;
	}
	return false;
}

inline bool ClassEntity::getPropertyPublic(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_public == DT_TRUE;
	}
	return false;
}

inline bool ClassEntity::getPropertyPrivate(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_private == DT_TRUE;
	}
	return false;
}

inline bool ClassEntity::getPropertyAtonce(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_atonce == DT_TRUE;
	}
	return false;
}

inline int ClassEntity::getPropertyCount()
{
	return (int)m_props.size();
}

inline int ClassEntity::getPropertySaveCount()
{
	return m_savePropCount;
}

inline int ClassEntity::getPropertyIndex(const String& propName)
{
	Map<String, int>::iterator it = m_propIndex.find(propName);
	if(it != m_propIndex.end())
	{
		return it->second;
	}
	return -1;
}

inline const char* ClassEntity::getRecordName(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		return m_records[recordIndex]->m_name.c_str();
	}
	return "";
}

inline bool ClassEntity::getRecordSave(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		return m_records[recordIndex]->m_save == DT_TRUE;
	}
	return false;
}

inline bool ClassEntity::getRecordPrivate(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		return m_records[recordIndex]->m_private == DT_TRUE;
	}
	return false;

}

inline int   ClassEntity::getRecordRowMax(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		return m_records[recordIndex]->m_rowMax;
	}
	return -1;

}

inline int  ClassEntity::getColumnType(int recordIndex, int columnIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		if(columnIndex >= 0 && columnIndex < m_records[recordIndex]->m_columnTypes.size())
		{
			return m_records[recordIndex]->m_columnTypes[columnIndex];
		}
	}
	return -1;
		
}

inline const char* ClassEntity::getColumnName(int recordIndex, int columnIndex)
{

	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		if(columnIndex >= 0 && columnIndex < m_records[recordIndex]->m_columnNames.size())
		{
			return m_records[recordIndex]->m_columnNames[columnIndex].c_str();
		}
	}
	return "";
}

inline int ClassEntity::getColumnIndex(int recordIndex, const String& columnName)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		Vector<String> colname = m_records[recordIndex]->m_columnNames;
		for(int i = 0; i < colname.size(); ++i)
		{
			if(colname[i] == columnName)
				return i;
		}
	}
	return -1;
}

inline int ClassEntity::getRecordCount()
{
	return (int)m_records.size();
}

inline int ClassEntity::getRecordSaveCount()
{
	return m_saveRecordCount;
}

inline const Vector<int>& ClassEntity::getRecordColumnTypes(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		return m_records[recordIndex]->m_columnTypes;
	}
	static Vector<int> ret;
	return ret;
}

inline int ClassEntity::getRecordIndex(const String& recordName)
{
	Map<String, int>::iterator it = m_recordIndex.find(recordName);
	if(it != m_recordIndex.end())
	{
		return it->second;
	}
	return -1;
}

inline int ClassEntity::getPropertyCallback(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		return m_props[propIndex]->m_callback;
	}
	return -1;
}

inline void ClassEntity::setPropertyCallback(int propIndex, int cb)
{
	if(propIndex >= 0 && propIndex < m_props.size())
	{
		m_props[propIndex]->m_callback = cb;
	}
}

inline int ClassEntity::getRecordCallback(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		return m_records[recordIndex]->m_callback;
	}
	return -1;
}

inline void ClassEntity::setRecordCallback(int recordIndex, int cb)
{
	if(recordIndex >= 0 && recordIndex < m_records.size())
	{
		m_records[recordIndex]->m_callback = cb;
	}
}

}
#endif //CORE_CORE_CLASSENTITY_H__
