#ifndef CORE_CORE_IDATA_H__
#define  CORE_CORE_IDATA_H__

#include "ObjectID.hpp"
#include "typedef.hpp"

namespace core{

class IData
{
public:
	IData(){}
	virtual ~IData(){}

	virtual void removeObject(const ObjectID& objID) = 0;

	virtual int getInt(const ObjectID& objID, int propIndex) = 0;
	virtual void setInt(const ObjectID& objID, int propIndex, int value) = 0;
	virtual float getFloat(const ObjectID& objID, int propIndex) = 0;
	virtual void setFloat(const ObjectID& objID, int propIndex, float value) = 0;
	virtual const String& getStr(const ObjectID& objId, int propIndex) = 0;
	virtual void setStr(const ObjectID& objID, int propIndex, const String& value) = 0;

	virtual int getRecordInt(const ObjectID& objID, int recordIndex, int row, int column) = 0;
	virtual void setRecordInt(const ObjectID& objID, int recordIndex, int row, int column, int value) = 0;
	virtual float getRecordFloat(const ObjectID& objID, int recordIndex, int row, int column) = 0;
	virtual void setRecordFloat(const ObjectID& objID, int recordIndex, int row, int column, float value) = 0;
	virtual const String& getRecordStr(const ObjectID& objID, int recordIndex, int row, int column) = 0;
	virtual void setRecordStr(const ObjectID& objID, int recordIndex, int row, int column, const String& value) = 0;

	virtual int addRecordRow(const ObjectID& objID, int recordIndex) = 0;
	virtual void deleteRecordRow(const ObjectID& objID, int recordIndex, int row) = 0;
	virtual int getRecordRows(const ObjectID& objID, int recordIndex) = 0;
	virtual int findRecordInt(ObjectID& objID, int recordIndex, int column, int value) = 0;
	virtual int findRecordFloat(ObjectID& objID, int recordIndex, int column, float value) = 0;
	virtual int findRecordStr(ObjectID& objID, int recordIndex, int column, const String& value) = 0;



};

}
#endif //CORE_CORE_IDATA_H__

