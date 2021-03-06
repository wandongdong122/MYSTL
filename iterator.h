#ifndef MYSTL_ITERATOR_H_
#define MYSTL_ITERATOR_H_

// 这个头文件用于迭代器设计，包含了一些模板结构体与全局函数

#include <cstddef>  // 是stddef.h的C++版本  stddef.h定义了一些标准宏以及类型，是C语言标准所必须的一部分。
#include "type_traits.h"

namespace mystl
{
// 声明五种迭代器类型
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};

// iterator 模板
template <class Category,class T, class Distance = ptrdiff_t,
		  class Pointer = T*, class Reference = T&>
struct iterator  // 迭代器类，声明了迭代器的5个“属性”（迭代器所指对象的型别）
{
	typedef Category                          iterator_category;		// 迭代器类种类
	typedef T                                 value_type;				// 迭代器所指向的值的类型
	typedef Pointer                           pointer;					// 迭代器所指向的值的类型的指针
	typedef Reference                         reference;				// 迭代器所指向的值的类型的引用
	typedef Distance                          difference_type;			// 指针相减的结果类型
};

// iterator traits
template <class T>
struct has_iterator_cat
{
private:
	struct two { char a; char b; };  //声明一个结构体
	// 声明了一个函数并且进行重载，但不知道有啥用(大概是用来判断迭代器iterator_category*属性是否为空)
	// 如果只传入一个iterator_category参数则返回true，否则返回false
	template <class U> static two test(...);
	template <class U> static char test(typename U::iterator_category* = 0);  
public:
	// 给定一个bool变量
	static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

// 一个迭代器萃取的对外接口
template <class Iterator, bool>
struct iterator_traits_impl {};

template <class Iterator>
struct iterator_traits_impl<Iterator,true>
{	
	// 萃取出传入迭代器的性质
	typedef typename Iterator::iterator_category  iterator_category;
	typedef typename Iterator::value_type         value_type;
	typedef typename Iterator::pointer            pointer;
	typedef typename Iterator::reference          reference;
	typedef typename Iterator::difference_type    difference_type;
};

template <class Iterator,bool>
struct iterator_traits_helper{};

template <class Iterator>
struct iterator_traits_helper<Iterator, true>
	: public iterator_traits_impl<Iterator,
	std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||   // 用于检查是否可以将任何数据类型A隐式转换为任何数据类型B。它返回布尔值true或false。
	std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
{
};

// 萃取迭代器的特征
template <class Iterator>
struct iterator_traits
	: public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>{}; // 判断这个迭代器是否具有cat的特征 
								
// 针对原生指针的偏特化版本
template <class T>
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag           iterator_category;  // 原生指针的迭代器的类型就是随机迭代器
	typedef T                                    value_type;
	typedef T*									 pointer;
	typedef T&									 reference;
	typedef ptrdiff_t                            difference_type;
};

// 对于const原生指针的偏特化版本
template <class T>
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag           iterator_category;
	typedef T                                    value_type;
	typedef const T*							 pointer;
	typedef const T&							 reference;
	typedef ptrdiff_t                            difference_type;
};

template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of
	: public m_bool_constant<std::is_convertible<
	typename iterator_traits<T>::iterator_category, U>::value> // 当前迭代器的种类是否可以转换成U
{
};

// 萃取某种迭代器
template <class T, class U>
struct has_iterator_cat_of<T,U,false> :public m_false_type{};

template <class Iter>
struct is_input_iterator: public has_iterator_cat_of<Iter,input_iterator_tag> {}; // 判断是不是input_iterator_tag

template <class Iter>
struct is_output_iterator:public has_iterator_cat_of<Iter,output_iterator_tag>{}; // 判断是不是output_iterator_tag

template <class Iter>
struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};  // 判断是不是forward_iterator_tag

template <class Iter>
struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};  // 判断是不是bidirectional_iterator_tag

template <class Iter>
struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};  // 判断是不是random_access_iterator_tag

template <class Iterator>
struct is_iterator :   // 判断是input_iterator_tag或者是output_iterator_tag
	public m_bool_constant<is_input_iterator<Iterator>::value ||
	is_output_iterator<Iterator>::value>
{
};

// 萃取某个迭代器的 category
template <class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
	typedef typename iterator_traits<Iterator>::iterator_category Category;
	return Category();  // 返回的是一个匿名对象
}

// 萃取某个迭代器的 distance_type
template <class Iterator>
typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&)
{
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0); // 强制类型转换，将int转换成给定类型
}

// 萃取某个迭代器的 value_type
template <class Iterator>
typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&)
{
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}


// 以下函数用于计算迭代器间的距离
// distance 的 input_iterator_tag 的版本
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

// distance 的 random_access_iterator_tag 的版本
template <class RandomIter>
typename iterator_traits<RandomIter>::difference_type
distance_dispatch(RandomIter first, RandomIter last,
	random_access_iterator_tag)
{
	return last - first;
}

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	return distance_dispatch(first, last, iterator_category(first));
}


// 以下函数用于让迭代器前进 n 个距离

// advance 的 input_iterator_tag 的版本
template <class InputIterator, class Distance>
void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag)
{
	while (n--)
		++i;
}

// advance 的 bidirectional_iterator_tag 的版本
template <class BidirectionalIterator, class Distance>
void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
	if (n >= 0)
		while (n--)  ++i;
	else
		while (n++)  --i;
}

// advance 的 random_access_iterator_tag 的版本
template <class RandomIter, class Distance>
void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag)
{
	i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n)
{
	advance_dispatch(i, n, iterator_category(i));
}

/******************************  reverse_iterator  ***************************************/

// 模板类 : reverse_iterator
// 代表反向迭代器，使前进为后退，后退为前进
template<class Iterator>
class reverse_iterator
{
private:
	Iterator current; // 记录对应的正向迭代器

public:
	// 反向迭代器的五种相应型别
	typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
	typedef typename iterator_traits<Iterator>::value_type         value_type;
	typedef typename iterator_traits<Iterator>::difference_type    difference_type;
	typedef typename iterator_traits<Iterator>::pointer            pointer;
	typedef typename iterator_traits<Iterator>::reference          reference;

	typedef Iterator                                               iterator_type;
	typedef reverse_iterator<Iterator>                             self;

public:
	// 构造函数
	reverse_iterator() {}
	explicit reverse_iterator(iterator_type i) :current(i) {}
	reverse_iterator(const self& rhs):current(rhs.current){}

public:
	// 取出对应的正向迭代器
	iterator_type base() const  // 表示函数隐含传入的this指针为const指针，也就是说函数内部不能修改类的成员变量
	{
		return current;
	}
	// 重载操作符
	reference operator*() const  // 以引用的方式传出   
	{
		// 实际对应正向迭代器的前一个位置
		auto tmp = current;
		return *--tmp;
	}
	pointer operator->()const
	{
		return &(operator*());  // 对应用取地址，返回一个指针变量
	}

	// 前进(++)变为后退(--)  
	self& operator++()  // 前置++
	{
		--current;
		return *this;
	}

	self operator++(int) // 后置++
	{
		self tmp = *this;
		--current;
		return tmp;
	}

	// 后退(--)变为前进(++)
	self& operator--()
	{
		++current;
		return *this;
	}
	self operator--(int)
	{
		self tmp = *this;
		++current;
		return tmp;
	}

	self& operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}
	self operator+(difference_type n) const
	{
		return self(current - n);
	}
	self& operator-=(difference_type n)
	{
		current += n;
		return *this;
	}
	self operator-(difference_type n) const
	{
		return self(current + n);
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}
};

/******************************  操作符重载  ***************************************/

// 重载 operator-
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs,
		  const reverse_iterator<Iterator>& rhs)
{
	return rhs.base() - lhs.base();
}

// 重载比较操作符
template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() == rhs.base();
}

//重载 < 操作符
template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
	           const reverse_iterator<Iterator>& rhs)
{
	return rhs.base() < lhs.base();
}


template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return !(lhs == rhs);
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs)
{
	return rhs < lhs;
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
			    const reverse_iterator<Iterator>& rhs)
{
	return !(rhs < lhs);
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
			    const reverse_iterator<Iterator>& rhs)
{
	return !(lhs < rhs);
}

} // namespace mystl
#endif // !MYSTL_ITERATOR_H_
