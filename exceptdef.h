#ifndef MYSTL_EXCEPTDEF_H_
#define MYSTL_EXCEPTDEF_H_

#include <stdexcept>
#include <cassert>

/*
assert() 会对表达式expression进行检测：
如果expression的结果为 0（条件不成立），那么断言失败，表明程序出错，assert() 会向标准输出设备（一般是显示器）打印一条错误信息，并调用 abort() 函数终止程序的执行。
如果expression的结果为非 0（条件成立），那么断言成功，表明程序正确，assert() 不进行任何操作。
*/
namespace mystl
{

#define MYSTL_DEBUG(expr) \
	assert(expr)
#define THROW_LENGTH_ERROR_IF(expr,what) \
	if((expr)) throw std::length_error(what)  //抛出异常,但不处理

#define THROW_OUT_OF_RANGE_IF(expr, what) \
	if((expr)) throw std::out_of_range(what)

#define THROW_RUNTIME_ERROR_IF(expr, what) \
  if ((expr)) throw std::runtime_error(what)

}// namespace mystl


#endif // !MYSTL_EXCEPTDEF_H_

