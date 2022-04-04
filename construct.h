#ifndef MYSTL_CONSTRUCT_H_
#define MYSTL_CONSTRUCT_H_

// ���ͷ�ļ������������� construct��destroy
// construct : �������Ĺ���
// destroy   : ������������

#include <new>

#include "type_traits.h"
#include "iterator.h"

#ifdef _MSC_VER  // ����������汾
#pragma warning(push)
#pragma warning(disable : 4100)
#endif // _MSC_VER

namespace mystl
{
// construct ���캯��

// Ĭ�Ϲ���
template <class Ty>
void construct(Ty* ptr)
{
    ::new ((void*)ptr) Ty();   // ����new�ķ�ʽ�� placement new ������ָ��ptr��ָ����ڴ�ռ䴴��һ��Ty���͵Ķ���.
}         //Ϊɶ����ǿ��ת����

// �вι���
template <class Ty1, class Ty2>
void construct(Ty1* ptr, const Ty2& value)
{
	::new ((void*)ptr) Ty1(value);
}

template <class Ty, class... Args>
void construct(Ty* ptr, Args&&... args)
{
    ::new ((void*)ptr) Ty(mystl::forward<Args>(args)...);
}
// destroy ����������

template <class Ty>
void destroy_one(Ty*, std::true_type) {}  // �ڶ���������ʾ�жϵ�ǰ���͵�������������û����Ч���������û�У�true_type����ʲô������

template <class Ty>
void destroy_one(Ty* pointer, std::false_type)  // �ڶ���������ʾ����Ч��������������
{
    if (pointer != nullptr)
    {
        pointer->~Ty();
    }
}

template <class ForwardIter>
void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
{
    for (; first != last; ++first)
        destroy(&*first);
}

template <class Ty>
void destroy(Ty* pointer)
{
    destroy_one(pointer, std::is_trivially_destructible<Ty>{});
}

template <class ForwardIter>
void destroy(ForwardIter first, ForwardIter last)
{
    destroy_cat(first, last, std::is_trivially_destructible<
        typename iterator_traits<ForwardIter>::value_type>{});
}

} // namespace MYSTL



#endif // MYSTL_CONSTRUCT_H_H
