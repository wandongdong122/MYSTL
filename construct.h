#ifndef MYSTL_CONSTRUCT_H_
#define MYSTL_CONSTRUCT_H_

// 这个头文件包含两个函数 construct，destroy
// construct : 负责对象的构造
// destroy   : 负责对象的析构

#include <new>

#include "type_traits.h"
#include "iterator.h"

#ifdef _MSC_VER  // 定义编译器版本
#pragma warning(push)
#pragma warning(disable : 4100)
#endif // _MSC_VER

namespace mystl
{
// construct 构造函数

// 默认构造
template <class Ty>
void construct(Ty* ptr)
{
    ::new ((void*)ptr) Ty();   // 这种new的方式是 placement new 就是在指针ptr所指向的内存空间创建一个Ty类型的对象.
}         //为啥会有强制转换呢

// 有参构造
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
// destroy 将对象析构

template <class Ty>
void destroy_one(Ty*, std::true_type) {}  // 第二个参数表示判断当前类型的析构函数内有没有有效操作，如果没有（true_type）则什么都不做

template <class Ty>
void destroy_one(Ty* pointer, std::false_type)  // 第二个参数表示有有效操作，进行析构
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
