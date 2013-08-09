#ifndef CORE_CORE_PROTOMANAGER_H__
#define CORE_CORE_PROTOMANAGER_H__

#include "Log.hpp"
#include "typedef.hpp"
#include "core.hpp"

namespace core{

class Member
{
public:
	core::String name;
	core::String type;
	core::String desc;
	core::String repeat;

};

class Protocol
{
public:
	int id;
	core::String name;
	core::String desc;
	core::Vector<Member> mems;
};

class Struct
{
public:
	core::String name;
	core::String desc;
	core::Vector<Member> mems;
};

class ProtoManager
{
private:
	ProtoManager();

public:
	static ProtoManager& getInstance()
	{
		static ProtoManager ins;
		return ins;
	}

	bool parseProto(const char * protofile);
	void print(int userID, char * buf, int size);
	void printStruct(IStream & is, core::String& structName, core::String& out);

private:
	core::Map<int, Protocol*> m_protos;
	core::Map<core::String, Struct*> m_structs;
	Logger  m_logger;
};

}
#endif //CORE_CORE_PROTOMANAGER_H__