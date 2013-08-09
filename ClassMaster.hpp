#ifndef CORE_CORE_CLASSMASTER_H__
#define CORE_CORE_CLASSMASTER_H__

#include "typedef.hpp"

namespace core{

enum DataType
{
	DT_INT     = 1,
	DT_FLOAT = 2,
	DT_STR     = 3,
	DT_TRUE   = 1,
	DT_FALSE  = 0


};


class ClassEntity;
class Property;
class Record;

class ClassMaster
{
private:
		ClassMaster();

public:
	~ClassMaster();

	static ClassMaster& getInstance();

	const char* getClassName(int classIndex);
	int getClassType(int classIndex);
	int getClassIndex(const String& className);
	

	const char* getPropertyName(int classIndex, int propIndex);
	int getPropertyType(int classIndex, int propIndex);
	bool getPropertySave(int classIndex, int propIndex);
	bool getPropertyPublic(int classIndex, int propIndex);
	bool getPropertyPrivate(int classIndex, int propIndex);
	bool getPropertyAtonce(int classIndex, int propIndex);
	int getPropertyCount(int classIndex);
	int getPropertySaveCount(int classIndex);
	int getPropertyIndex(int classIndex, const String& propname);

	const char* getRecordName(int classIndex, int recordIndex);
	bool getRecordSave(int classIndex, int recordIndex);
	bool getRecordPrivate(int classIndex, int recordIndex);
	int   getRecordRowMax(int classIndex, int recordIndex);
	int   getColumnType(int classIndex, int recordIndex, int columnIndex);
	const char*  getColumnName(int classIndex, int recordIndex, int columnIndex);
	int getColumnIndex(int classIndex, int recordIndex, const String& columnName);
	int getRecordCount(int classIndex);
	int getRecordSaveCount(int classIndex);
	const Vector<int>& getRecordColumnTypes(int classIndex, int recordIndex); 
	int getRecordIndex(int classIndex, const String& recordname);

	int getPropertyCallback(int classIndex, int propIndex);
	void setPropertyCallback(int classIndex, int propIndex, int cb);
	int getRecordCallback(int classIndex, int recordIndex);
	void setRecordCallback(int classIndex, int recordIndex, int cb);

	bool parse(const char * filename);


private:
	void initClassMaster(const Vector<ClassEntity*> & classes);
	int addClassEntity(ClassEntity * c);
	void addProperty(int classIndex, const Property& prop);
	void addRecord(int classIndex, const Record& record);
	void addParentProperty(int classIndex, int parentIndex, const Vector<ClassEntity*> & classes);
	void addParentRecord(int classIndex, int parentIndex, const Vector<ClassEntity*> & classes);

private:
	Vector<ClassEntity*> m_classes;
	Map<String, int> m_classIndex;
};

}
#endif //CORE_CORE_CLASSMASTER_H__
