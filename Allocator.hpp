#ifndef	CORE_CORE_ALLOCATOR_H__
#define CORE_CORE_ALLOCATOR_H__

template<typename _Ty>
class Allocator
{	// generic allocator for objects of typename _Ty
public:
	typedef _Ty value_type;
	typedef value_type * pointer;
	typedef value_type & reference;
	typedef const value_type * const_pointer;
	typedef const value_type & const_reference;

	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template<typename _Other>
	struct rebind
	{	// convert an allocator<_Ty> to an allocator <_Other>
		typedef Allocator<_Other> other;
	};

	pointer address(reference _Val) const
	{	// return address of mutable _Val
		return (&_Val);
	}

	const_pointer address(const_reference _Val) const
	{	// return address of nonmutable _Val
		return (&_Val);
	}

	Allocator()
	{	// construct default allocator (do nothing)
	}

	Allocator(const Allocator<_Ty>&)
	{	// construct by copying (do nothing)
	}

	template<typename _Other>
	Allocator(const Allocator<_Other>&)
	{	// construct from a related allocator (do nothing)
	}

	template<class _Other>
	Allocator<_Ty>& operator=(const Allocator<_Other>&)
	{	// assign from a related allocator (do nothing)
		return (*this);
	}

	void deallocate(pointer _Ptr, size_type);

	pointer allocate(size_type _Count);

	pointer allocate(size_type _Count, const void *)
	{	// allocate array of _Count elements, ignore hint
		return (allocate(_Count));
	}

	void construct(pointer _Ptr, const _Ty& _Val)
	{	// construct object at _Ptr with value _Val
		::new(_Ptr) _Ty(_Val);
	}

	void destroy(pointer _Ptr)
	{	// destroy object at _Ptr
		_Ptr->~_Ty();
	}

	size_type max_size() const
	{	// estimate maximum array size
		size_type _Count = (size_type)(-1) / sizeof (_Ty);
		return (0 < _Count ? _Count : 1);
	}
};

// allocator TEMPLATE OPERATORS
template<typename _Ty,typename _Other> 
inline bool operator==(const Allocator<_Ty>&, const Allocator<_Other>&)
{	// test for allocator equality (always true)
	return (true);
}

template<typename _Ty,typename _Other> 
inline bool operator!=(const Allocator<_Ty>&, const Allocator<_Other>&)
{	// test for allocator inequality (always false)
	return (false);
}

template<typename _Ty>
void Allocator<_Ty>::deallocate(pointer _Ptr, size_type sz)
{	// deallocate object at _Ptr, ignore size
	core_free(_Ptr,sz * sizeof(_Ty));
}

template<typename _Ty>
typename Allocator<_Ty>::pointer Allocator<_Ty>::allocate(size_type _Count)
{	// allocate array of _Count elements
	return (_Ty*)core_malloc(sizeof(_Ty) * _Count);
}

#endif //CORE_CORE_ALLOCATOR_H__


