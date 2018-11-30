#pragma once
#ifndef __TUPLE_PARAMS_H__
#define __TUPLE_PARAMS_H__

#include <tuple>
#include <memory>

class TupleParamsBase
{
public:
	TupleParamsBase(){}
	virtual ~TupleParamsBase(){}
};

template<class _This, class... _Rest>
class TupleParams
	: public TupleParamsBase
	, public std::tuple<_This, _Rest...>
{
public:
	typedef _This _This_type;
	typedef TupleParams<_This, _Rest...> _Myt;
	typedef std::tuple<_This_type, _Rest...> _ThisTuple;

	template<class _This2, class... _Rest2>
	constexpr TupleParams(_This2&& ft, _Rest2&&... args)
		:_ThisTuple(std::forward<_This2>(ft), std::forward<_Rest2>(args)...){}
	virtual ~TupleParams(){}

public:
	TupleParams(const _Myt&) = delete;
	TupleParams(_Myt&&) = delete;
	_Myt& operator = (_Myt&) = delete;
	_Myt& operator = (_Myt&&) = delete;
};

template<typename _FirstType, typename..._Types>
decltype(auto) new_tuple_params(_FirstType&& ft, _Types&&... _Args)
{
	using _TupleParamType = TupleParams<std::_Unrefwrap_t<_FirstType>, std::_Unrefwrap_t<_Types>...>;
	return std::make_unique<_TupleParamType>(std::forward<_FirstType>(ft), std::forward<_Types>(_Args)...);
}


#endif // __TUPLE_PARAMS_H__