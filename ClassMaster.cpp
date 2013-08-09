#include "ClassMaster.hpp"
#include "ClassEntity.hpp"
#include "stdio.h"

namespace core{

ClassMaster::ClassMaster()
{

}

ClassMaster::~ClassMaster()
{
	Vector<ClassEntity*>::iterator it = m_classes.begin();
	Vector<ClassEntity*>::iterator end = m_classes.end();

	for(; it != end; ++it)
	{
		delete (*it);
	}
}

ClassMaster& ClassMaster::getInstance()
{
	static ClassMaster ins;
	return ins;
}





const char * ClassMaster::getClassName(int classIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getClassName();
	}
	return "";
}

int ClassMaster::getClassType(int classIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getClassType();
	}
	return -1;
}

int ClassMaster::getClassIndex(const String& className)
{
	Map<String, int>::iterator iter = m_classIndex.find(className);
	if(iter != m_classIndex.end())
	{
		return iter->second;
	}
	return -1;
}

const char* ClassMaster::getPropertyName(int classIndex, int propIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyName(propIndex);
	}
	return "";
}

int ClassMaster::getPropertyType(int classIndex, int propIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyType(propIndex);
	}
	return -1;
}

bool ClassMaster::getPropertySave(int classIndex, int propIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertySave(propIndex);
	}
	return false;
}

bool ClassMaster::getPropertyPublic(int classIndex, int propIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyPublic(propIndex);
	}
	return false;
}

bool ClassMaster::getPropertyPrivate(int classIndex, int propIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyPrivate(propIndex);
	}
	return false;
}

bool ClassMaster::getPropertyAtonce(int classIndex, int propIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyAtonce(propIndex);
	}
	return false;
}

int ClassMaster::getPropertyCount(int classIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyCount();
	}
	return -1;
}

int ClassMaster::getPropertySaveCount(int classIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertySaveCount();
	}
	return -1;
}

int ClassMaster::getPropertyIndex(int classIndex, const String& propname)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyIndex(propname);
	}
	return -1;
}

const char* ClassMaster::getRecordName(int classIndex, int recordIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordName(recordIndex);
	}
	return "";
}

bool ClassMaster::getRecordSave(int classIndex, int recordIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordSave(recordIndex);
	}
	return false;
}

bool ClassMaster::getRecordPrivate(int classIndex, int recordIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordPrivate(recordIndex);
	}
	return false;
}

int ClassMaster::getRecordRowMax(int classIndex, int recordIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordRowMax(recordIndex);
	}
	return false;
}



int ClassMaster::getColumnType(int classIndex, int recordIndex, int columnIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getColumnType(recordIndex, columnIndex);
	}
	return -1;
}

const char* ClassMaster::getColumnName(int classIndex, int recordIndex, int columnIndex)
{

	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getColumnName(recordIndex, columnIndex);
	}
	return "";
}

int ClassMaster::getColumnIndex(int classIndex, int recordIndex, const String& columnName)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getColumnIndex(recordIndex, columnName);
	}
	return -1;
}

int ClassMaster::getRecordCount(int classIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordCount();
	}
	return -1;
}

int ClassMaster::getRecordSaveCount(int classIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordSaveCount();
	}
	return 0;
}

const Vector<int>& ClassMaster::getRecordColumnTypes(int classIndex, int recordIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordColumnTypes(recordIndex);
	}

	static Vector<int> ret;
	return ret;
}

int ClassMaster::getRecordIndex(int classIndex, const String& recordname)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordIndex(recordname);
	}
	return -1;
}

int ClassMaster::getPropertyCallback(int classIndex, int propIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getPropertyCallback(propIndex);
	}
	return -1;
}

void ClassMaster::setPropertyCallback(int classIndex, int propIndex, int cb)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		m_classes[classIndex]->setPropertyCallback(propIndex, cb);
	}

}

int ClassMaster::getRecordCallback(int classIndex, int recordIndex)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		return m_classes[classIndex]->getRecordCallback(recordIndex);
	}
	return -1;
}

void ClassMaster::setRecordCallback(int classIndex, int recordIndex, int cb)
{
	if(classIndex >= 0 && classIndex < m_classes.size())
	{
		m_classes[classIndex]->setRecordCallback(recordIndex, cb);
	}
}

void ClassMaster::initClassMaster(const Vector<ClassEntity*> & classes)
{
	for(int i = 0; i < classes.size(); ++i)
	{
		ClassEntity * c = classes[i];
		int classIndex = addClassEntity(c);

		addParentProperty(classIndex, i, classes);
		addParentRecord(classIndex, i, classes);

	}
}

int ClassMaster::addClassEntity(ClassEntity * c)
{
	ClassEntity * classEntity = new ClassEntity();
	classEntity->m_className = c->m_className;
	classEntity->m_parentIndex = c->m_parentIndex;
	m_classes.push_back(classEntity);
	return (int)m_classes.size() - 1;
}


void ClassMaster::addProperty(int classIndex, const Property& prop)
{
	Property * p    = new Property(prop);
	ClassEntity * c =m_classes[classIndex];
	c->m_props.push_back(p);
}

void ClassMaster::addRecord(int classIndex, const Record& record)
{
	Record * r = new Record(record);
	ClassEntity * c = m_classes[classIndex];
	c->m_records.push_back(r);
}

void ClassMaster::addParentProperty(int classIndex, int parentIndex, const Vector<ClassEntity*> & classes)
{
	if(parentIndex >= 0)
	{
		addParentProperty(classIndex, classes[parentIndex]->m_parentIndex-1, classes);
	}
	else
	{
		return;
	}

	for(int i = 0; i < classes[parentIndex]->m_props.size(); ++i)
	{
		addProperty(classIndex, *classes[parentIndex]->m_props[i]);
	}
}

void ClassMaster::addParentRecord(int classIndex, int parentIndex, const Vector<ClassEntity*> & classes)
{

	if(parentIndex >= 0)
	{
		addParentRecord(classIndex, classes[parentIndex]->m_parentIndex-1, classes);
	}
	else
	{
		return;
	}

	for(int i = 0; i < classes[parentIndex]->m_records.size(); ++i)
	{
		addRecord(classIndex, *classes[parentIndex]->m_records[i]);
	}
}

static int readInt(FILE * pf)
{
	int value = 0;
	fread(&value,4, 1, pf);
	//fscanf_s(pf, "%d", &value);
	return value;
}

static String readStr(FILE * pf)
{
	int len = readInt(pf);
	static char buf[1024];
	fread(buf, len,1, pf);
	String s;
	s.assign(buf, len);
	return s;
}

static Property * readProp(FILE *pf)
{
	Property * p = new Property();
	p->m_name = readStr(pf);
	p->m_type = readInt(pf);
	p->m_public = readInt(pf);
	p->m_private = readInt(pf);
	p->m_save = readInt(pf);
	p->m_atonce= readInt(pf);
//	p->m_master = readStr(pf);
	p->m_explain = readStr(pf);
	return p;
}

static Record * readRecord(FILE *pf)
{
	Record * r = new Record();
	r->m_name = readStr(pf);
	r->m_private = readInt(pf);
	r->m_rowMax= readInt(pf);
	r->m_save = readInt(pf);
//	r->m_master = readStr(pf);
	r->m_explain = readStr(pf);
//	r->m_key = readInt(pf);
	r->m_cols = readInt(pf);
	
	for(int i = 0;i < r->m_cols; ++i)
	{
		int t = readInt(pf);
		r->m_columnTypes.push_back(t);
		String s = readStr(pf);
		r->m_columnNames.push_back(s);
		s = readStr(pf);
		r->m_columnDescs.push_back(s);
	}
	return r;
}


static ClassEntity * readClass(FILE* pf)
{
	ClassEntity * c = new ClassEntity();
	c->m_className   = readStr(pf);
//	c->m_classType    = readInt(pf);
	c->m_explain        = readStr(pf);
//	c->m_parentIndex = readInt(pf);

	//int childcount = readInt(pf);
	//for(int i = 0; i < childcount; ++i)
	//{
	//	c->m_child.push_back(readInt(pf));
	//}

	int propcount = readInt(pf);
	for(int i = 0; i < propcount; ++i)
	{
		Property * p = readProp(pf);
		c->m_props.push_back(p);
		c->m_propIndex[p->m_name] = c->m_props.size() - 1;
		if(p->m_save == DT_TRUE)
			++c->m_savePropCount;
	}

	int recordcount = readInt(pf);
	for(int i = 0; i < recordcount; ++i)
	{
		Record * r = readRecord(pf);
		c->m_records.push_back(r);
		c->m_recordIndex[r->m_name] = c->m_records.size()-1;
		if(r->m_save == DT_TRUE)
			++c->m_saveRecordCount;
	}

	return c;

}



bool ClassMaster::parse(const char * filename)
{
	FILE * pf = fopen(filename, "rb+");

	//Vector<ClassEntity*> raw;

	int classCount = readInt(pf);
	for(int i = 0; i < classCount; ++i)
	{
		ClassEntity * c = readClass(pf);
		m_classes.push_back(c);
		m_classIndex[c->m_className] = i;

//		raw.push_back(c);
	}


	//initClassMaster(raw);


	//for(int i = 0; i < raw.size(); ++i)
	//{
	//	delete raw[i];
	//}

	fclose(pf);
	return true;
}

}


