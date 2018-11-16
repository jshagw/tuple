#pragma once
#ifndef __TUPLE_PARAMS_H__
#define __TUPLE_PARAMS_H__

#include <tuple>
#include <memory>
#include <share.h>

template<class... _Types>
class TupleParams;

template<> 
class TupleParams<>
{
public:
	typedef typename TupleParams<> _Myt;
	TupleParams(){}
	virtual ~TupleParams(){}

private:
	TupleParams(_Myt&) = delete;
	_Myt& operator = (_Myt&) = delete;
};
typedef TupleParams<> TupleParamsBase;

template<class _This, class... _Rest>
class TupleParams<_This, _Rest...>
	: public TupleParamsBase
{
public:
	typedef _This _This_type;
	typedef TupleParams<_This, _Rest...> _Myt;
	typedef std::tuple<typename std::remove_reference_t<_This_type>, typename std::remove_reference_t<_Rest>...> _ThisTuple;
	TupleParams(_This&& t, _Rest&&...)
		:_t(t)
	{

	}

	virtual ~TupleParams()
	{

	}

public:
	const _ThisTuple& getTuple(void) const
	{
		return _t;
	}

private:
	//template<class _This, class... _Rest>
	TupleParams(_Myt&) = delete;
	_Myt& operator = (_Myt&) = delete;

private:
	_ThisTuple _t;
};

typedef std::shared_ptr<TupleParamsBase> TupleParamsBasePtr;

template<typename _FirstType, typename..._Types>
decltype<auto> new_tuple_params(_FirstType&& ft, _Types&&... _Args)
{
	using _TupleParamType = TupleParams<typename std::remove_reference_t<_FirstType>, typename std::remove_reference_t<_Types>...>;
	return std::make_unique<_TupleParamType>(std::forward<std::remove_reference_t<_FirstType>>(ft),
		std::forward<std::remove_reference_t<_Types>>(_Args)...);
}


#endif // __TUPLE_PARAMS_H__