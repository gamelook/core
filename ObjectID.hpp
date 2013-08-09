#ifndef CORE_CORE_OBJECTID_H__
#define CORE_CORE_OBJECTID_H__

namespace core{

class ObjectID
{
public:
	ObjectID():
	  type(-1), ownerID(-1), index(-1)
	{
	}

	ObjectID(int t, int o, int i):
		type(t),ownerID(o),index(i)
	{
	}

	ObjectID(const ObjectID& objID):
		type(objID.type), ownerID(objID.ownerID), index(objID.index)
	{

	}

	ObjectID& operator = (const ObjectID& objID)
	{
		type = objID.type;
		ownerID = objID.ownerID;
		index = objID.index;
		return *this;
	}

	bool operator == (const ObjectID& objID)
	{
		if(type == objID.type && ownerID == objID.ownerID && index == objID.index)
			return true;
		else
			return false;
	}

	bool isValid()
	{
		if(type == -1 || ownerID == -1 || index == -1)
		{
			return false;
		}
		return true;
	}

	int type;
	int ownerID;
	int index;

};

template <typename AR>
AR& operator >> (AR& ar, ObjectID& data)
{
	ar >> data.type;
	ar >> data.ownerID;
	ar >> data.index;
	return ar;
}

template <typename AR>
AR& operator << (AR& ar, const ObjectID& data)
{
	ar << data.type;
	ar << data.ownerID;
	ar << data.index;
	return ar;
}

}
#endif //CORE_CORE_OBJECTID_H__

