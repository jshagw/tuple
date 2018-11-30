// Tuple.cpp : 定义控制台应用程序的入口点。
//

#include <tuple>
#include <memory>
#include <string>
#include <iostream>
#include <assert.h>
#include "TupleParams.h"

using namespace std;

class Packet
{
public:
	Packet(){

	}

	~Packet()
	{

	}

	template<typename _FirstType, typename..._Types>
	void setParams(_FirstType&& ft, _Types&&... _Args)
	{
		_p = std::move(new_tuple_params(ft, _Args...));
	}

	template<typename _FirstType, typename..._Types>
	bool getParams(_FirstType& ft, _Types&... _Args)
	{
		using _TupleParamType = TupleParams<std::_Unrefwrap_t<_FirstType>, std::_Unrefwrap_t<_Types>...>;
		std::shared_ptr<_TupleParamType> p = dynamic_pointer_cast<_TupleParamType, TupleParamsBase>(_p);
		assert(p);
		if (p)
		{
			std::tie(ft, _Args...) = p->getTuple();
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	std::shared_ptr<TupleParamsBase> _p;
};

int main(int argc, char* argv[])
{
	int i = 2;
	string s = "333";
	string& sref = s;

	typedef std::shared_ptr<unsigned char> BytePtr;
	size_t blen = 1000;
	BytePtr bp(new unsigned char[blen]);

	Packet pack;
	pack.setParams(3, s, sref, bp, blen);

	int n = 0;
	string ss1;
	string&& ss2 = "";
	string &rs2 = ss2;
	long l = 0;
	size_t blen2;
	BytePtr bp2;
	pack.getParams(n, ss1, ss2, bp2, blen2);

	cout << n << " " << ss1 << " " << ss2 << endl;

	/*auto p = new_child(i,s);

	//for (size_t i = 0; i < 100; i++)
	{
		auto ppp = new_child(shared_ptr<char>(new char[1000 * 1024]));
		shared_ptr<remove_pointer<decltype(ppp)>::type> sp(ppp);
		int j = (i+5);
		(void)j;
	}

	auto str = shared_ptr<char>(new char[1000*1024]);
	strcpy_s(str.get(), 100, "this is test string");

	auto p1 = new_child(1, "2", str);
	str.reset();
	{
		shared_ptr<Base> bsp;
		{
			shared_ptr<remove_pointer<decltype(p)>::type> sp(p);
			bsp = sp;
		}

		shared_ptr<remove_pointer<decltype(p1)>::type> sp1(p1);

		cout << "p is " << p << endl;
		cout << "sp1 is " << sp1 << endl;
		cout << "bsp is " << bsp << endl;
		cout << get<0>(p->get()) << " " << get<1>(p->get()) << endl;
		cout << get<2>(sp1->get()) << endl;
	}*/
/*	shared_ptr<Base> b(new Child<int,string>(make_tuple(2, "3333")));
	shared_ptr<Child<int, string>> p = dynamic_pointer_cast<Child<int, string>, Base>(b);
	shared_ptr<Base> b1 = p;
	cout << "b is " << b << endl;
	cout << "p is " << p << endl;
	cout << "b1 is " << b1 << endl;
	cout << get<0>(p->get()) << " " << get<1>(p->get()) << endl;
*/
	typedef tuple<> tuple_base;
	typedef tuple<int, string> tuple_int_string;

	//tuple_base * pB = nullptr;
	//tuple_int_string *pS = new tuple_int_string(2, "333");

	//pB = pS;

	//shared_ptr<tuple_base> base;
	//shared_ptr<tuple_int_string> p1(new tuple_int_string(1, "200"));
	//base = p1;

	int kkk = 0;
	kkk++;


	return 0;
}

