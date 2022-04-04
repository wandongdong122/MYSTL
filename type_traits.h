#ifndef MYSTL_TYPE_TRAITS_H_
#define MYSTL_TYPE_TRAITS_H_

// 这个头文件用于提取类型信息

#include <type_traits> 
/*
	type_traits是C++11提供的模板元基础库。
	type_traits可实现在编译期计算、判断、转换、查询等等功能。
	type_traits提供了编译期的true和false
*/

namespace mystl 
{
// helper struct

template <class T,T v>
struct m_integral_constant
{
	// C++11 标准中，定义变量时可以用 constexpr 修饰，从而使该变量获得在编译阶段即可计算出结果的能力,即可以做常量使用。
	static constexpr T value = v;
};

// 判断是true还是false
template <bool b>
using m_bool_constant = m_integral_constant<bool, b>; // 在c++11中可以通过using指定别名

typedef m_bool_constant<true>  m_true_type;
typedef m_bool_constant<false> m_false_type;

/*****************************type traits****************************************/
// 判断是否是pair
template <class T1, class T2>
struct pair;

template <class T>
struct is_pair : mystl::m_false_type{};

template<class T1,class T2>
struct is_pair<mystl::pair<T1,T2> >: mystl::m_true_type{};

} // namespace mystl

#endif // MYSTL_TYPE_TRAITS_H_

