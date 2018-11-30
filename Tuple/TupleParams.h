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
	typedef typename TupleParams<> _Myt;

protected:
	TupleParams(){}
	virtual ~TupleParams(){}

public:
	TupleParams(const _Myt&) = delete;
	TupleParams(_Myt&&) = delete;
	_Myt& operator = (_Myt&) = delete;
	_Myt& operator = (_Myt&&) = delete;
};
using TupleParamsBase = TupleParams<> ;

template<class _This, class... _Rest>
class TupleParams<_This, _Rest...>
	: public TupleParamsBase
{
public:
	typedef _This _This_type;
	typedef TupleParams<_This, _Rest...> _Myt;
	typedef std::tuple<_This_type, _Rest...> _ThisTuple;

	template<class _This2, class... _Rest2>
	constexpr TupleParams(_This2&& ft, _Rest2&&... args)
		:_t(std::forward<_This2>(ft), std::forward<_Rest2>(args)...){}
	virtual ~TupleParams(){}

public:
	constexpr _ThisTuple& getTuple(void) noexcept
	{
		return _t;
	}

public:
	TupleParams(const _Myt&) = delete;
	TupleParams(_Myt&&) = delete;
	_Myt& operator = (_Myt&) = delete;
	_Myt& operator = (_Myt&&) = delete;

private:
	_ThisTuple _t;
};

template<typename _FirstType, typename..._Types>
decltype(auto) new_tuple_params(_FirstType&& ft, _Types&&... _Args)
{
	using _TupleParamType = TupleParams<std::_Unrefwrap_t<_FirstType>, std::_Unrefwrap_t<_Types>...>;
	return std::make_shared<_TupleParamType>(std::forward<_FirstType>(ft), std::forward<_Types>(_Args)...);
}


#endif // __TUPLE_PARAMS_H__