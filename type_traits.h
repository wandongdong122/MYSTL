#ifndef MYSTL_TYPE_TRAITS_H_
#define MYSTL_TYPE_TRAITS_H_

// ���ͷ�ļ�������ȡ������Ϣ

#include <type_traits> 
/*
	type_traits��C++11�ṩ��ģ��Ԫ�����⡣
	type_traits��ʵ���ڱ����ڼ��㡢�жϡ�ת������ѯ�ȵȹ��ܡ�
	type_traits�ṩ�˱����ڵ�true��false
*/

namespace mystl 
{
// helper struct

template <class T,T v>
struct m_integral_constant
{
	// C++11 ��׼�У��������ʱ������ constexpr ���Σ��Ӷ�ʹ�ñ�������ڱ���׶μ��ɼ�������������,������������ʹ�á�
	static constexpr T value = v;
};

// �ж���true����false
template <bool b>
using m_bool_constant = m_integral_constant<bool, b>; // ��c++11�п���ͨ��usingָ������

typedef m_bool_constant<true>  m_true_type;
typedef m_bool_constant<false> m_false_type;

/*****************************type traits****************************************/
// �ж��Ƿ���pair
template <class T1, class T2>
struct pair;

template <class T>
struct is_pair : mystl::m_false_type{};

template<class T1,class T2>
struct is_pair<mystl::pair<T1,T2> >: mystl::m_true_type{};

} // namespace mystl

#endif // MYSTL_TYPE_TRAITS_H_

