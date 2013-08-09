#ifndef CORE_CORE_OBJECTMASTER_H__
#define CORE_CORE_OBJECTMASTER_H__

#include "IData.hpp"

class ObjectEntity;

namespace core{

class ObjectMaster:
	public IData
{
public:
	ObjectMaster(int ownerID, int type, int size);
	virtual ~ObjectMaster();

	virtual int getClassIndex(const ObjectID& objID);

	virtual ObjectID addObject(int classIndex);
	virtual ObjectID addObject(int index, int classIndex);
	virtual void removeObject(const ObjectID& objID);

	virtual int getInt(const ObjectID& objID, int propIndex);
	virtual void setInt(const ObjectID& objID, int propIndex, int value);
	virtual float getFloat(const ObjectID& objID, int propIndex);
	virtual void setFloat(const ObjectID& objID, int propIndex, float value);
	virtual const String& getStr(const ObjectID& objId, int propIndex);
	virtual void setStr(const ObjectID& objID, int propIndex, const String& value);

	virtual int getRecordInt(const ObjectID& objID, int recordIndex, int row, int column);
	virtual void setRecordInt(const ObjectID& objID, int recordIndex, int row, int column, int value);
	virtual float getRecordFloat(const ObjectID& objID, int recordIndex, int row, int column);
	virtual void setRecordFloat(const ObjectID& objID, int recordIndex, int row, int column, float value);
	virtual const String& getRecordStr(const ObjectID& objID, int recordIndex, int row, int column);
	virtual void setRecordStr(const ObjectID& objID, int recordIndex, int row, int column, const String& value);

	virtual int addRecordRow(const ObjectID& objID, int recordIndex);
	virtual void deleteRecordRow(const ObjectID& objID, int recordIndex, int row);
	virtual int getRecordRows(const ObjectID& objID, int recordIndex);
	virtual int findRecordInt(ObjectID& objID, int recordIndex, int column, int value);
	virtual int findRecordFloat(ObjectID& objID, int recordIndex, int column, float value);
	virtual int findRecordStr(ObjectID& objID, int recordIndex, int column, const String& value);

	bool toSaveStream(const ObjectID& objID, OStream& os);
	bool fromSaveStream(ObjectID& objID, IStream& is);

	bool toSaveStream(OStream& os);
	bool fromSaveStream(IStream& is);

protected:
	int m_ownerID;
	int m_type;

private:
	int m_size;
	int m_count;
	ObjectEntity** m_objects;

};
}
#endif //CORE_CORE_OBJECTMASTER_H__

