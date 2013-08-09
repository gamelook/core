#include "ObjectEntity.hpp"
#include "ObjectMaster.hpp"

namespace core{

ObjectMaster::ObjectMaster(int ownerID, int type, int size):
	m_ownerID(ownerID),
	m_type(type),
	m_size(size),
	m_count(0)
{
	m_objects = new ObjectEntity*[m_size];
	for(int i = 0; i < m_size; ++i)
	{
		m_objects[i]  = NULL;
	}
}

ObjectMaster::~ObjectMaster()
{
	for(int i = 0; i < m_size; ++i)
	{
		if(m_objects[i] != NULL)
		{
			delete m_objects[i];
		}
	}
}

int ObjectMaster::getClassIndex(const ObjectID& objID)
{
	if(objID.index >= 0 && objID.index < m_size && m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->m_classIndex;
	}
	return -1;
}

ObjectID ObjectMaster::addObject(int classIndex)
{
	for(int i = 0; i < m_size; ++i)
	{
		if(m_objects[i] == NULL)
		{
			++m_count;
			m_objects[i] = new ObjectEntity(classIndex);
			return ObjectID(m_type, m_ownerID, i);
		}
	}
	return ObjectID();
}

ObjectID ObjectMaster::addObject(int index, int classIndex)
{
	if(index >= 0 && index < m_size && m_objects[index] == NULL)
	{
		++m_count;
		m_objects[index] = new ObjectEntity(classIndex);
		return ObjectID(m_type, m_ownerID, index);
	}
	return ObjectID();
}

void ObjectMaster::removeObject(const ObjectID& objID)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		--m_count;
		delete m_objects[objID.index];
		m_objects[objID.index] = NULL;
	}
}

int ObjectMaster::getInt(const ObjectID& objID, int propIndex)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getInt(propIndex);
	}
	return 0;
}

void ObjectMaster::setInt(const ObjectID& objID, int propIndex, int value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->setInt(propIndex, value);
	}
}

float ObjectMaster::getFloat(const ObjectID& objID, int propIndex)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getFloat(propIndex);
	}
	return 0;
}

void ObjectMaster::setFloat(const ObjectID& objID, int propIndex, float value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->setFloat(propIndex, value);
	}
}

const String& ObjectMaster::getStr(const ObjectID& objID, int propIndex)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getStr(propIndex);
	}
	static String e;
	return e;
}

void ObjectMaster::setStr(const ObjectID& objID, int propIndex, const String& value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->setStr(propIndex, value);
	}
}

int ObjectMaster::getRecordInt(const ObjectID& objID, int recordIndex, int row, int column)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getRecordInt(recordIndex,  row, column);
	}
	return 0;
}

void ObjectMaster::setRecordInt(const ObjectID& objID, int recordIndex, int row, int column, int value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->setRecordInt(recordIndex,row, column,value);
	}

}

float ObjectMaster::getRecordFloat(const ObjectID& objID, int recordIndex, int row, int column)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getRecordFloat(recordIndex, row, column);
	}
	return 0;
}

void ObjectMaster::setRecordFloat(const ObjectID& objID, int recordIndex, int row, int column, float value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->setRecordFloat(recordIndex, row, column, value);
	}
}

const String& ObjectMaster::getRecordStr(const ObjectID& objID, int recordIndex, int row, int column)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getRecordStr(recordIndex, row, column);
	}
	static String e;
	return e;
}

void ObjectMaster::setRecordStr(const ObjectID& objID, int recordIndex, int row, int column, const String& value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->setRecordStr(recordIndex, row, column, value);
	}
}

int ObjectMaster::addRecordRow(const ObjectID& objID, int recordIndex)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->addRecordRow(recordIndex);
	}
	return -1;
}

void ObjectMaster::deleteRecordRow(const ObjectID& objID, int recordIndex, int row)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		m_objects[objID.index]->deleteRecordRow(recordIndex, row);
	}
}

int ObjectMaster::getRecordRows(const ObjectID& objID, int recordIndex)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->getRecordRows(recordIndex);
	}
	return -1;
}

int ObjectMaster::findRecordInt(ObjectID& objID, int recordIndex, int column, int value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->findRecordInt(recordIndex, column, value);
	}
	return -1;
}

int ObjectMaster::findRecordFloat(ObjectID& objID, int recordIndex, int column, float value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->findRecordFloat(recordIndex, column, value);
	}
	return -1;
}

int ObjectMaster::findRecordStr(ObjectID& objID, int recordIndex, int column, const String& value)
{
	if(m_ownerID == objID.ownerID &&
		m_type == objID.type && 
		objID.index >= 0 && 
		objID.index < m_size && 
		m_objects[objID.index] != NULL)
	{
		return m_objects[objID.index]->findRecordStr(recordIndex, column, value);
	}
	return -1;
}


bool ObjectMaster::toSaveStream(const ObjectID& objID, OStream& os)
{
	if(objID.index < 0 || objID.index >= m_size || m_objects[objID.index] == NULL)
		return false;

	ObjectEntity * entity = m_objects[objID.index];

	os << objID.type;
	os << objID.ownerID;
	os << objID.index;

	int classIndex = entity->m_classIndex;
	String classname = ClassMaster::getInstance().getClassName(classIndex);
	os << classname;

	int propcount = ClassMaster::getInstance().getPropertyCount(classIndex);
	int savepropcount = ClassMaster::getInstance().getPropertySaveCount(classIndex);
	os << savepropcount;
	for(int j = 0; j < propcount; ++j)
	{
		if(!ClassMaster::getInstance().getPropertySave(classIndex, j))
			continue;


		String propname = ClassMaster::getInstance().getPropertyName(classIndex, j);
		int proptype = ClassMaster::getInstance().getPropertyType(classIndex, j);
		os << propname;
		os << proptype;
		switch(proptype)
		{
		case DT_INT:
			os << entity->getInt(j);
			break;
		case DT_FLOAT:
			os << entity->getFloat(j);
			break;
		default://DT_STR
			os << entity->getStr(j);

		}
	}

	int recordcount = ClassMaster::getInstance().getRecordCount(classIndex);
	int saverecordcount = ClassMaster::getInstance().getRecordSaveCount(classIndex);
	os << saverecordcount;
	for(int k = 0; k < recordcount; ++k)
	{
		if(!ClassMaster::getInstance().getRecordSave(classIndex, k))
			continue;

		String recordname = ClassMaster::getInstance().getRecordName(classIndex, k);
		Vector<int> columnTypes = ClassMaster::getInstance().getRecordColumnTypes(classIndex, k);
		int row = entity->getRecordRows(k);

		os << recordname;
		os << row;
		os << (int)columnTypes.size();
		for(int m = 0; m < columnTypes.size(); ++m)
		{
			String columnname = ClassMaster::getInstance().getColumnName(classIndex, k, m);
			os << columnname;
			os << columnTypes[m];
			for(int r = 0; r < row; ++r)
			{
				switch(columnTypes[m])
				{
				case DT_INT:
					os << entity->getRecordInt(k,r,m);
					break;
				case DT_FLOAT:
					os << entity->getRecordFloat(k,r,m);
					break;
				default://DT_STR
					os << entity->getRecordStr(k,r,m);
				}
			}
		}
	}

	return true;
}

static void skipColumn(IStream& is, int row)
{
	int columntype;
	is >> columntype;
	int iV;
	float fV;
	String sV;
	for(int r = 0; r < row; ++r)
	{
		switch(columntype)
		{
		case DT_INT:
			is >> iV;
			break;
		case DT_FLOAT:
			is >> fV;
			break;
		default:
			is >> sV;
		}
	}
}

static void skipRecord(IStream& is)
{
	int row, column;
	is >> row;
	is >> column;
	for(int i = 0; i < column; ++i)
	{
		String columnname;
		is >> columnname;
		skipColumn(is, row);
	}
}

static void skipClass(IStream& is)
{
	int propcount;
	is >> propcount;

	for(int j = 0; j < propcount; ++j)
	{
		String propname;
		int proptype;
		int iV;
		float fV;
		String sV;
		is >> propname;
		is >> proptype;
		switch(proptype)
		{
		case DT_INT:
			is >> iV;
			break;
		case DT_FLOAT:
			is >> fV;
			break;
		default:
			is >> sV;
		}
	}

	int recordcount;
	is >>recordcount;
	for(int j = 0; j < recordcount; ++j)
	{
		String recordname;
		is >>recordname;
		skipRecord(is);
	}
}

bool ObjectMaster::fromSaveStream(ObjectID& objID, IStream& is)
{
	is >> objID.type;
	is >> objID.ownerID;
	is >> objID.index;
	String classname;
	is >> classname;
	int classIndex = ClassMaster::getInstance().getClassIndex(classname);
	if(classIndex == -1)
	{
		skipClass(is);
	}

	addObject(objID.index, classIndex);

	int propcount;
	is >> propcount;

	for(int j = 0; j < propcount; ++j)
	{
		String propname;
		int proptype;
		int iV;
		float fV;
		String sV;
		is >> propname;
		is >> proptype;
		switch(proptype)
		{
		case DT_INT:
			is >> iV;
			break;
		case DT_FLOAT:
			is >> fV;
			break;
		default:
			is >> sV;
		}

		int propIndex = ClassMaster::getInstance().getPropertyIndex(classIndex, propname);
		if(propIndex == -1)
			continue;

		switch(proptype)
		{
		case DT_INT:
			setInt(objID, j, iV);
			break;
		case DT_FLOAT:
			setFloat(objID, j, fV);
			break;
		default:
			setStr(objID, j, sV);
		}
	}

	int recordcount;
	is >> recordcount;
	for(int k = 0; k < recordcount; ++k)
	{
		String recordname;
		int row,column;

		is >> recordname;
		int recordIndex = ClassMaster::getInstance().getRecordIndex(classIndex, recordname);
		if(recordIndex == -1)
		{
			skipRecord(is);
			continue;
		}

		is >> row;
		is >> column;


		for(int m = 0; m < column; ++m)
		{
			String columnname;
			int columnIndex;
			is >> columnname;
			columnIndex = ClassMaster::getInstance().getColumnIndex(classIndex, k, columnname);
			if(columnIndex == -1)
			{
				skipColumn(is,row);
				continue;
			}
			int columntype;
			is >> columntype;
			int iV;
			float fV;
			String sV;
			for(int r = 0; r < row; ++r)
			{
				if(getRecordRows(objID, recordIndex) < r+1)
					addRecordRow(objID, recordIndex);

				switch(columntype)
				{
				case DT_INT:
					is >> iV;
					setRecordInt(objID, recordIndex, r, m,iV);
					break;
				case DT_FLOAT:
					is >> fV;
					setRecordFloat(objID, recordIndex, r, m, fV);
					break;
				default:
					is >> sV;
					setRecordStr(objID, recordIndex, r, m, sV);
				}
			}

		}


	}
	return true;
}


bool ObjectMaster::toSaveStream(OStream& os)
{
	os << m_count;
	for(int i = 0; i < m_size; ++i)
	{
		if(m_objects[i] != NULL)
		{
			ObjectID objID(m_type, m_ownerID, i);
			toSaveStream(objID, os);
		}
	}
	return true;
}



bool ObjectMaster::fromSaveStream(IStream& is)
{
	int count;
	is >> count;

	for(int i = 0; i < count; ++i)
	{
		ObjectID objID;
		fromSaveStream(objID, is);
	}
	return true;
}

}

