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

private:
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
	typedef std::tuple<typename std::remove_reference_t<_This_type>, typename std::remove_reference_t<_Rest>...> _ThisTuple;

	template<class _This, class... _Rest>
	TupleParams(_This&& ft, _Rest&&... args)
		:_t(std::forward<_This>(ft), std::forward<_Rest>(args)...){}
	virtual ~TupleParams(){}

public:
	const _ThisTuple& getTuple(void) const noexcept
	{
		return _t;
	}

private:
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
	using _TupleParamType = TupleParams<typename std::remove_reference_t<_FirstType>, typename std::remove_reference_t<_Types>...>;
	return std::make_shared<_TupleParamType>(std::forward<_FirstType>(ft), std::forward<_Types>(_Args)...);
}


#endif // __TUPLE_PARAMS_H__