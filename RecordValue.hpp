#ifndef CORE_CORE_RECORDVALUE_H__
#define CORE_CORE_RECORDVALUE_H__


#include "ClassMaster.hpp"
#include "IStream.hpp"
#include "OStream.hpp"
#include "typedef.hpp"

namespace core{

class PropertyValue:
	public Pool
{
public:
	PropertyValue():
		type(0)
	{

	}
	~PropertyValue()
	{
		if(type == DT_STR)
		{
			delete data.s;
		}
	}
	void initInt()
	{
		type = DT_INT;
		data.i = 0;
	}

	void initFloat()
	{
		type = DT_FLOAT;
		data.f = 0;
	}
	void initStr()
	{
		type = DT_STR;
		data.s = new String();
	}

	int type;
	union DATA
	{
		int i;
		float f;
		String * s;
	} data;
};

class Column:
	public Pool
{
public:
	Column();
	~Column();
	void initInt();
	void initFloat();
	void initStr();

	int getRecordInt(int row);
	void setRecordInt(int row, int value);
	float getRecordFloat(int row);
	void setRecordFloat(int row, float value);
	const String& getRecordStr(int row);
	void setRecordStr(int row, const String& value);

	void addRecordRow();
	void deleteRecordRow(int row);
	int findRecordInt(int value);
	int findRecordFloat(float value);
	int findRecordStr(const String& value);

private:
	int type;
	union DATA
	{
		Vector<int> * i;
		Vector<float> * f;
		Vector<String> * s;
	};

	DATA m_columns;


};

inline Column::Column():
	type(0)
{

}

inline Column::~Column()
{
	if(type == DT_INT)
	{
		delete m_columns.i;
	}
	else if(type == DT_FLOAT)
	{
		delete m_columns.f;
	}
	else if(type == DT_STR)
	{
		delete m_columns.s;
	}
}

inline void Column::initInt()
{
	type = DT_INT;
	m_columns.i = new Vector<int>();
}

inline void Column::initFloat()
{
	type = DT_FLOAT;
	m_columns.f = new Vector<float>();
}

inline void Column::initStr()
{
	type = DT_STR;
	m_columns.s = new Vector<String>();
}

inline int Column::getRecordInt(int row)
{
	if(type == DT_INT)
	{
		return (*m_columns.i)[row];
	}
	return 0;
}

inline void Column::setRecordInt(int row, int value)
{
	if(type == DT_INT)
	{
		(*(m_columns.i))[row] = value;
	}
}

inline float Column::getRecordFloat(int row)
{
	if(type == DT_FLOAT)
	{
		return (*m_columns.f)[row];
	}
	return 0;
}

inline void Column::setRecordFloat(int row, float value)
{
	if(type == DT_FLOAT)
	{
		(*m_columns.f)[row] = value;
	}

}

inline const String& Column::getRecordStr(int row)
{
	if(type == DT_STR)
	{
		return (*m_columns.s)[row];
	}
	static String s;
	return s;
}

inline void Column::setRecordStr(int row, const String& value)
{
	if(type == DT_STR)
	{
		(*m_columns.s)[row] = value;
	}
}

inline void Column::addRecordRow()
{
	if(type == DT_INT)
	{
		m_columns.i->push_back(0);
	}
	else if(type == DT_FLOAT)
	{
		m_columns.f->push_back(0);
	}
	else if(type == DT_STR)
	{
		m_columns.s->push_back("");
	}

}

inline void Column::deleteRecordRow(int row)
{
	if(type == DT_INT)
	{
		m_columns.i->erase(m_columns.i->begin()+row);
	}
	else if(type == DT_FLOAT)
	{
		m_columns.f->erase(m_columns.f->begin()+row);
	}
	else if(type == DT_STR)
	{
		m_columns.s->erase(m_columns.s->begin()+row);
	}
}

inline int Column::findRecordInt(int value)
{
	if(type = DT_INT)
	{
		const Vector<int>& is = *m_columns.i;
		for(int i = 0; i < is.size(); ++i)
		{
			if(is[i] == value)
				return i;
		}
	}
	return -1;
}

inline int Column::findRecordFloat(float value)
{
	if(type == DT_FLOAT)
	{
		const Vector<float>& fs = *m_columns.f;
		for(int i = 0; i < fs.size(); ++i)
		{
			if(fs[i] == value)
				return i;
		}
	}

	return -1;
}

inline int Column::findRecordStr(const String& value)
{
	if(type == DT_STR)
	{
		const Vector<String>& ss = *m_columns.s;
		for(int i = 0; i < ss.size(); ++i)
		{
			if(ss[i] == value)
				return i;
		}
	}
	return -1;
}


///////////////////////////////////////////////////////////////

class RecordValue:
	public Pool
{
public:
	RecordValue();
	~RecordValue();
	void init(Vector<int> coltypes);
	int getRecordInt(int row, int column);
	void setRecordInt(int row, int column, int value);
	float getRecordFloat(int row, int column);
	void setRecordFloat(int row, int column, float value);
	const String& getRecordStr(int row, int column);
	void setRecordStr(int row, int column, const String& value);

	int addRecordRow();
	void deleteRecordRow(int row);
	int findRecordInt(int column, int value);
	int findRecordFloat(int column, float value);
	int findRecordStr(int column, const String& value);

	bool toStream(OStream& os);
	bool fromStream(IStream& is);

	Column* m_columns;
	int m_colsize;
	int m_row;

};


inline RecordValue::RecordValue():
	m_columns(NULL),m_colsize(0),m_row(0)
{

}
inline RecordValue::~RecordValue()
{
	if(m_columns != NULL)
		delete [] m_columns;
}

inline void RecordValue::init(Vector<int> coltypes)
{
	m_colsize = coltypes.size();
	m_columns = new Column[coltypes.size()];
	for(int i = 0; i < coltypes.size(); ++i)
	{
		if(coltypes[i] == DT_INT)
		{
			m_columns[i].initInt();
		}
		else if(coltypes[i] == DT_FLOAT)
		{
			m_columns[i].initFloat();
		}
		else
		{
			m_columns[i].initStr();
		}
	}
}
inline int RecordValue::getRecordInt(int row, int column)
{
	if(column >= 0 && column < m_colsize)
	{
		return m_columns[column].getRecordInt(row);
	}
	return 0;
}

inline void RecordValue::setRecordInt(int row, int column, int value)
{
	if(column >= 0 && column < m_colsize)
	{
		m_columns[column].setRecordInt(row, value);
	}
}

inline float RecordValue::getRecordFloat(int row, int column)
{
	if(column >= 0 && column < m_colsize)
	{
		return m_columns[column].getRecordFloat(row);
	}
	return 0;

}

inline void RecordValue::setRecordFloat(int row, int column, float value)
{
	if(column >= 0 && column < m_colsize)
	{
		m_columns[column].setRecordFloat(row, value);
	}

}

inline const String& RecordValue::getRecordStr(int row, int column)
{
	if(column >= 0 && column < m_colsize)
	{
		return m_columns[column].getRecordStr(row);
	}
	static String s;
	return s;
}

inline void RecordValue::setRecordStr(int row, int column, const String& value)
{
	if(column >= 0 && column < m_colsize)
	{
		m_columns[column].setRecordStr(row, value);
	}
}

inline int RecordValue::addRecordRow()
{
	for(int i = 0; i < m_colsize; ++i)
	{
		m_columns[i].addRecordRow();
	}

	return m_row++;

}

inline void RecordValue::deleteRecordRow(int row)
{
	for(int i = 0; i < m_colsize; ++i)
	{
		m_columns[i].deleteRecordRow(row);
	}
	--m_row;
}

inline int RecordValue::findRecordInt(int column, int value)
{
	if(column >= 0 && column < m_colsize)
	{
		return m_columns[column].findRecordInt(value);
	}
	return -1;
}

inline int RecordValue::findRecordFloat(int column, float value)
{
	if(column >= 0 && column < m_colsize)
	{
		return m_columns[column].findRecordFloat(value);
	}
	return -1;
}

inline int RecordValue::findRecordStr(int column, const String& value)
{
	if(column >= 0 && column < m_colsize)
	{
		return m_columns[column].findRecordStr(value);
	}
	return -1;
}
}
#endif //CORE_CORE_RECORDVALUE_H__

