#include "ProtoManager.hpp"
#include <stdio.h>
#include <iostream>
#include "utils.hpp"

namespace core{

static int readInt(FILE * pf)
{
	int value = 0;
	fread(&value,4, 1, pf);
	//fscanf_s(pf, "%d", &value);
	return value;
}

static core::String readStr(FILE * pf)
{
	int len = readInt(pf);
	static char buf[1024];
	fread(buf, len,1, pf);
	core::String s;
	s.assign(buf, len);
	return s;
}

ProtoManager::ProtoManager()
{
	m_logger = Logger::getInstance(LOG4CPLUS_TEXT("rootLogger"));
}

bool ProtoManager::parseProto(const char * protofile)
{
	FILE * pf = fopen(protofile, "rb+");
	
	{
		int protosize = readInt(pf);
		for(int i = 0; i < protosize; ++i)
		{
			Protocol * p = new Protocol();
			p->id = readInt(pf);
			p->name = readStr(pf);
			p->desc = readStr(pf);
			int memsize = readInt(pf);
			for(int j = 0; j < memsize; ++j)
			{
				Member m;
				m.name = readStr(pf);
				m.type = readStr(pf);
				m.desc = readStr(pf);
				m.repeat = readStr(pf);
				p->mems.push_back(m);
			}
			m_protos[p->id] = p;
		}
	}
		
	
	{


		int structsize = readInt(pf);
		for(int i = 0; i < structsize; ++i)
		{
			Struct* str = new Struct();
			str->name = readStr(pf);
			str->desc = readStr(pf);
			int memsize = readInt(pf);
			for(int j = 0; j < memsize; ++j)
			{
				Member m;
				m.name = readStr(pf);
				m.type = readStr(pf);
				m.desc = readStr(pf);
				m.repeat = readStr(pf);
				str->mems.push_back(m);
			}
			m_structs[str->name] = str;
		}
		{
			Struct* str = new Struct();
			str->name = "ObjectID";
			str->desc = "¶ÔÏóID";
			Member m;
			m.name = "type";
			m.type = "i32";
			m.desc = "";
			m.repeat = "";
			str->mems.push_back(m);

			Member m1;
			m1.name = "ownerID";
			m1.type = "i32";
			m1.desc = "";
			m1.repeat = "";
			str->mems.push_back(m1);

			Member m2;
			m2.name = "index";
			m2.type = "i32";
			m2.desc = "";
			m2.repeat = "";
			str->mems.push_back(m2);
			m_structs[str->name] = str;
		}
	}

	fclose(pf);

	return true;
}


void ProtoManager::print(int userID, char * buf, int size)
{
	IStream is(buf, size);
	core::MessageID mid;
	is >> mid;
	core::Map<int, Protocol*>::iterator it = m_protos.find(mid);
	if(it != m_protos.end())
	{
		core::String out;
		out = itos(userID);
		out += "    ";
		Protocol * p = it->second;
		out += p->name + ":{";
		for(int i = 0; i < p->mems.size(); ++i)
		{
			if(i != 0)
			{
				out.append(",");
			}

			if(p->mems[i].type == "i32")
			{

				out.append(p->mems[i].name.c_str());
				out.append(":");

				if(p->mems[i].repeat == "true")
				{
					out.append("[");
					short size;
					is >> size;
					for(int j = 0; j < size; ++j)
					{
						if(j != 0)
						{
							out.append(",");
						}
						int v;
						is >> v;
						out.append(itos(v));
					}
					out.append("]");
				}
				else
				{
					int v;
					is >> v;
					out.append(itos(v));

				}

			}
			else if(p->mems[i].type == "string")
			{
				out.append(p->mems[i].name.c_str());
				out.append(":");

				if(p->mems[i].repeat == "true")
				{
					out.append("[");
					short size;
					is >> size;
					for(int j = 0; j < size; ++j)
					{
						if(j != 0)
						{
							out.append(",");
						}
						core::String v;
						is >> v;
						out.append(v);
					}
					out.append("]");
				}
				else
				{
					core::String v;
					is >> v;
					out.append(v);

				}

			}
			else
			{
				out.append(p->mems[i].name.c_str());
				out.append(":");

				if(p->mems[i].repeat == "true")
				{
					out.append("[");
					short size;
					is >> size;
					for(int j = 0; j < size; ++j)
					{
						if(j != 0)
						{
							out.append(",");
						}
						printStruct(is, p->mems[i].type, out);
					}
					out.append("]");
				}
				else
				{
					printStruct(is, p->mems[i].type, out);
				}
			}
		}
		out.append("}");
		//std::cout << out << std::endl;
		LOG_DEBUG(m_logger, out.c_str());
	}

}

void ProtoManager::	printStruct(IStream & is, core::String& structName, core::String& out)
{
	core::Map<core::String, Struct*>::iterator it = m_structs.find(structName);
	if(it != m_structs.end())
	{
		out.append("{");
		Struct* p = it->second;
		for(int i = 0; i < p->mems.size(); ++i)
		{
			if(i != 0)
			{
				out.append(",");
			}

			if(p->mems[i].type == "i32")
			{

				out.append(p->mems[i].name.c_str());
				out.append(":");

				if(p->mems[i].repeat == "true")
				{
					out.append("[");
					short size;
					is >> size;
					for(int j = 0; j < size; ++j)
					{
						if(j != 0)
						{
							out.append(",");
						}
						int v;
						is >> v;
						out.append(itos(v));
					}
					out.append("]");
				}
				else
				{
					int v;
					is >> v;
					out.append(itos(v));

				}

			}
			else if(p->mems[i].type == "string")
			{
				out.append(p->mems[i].name.c_str());
				out.append(":");

				if(p->mems[i].repeat == "true")
				{
					out.append("[");
					short size;
					is >> size;
					for(int j = 0; j < size; ++j)
					{
						if(j != 0)
						{
							out.append(",");
						}
						core::String v;
						is >> v;
						out.append(v);
					}
					out.append("]");
				}
				else
				{
					core::String v;
					is >> v;
					out.append(v);

				}

			}
			else
			{
				out.append(p->mems[i].name.c_str());
				out.append(":");

				if(p->mems[i].repeat == "true")
				{
					out.append("[");
					short size;
					is >> size;
					for(int j = 0; j < size; ++j)
					{
						if(j != 0)
						{
							out.append(",");
						}
						printStruct(is, p->mems[i].type, out);
					}
					out.append("]");
				}
				else
				{
					printStruct(is, p->mems[i].type, out);
				}
			}
		}
		out.append("}");

	}
}

}


