#ifndef MYSTL_EXCEPTDEF_H_
#define MYSTL_EXCEPTDEF_H_

#include <stdexcept>
#include <cassert>

/*
assert() ��Ա��ʽexpression���м�⣺
���expression�Ľ��Ϊ 0������������������ô����ʧ�ܣ������������assert() �����׼����豸��һ������ʾ������ӡһ��������Ϣ�������� abort() ������ֹ�����ִ�С�
���expression�Ľ��Ϊ�� 0����������������ô���Գɹ�������������ȷ��assert() �������κβ�����
*/
namespace mystl
{

#define MYSTL_DEBUG(expr) \
	assert(expr)
#define THROW_LENGTH_ERROR_IF(expr,what) \
	if((expr)) throw std::length_error(what)  //�׳��쳣,��������

#define THROW_OUT_OF_RANGE_IF(expr, what) \
	if((expr)) throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what) \
  if ((expr)) throw std::runtime_error(what)

}// namespace mystl


#endif // !MYSTL_EXCEPTDEF_H_

