#ifndef CORE_CORE_HASH_H__
#define CORE_CORE_HASH_H__

namespace core{

template <typename T>
class Hash
{
	enum{MAX_LEN = 0x10000};
	union id_t
	{
		int data;
		struct rid
		{
			short id;
			short r;
		};
	};

public:
	Hash();
	~Hash();

	int add(T * v);
	T* find(int idx);
	int size();
	void remove(int idx);
	void removeAll();

private:
	short getR(int idx)
	{
		id_t id;
		id.data = idx;
		return id.rid.r;
	}

	short getID(int idx)
	{
		id_t id;
		id.data = idx;
		return id.rid.id;
	}

private:
	T**     m_item;
	short* m_rand;
	int      m_cur;
	int      m_size;
};

template <typename T>
Hash<T>::Hash():
	m_cur(0),
	m_size(0)
{
	m_item = new T*[MAX_LEN];
	m_rand  = new short[MAX_LEN];
	for(int i = 0; i < MAX_LEN; ++i)
	{
		m_item[i] = NULL;
		m_rand[i] = 0;
	}
}

template <typename T>
Hash<T>::~Hash()
{
	removeAll();
	delete [] m_item;
	delete [] m_rand;
}

template <typename T>
int Hash<T>::add(T* v)
{
	for(; m_cur < MAX_LEN && m_item[m_cur] != NULL; ++m_cur);

	if(m_cur < MAX_LEN && m_item[m_cur] == NULL)
	{
		m_item[m_cur] = v;
		++m_size;
		return m_cur++;
	}

	for(m_cur = 0; m_cur < MAX_LEN && m_item[m_cur]; ++m_cur);

	if(m_cur < MAX_LEN && m_item[m_cur] == NULL)
	{
		m_item[m_cur] = v;
		++m_size;
		return m_cur++;
	}
	return -1;
}

template <typename T>
T* Hash<T>::find(int idx)
{
	if(idx >= 0 && idx < MAX_LEN)
	{
		return m_item[idx];
	}
	return NULL;
}

template <typename T>
int Hash<T>::size()
{
	return m_size;
}

template <typename T>
void Hash<T>::remove(int idx)
{
	if(idx >= 0 && idx < MAX_LEN && m_item[idx] != NULL)
	{
		delete m_item[idx];
		m_item[idx] = NULL;
		--m_size;
	}

}

template <typename T>
void Hash<T>::removeAll()
{
	for(int i = 0; i < MAX_LEN; ++i)
	{
		if(m_item[i] != NULL)
		{
			delete m_item[i];
			m_item[i] = NULL;
		}
	}
	m_cur = 0;
}
}

#endif //CORE_CORE_HASH_H__

