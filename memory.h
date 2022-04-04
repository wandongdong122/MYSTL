#ifndef MYSTL_MEMORY_H_
#define MYSTL_MEMORY_H_

// ���ͷ�ļ�������߼��Ķ�̬�ڴ����
// ����һЩ�����������ռ���������δ��ʼ���Ĵ���ռ�������Լ�һ��ģ���� auto_ptr

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"

namespace mystl
{
// ��ȡ�����ַ
template <class Tp>
constexpr Tp* address_of(Tp& value) noexcept/*�������쳣*/
{
/*��������ʽ���������������ĺ������У����˿��԰��� using ָ�typedef ����Լ� static_assert �����⣬ֻ�ܰ���һ�� return ������䡣*/
/*constexpr �ؼ��ֵĹ�����ʹָ���ĳ�������ʽ����ڳ������׶μ��������������������صȵ��������н׶�*/
	return &value;
}

// ��ȡ  / �ͷ� ��ʱ������
template <class T>
pair<T*, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T*) // ��Ҫ��ȡ��ʱ�������Ĵ�С������
{
    if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
        len = INT_MAX / sizeof(T);
    while (len > 0)
    {
        T* tmp = static_cast<T*>(malloc(static_cast<size_t>(len) * sizeof(T)));
        if (tmp)
            return pair<T*, ptrdiff_t>(tmp, len);
        len /= 2;  // ����ʧ��ʱ���� len �Ĵ�С
    }
    return pair<T*, ptrdiff_t>(nullptr, 0); // ����ʧ��
}

template <class T>
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) 
{
    return get_buffer_helper(len, static_cast<T*>(0));
}

template <class T>
pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T*)
{
    return get_buffer_helper(len, static_cast<T*>(0));
}

template <class T>
void release_temporary_buffer(T* ptr)
{
    free(ptr);
}

// --------------------------------------------------------------------------------------
// ��ģ�� : temporary_buffer
// ������ʱ���������������ͷ�
template <class FrowardIterator, class T>
class temporary_buffer
{
private:
    ptrdiff_t original_len;  // ����������Ĵ�С
    ptrdiff_t len;           // ������ʵ�ʵĴ�С
    T*        buffer;        // ָ�򻺳�����ָ��

public:
    // ���졢��������
    temporary_buffer(FrowardIterator first, FrowardIterator last);

    ~temporary_buffer()
    {
        mystl::destroy(buffer, buffer + len);
        free(buffer);
    }
public:

    ptrdiff_t size()           const noexcept { return len; }
    ptrdiff_t requested_size() const noexcept { return original_len; }
    T*        begin()                noexcept { return buffer; }
    T*        end()                  noexcept { return buffer + len; }

private:
    void allocate_buffer();
    void initialize_buffer(const T&,std::true_type){}
    void initialize_buffer(const T& value,std::false_type)
    {mystl::uninitialized_fill_n(buffer, len, value);}

private:
    temporary_buffer(const temporary_buffer&);
    void operator=(const temporary_buffer&);
};
// ���캯��
template <class ForwardIterator, class T>
temporary_buffer<ForwardIterator, T>::
temporary_buffer(ForwardIterator first, ForwardIterator last)
{
    try
    {
        len = mystl::distance(first, last);
        allocate_buffer();
        if (len > 0)
        {
            initialize_buffer(*first, std::is_trivially_default_constructible<T>());
        }
    }
    catch (...)
    {
        free(buffer);
        buffer = nullptr;
        len = 0;
    }
}
// allocate_buffer ����
template <class ForwardIterator, class T>
void temporary_buffer<ForwardIterator, T>::allocate_buffer()
{
    original_len = len;
    if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
        len = INT_MAX / sizeof(T);
    while (len > 0)
    {
        buffer = static_cast<T*>(malloc(len * sizeof(T)));
        if (buffer)
            break;
        len /= 2;  // ����ʧ��ʱ��������ռ��С
    }
}

// --------------------------------------------------------------------------------------
// ģ����: auto_ptr
// һ�������ϸ��������Ȩ��С������ָ��
template <class T>
class auto_ptr
{
public:
    typedef T    elem_type;

private:
    T* m_ptr;  // ʵ��ָ��

public:
    // ���졢���ơ���������
    explicit auto_ptr(T* p = nullptr) :m_ptr(p) {}
    auto_ptr(auto_ptr& rhs) :m_ptr(rhs.release()) {}
    template <class U>
    auto_ptr(auto_ptr<U>& rhs) : m_ptr(rhs.release()) {}

    auto_ptr& operator=(auto_ptr& rhs)
    {
        if (this != &rhs)
        {
            delete m_ptr;
            m_ptr = rhs.release();
        }
        return *this;
    }
    template <class U>
    auto_ptr& operator=(auto_ptr<U>& rhs)
    {
        if (this->get() != rhs.get())
        {
            delete m_ptr;
            m_ptr = rhs.release();
        }
        return *this;
    }

    ~auto_ptr() { delete m_ptr; }

public:
    // ���� operator* �� operator->
    T& operator*()  const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

    // ���ָ��
    T* get() const { return m_ptr; }

    // �ͷ�ָ��
    T* release()
    {
        T* tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

    // ����ָ��
    void reset(T* p = nullptr)
    {
        if (m_ptr != p)
        {
            delete m_ptr;
            m_ptr = p;
        }
    }
};

} // namespace mystl
#endif // !MYSTL_MEMORY_H_
