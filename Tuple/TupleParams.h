#pragma once
#ifndef __TUPLE_PARAMS_H__
#define __TUPLE_PARAMS_H__

#include <tuple>
#include <memory>

template<class... _Types>
class TupleParams;

template<> 
class TupleParams<>
{
public:
	typedef TupleParams<> _Myt;
	typedef std::shared_ptr<_Myt> _MyPtr;
	TupleParams(){}
	virtual ~TupleParams(){}

private:
	TupleParams(_Myt&);
	_Myt& operator = (_Myt&);
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
	TupleParams(_ThisTuple&& t)
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
	template<class _This, class... _Rest>
	TupleParams(_Myt&);
	_Myt& operator = (_Myt&);

private:
	_ThisTuple _t;
};

typedef std::shared_ptr<TupleParamsBase> TupleParamsBasePtr;

template<typename _FirstType, typename..._Types>
TupleParamsBasePtr new_tuple_params(_FirstType&& ft, _Types&&... _Args)
{
	typedef TupleParams<typename std::remove_reference_t<_FirstType>, typename std::remove_reference_t<_Types>...> _TupleParamType;
	return std::shared_ptr<_TupleParamType>(new _TupleParamType(std::make_tuple(std::forward<_FirstType>(ft), std::forward<_Types>(_Args)...)));
}


#endif // __TUPLE_PARAMS_H__