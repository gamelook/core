#ifndef CORE_CORE_OBJECTENTITY_H__
#define CORE_CORE_OBJECTENTITY_H__

#include "ObjectID.hpp"
#include "ClassMaster.hpp"
#include "ClassEntity.hpp"
#include "RecordValue.hpp"
#include "OStream.hpp"
#include "IStream.hpp"

namespace core{

class ObjectEntity:
	public Pool
{
public:
	ObjectEntity(int classIndex);
	~ObjectEntity();

	int getInt(int propIndex);
	void setInt(int propIndex, int value);
	float getFloat(int propIndex);
	void setFloat(int propIndex, float value);
	const String& getStr(int propIndex);
	void setStr(int propIndex, const String& value);

	int getRecordInt(int recordIndex, int row, int column);
	void setRecordInt(int recordIndex, int row, int column, int value);
	float getRecordFloat(int recordIndex, int row, int column);
	void setRecordFloat(int recordIndex, int row, int column, float value);
	const String& getRecordStr(int recordIndex, int row, int column);
	void setRecordStr(int recordIndex, int row, int column, const String& value);

	int addRecordRow(int recordIndex);
	void deleteRecordRow(int recordIndex, int row);
	int getRecordRows(int recordIndex);
	int findRecordInt(int recordIndex, int column, int value);
	int findRecordFloat(int recordIndex, int column, float value);
	int findRecordStr(int recordIndex, int column, const String& value);


	int m_classIndex;
	int m_propCount;
	int m_recordCount;
	PropertyValue* m_props;
	RecordValue* m_records;

};


inline ObjectEntity::ObjectEntity(int classIndex):
	m_classIndex(classIndex),
	m_propCount(0),
	m_recordCount(0),
	m_props(NULL),
	m_records(NULL)
{
	m_propCount = ClassMaster::getInstance().getPropertyCount(classIndex);
	if(m_propCount > 0)
		m_props = new PropertyValue[m_propCount];

	for(int i = 0; i < m_propCount; ++i)
	{
		if(ClassMaster::getInstance().getPropertyType(m_classIndex, i) == DT_INT)
		{
			m_props[i].initInt();
		}
		else if(ClassMaster::getInstance().getPropertyType(m_classIndex, i) == DT_FLOAT)
		{
			m_props[i].initFloat();
		}
		else
		{
			m_props[i].initStr();
		}
	}
	
	m_recordCount = ClassMaster::getInstance().getRecordCount(classIndex);
	if(m_recordCount > 0)
		m_records = new RecordValue[m_recordCount];
	
	for(int j = 0; j < m_recordCount; ++j)
	{
		const Vector<int>& types = ClassMaster::getInstance().getRecordColumnTypes(m_classIndex, j);
		m_records[j].init(types);
	}
}

inline ObjectEntity::~ObjectEntity()
{
	delete [] m_props;
	delete [] m_records;
}


inline int ObjectEntity::getInt(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_propCount && m_props[propIndex].type == DT_INT)
	{
		return m_props[propIndex].data.i;
	}
	return 0;
}

inline void ObjectEntity::setInt(int propIndex, int value)
{
	if(propIndex >= 0 && propIndex < m_propCount && m_props[propIndex].type == DT_INT)
	{
		m_props[propIndex].data.i = value;
	}
}

inline float ObjectEntity::getFloat(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_propCount && m_props[propIndex].type == DT_FLOAT)
	{
		return m_props[propIndex].data.f;
	}
	return 0;
}

inline void ObjectEntity::setFloat(int propIndex, float value)
{
	if(propIndex >= 0 && propIndex < m_propCount && m_props[propIndex].type == DT_FLOAT)
	{
		m_props[propIndex].data.f = value;
	}
}

inline const String& ObjectEntity::getStr(int propIndex)
{
	if(propIndex >= 0 && propIndex < m_propCount && m_props[propIndex].type == DT_STR)
	{
		return *(m_props[propIndex].data.s);
	}
	static String s;
	return s;
}

inline void ObjectEntity::setStr(int propIndex, const String& value)
{
	if(propIndex >= 0 && propIndex < m_propCount && m_props[propIndex].type == DT_STR)
	{
		*m_props[propIndex].data.s = value;
	}
}

inline int ObjectEntity::getRecordInt(int recordIndex, int row, int column)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].getRecordInt(row, column);
	}
	return 0;
}

inline void ObjectEntity::setRecordInt(int recordIndex, int row, int column, int value)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		m_records[recordIndex].setRecordInt(row, column, value);
	}
}

inline float ObjectEntity::getRecordFloat(int recordIndex, int row, int column)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].getRecordFloat(row, column);
	}
	return 0;

}

inline void ObjectEntity::setRecordFloat(int recordIndex, int row, int column, float value)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		m_records[recordIndex].setRecordFloat(row, column, value);
	}
}

inline const String& ObjectEntity::getRecordStr(int recordIndex, int row, int column)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].getRecordStr(row, column);
	}
	static String s;
	return s;
}

inline void ObjectEntity::setRecordStr(int recordIndex, int row, int column, const String& value)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		m_records[recordIndex].setRecordStr(row, column, value);
	}
}

inline int ObjectEntity::addRecordRow(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].addRecordRow();
	}
	return -1;
}

inline void ObjectEntity::deleteRecordRow(int recordIndex, int row)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		m_records[recordIndex].deleteRecordRow(row);
	}
}

inline int ObjectEntity::getRecordRows(int recordIndex)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].m_row;
	}
	return -1;
}

inline int ObjectEntity::findRecordInt(int recordIndex, int column, int value)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].findRecordInt(column, value);
	}
	return -1;
}

inline int ObjectEntity::findRecordFloat(int recordIndex, int column, float value)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].findRecordFloat(column, value);
	}
	return -1;
}

inline int ObjectEntity::findRecordStr(int recordIndex, int column, const String& value)
{
	if(recordIndex >= 0 && recordIndex < m_recordCount)
	{
		return m_records[recordIndex].findRecordStr(column, value);
	}
	return -1;
}

}


#endif //CORE_CORE_OBJECTENTITY_H__


