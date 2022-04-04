#ifndef MYSTL_VECTOR_TEST_H_
#define MYSTL_VECTOR_TEST_H_

// vector test : 测试vector 的接口与push_back的性能
#include<vector>
#include "vector.h"
#include "test.h"


namespace mystl
{
namespace test
{
namespace vector_test
{
void vector_test()
{
	std::cout << "[===============================================================]\n";
	std::cout << "[----------------- Run container test : vector -----------------]\n";
	std::cout << "[-------------------------- API test ---------------------------]\n";

	int a[] = { 1,2,3,4,5 };
	mystl::vector<int> v1;
	mystl::vector<int> v2(10);
	mystl::vector<int> v3(10, 1);
	mystl::vector<int> v4(a, a + 5);
	mystl::vector<int> v5(v2);
	mystl::vector<int> v6(std::move(v2));
	mystl::vector<int> v7{ 1,2,3,4,5,6,7,8,9 };
	mystl::vector<int> v8, v9, v10;
	v8 = v3;
	v9 = std::move(v3);
	v10 = { 1,2,3,4,5,6,7,8,9 };
	
	// 宏函数----- 输出容器调用函数后的结果
	FUN_AFTER(v1, v1.assign(8, 8));  
	FUN_AFTER(v1, v1.assign(a, a + 5));
	FUN_AFTER(v1, v1.emplace(v1.begin(), 0));
	FUN_AFTER(v1, v1.emplace_back(6));
	FUN_AFTER(v1, v1.push_back(6));
	FUN_AFTER(v1, v1.insert(v1.end(), 7));
	FUN_AFTER(v1, v1.insert(v1.begin() + 3, 2, 3));
	FUN_AFTER(v1, v1.insert(v1.begin(), a, a + 5));
	FUN_AFTER(v1, v1.pop_back());
	FUN_AFTER(v1, v1.erase(v1.begin()));
	FUN_AFTER(v1, v1.erase(v1.begin(), v1.begin() + 2));
	FUN_AFTER(v1, v1.reverse());
	FUN_AFTER(v1, v1.swap(v4));

	int* p = v1.data();  // 返回容器的begin()
	*p = 10;
	*++p = 20;
	p[1] = 30;
	std::cout << " After change v1.data() :" << "\n";
	// 宏函数遍历容器并输出
	COUT(v1);
	std::cout << std::boolalpha;  // 使bool变量以true false的格式输出
	FUN_VALUE(v1.empty());
	std::cout << std::noboolalpha;
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.max_size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.resize(10));
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.shrink_to_fit());
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.resize(6, 6));
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.shrink_to_fit());
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.clear());
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.reserve(5));
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.reserve(20));
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	FUN_AFTER(v1, v1.shrink_to_fit());
	FUN_VALUE(v1.size());
	FUN_VALUE(v1.capacity());
	PASSED;

#if PERFORMANCE_TEST_ON
	std::cout << "[--------------------- Performance Testing ---------------------]\n";
	std::cout << "|---------------------|-------------|-------------|-------------|\n";
	std::cout << "|      push_back      |";
#if LARGER_TEST_DATA_ON
	CON_TEST_P1(vector<int>, push_back, rand(), LEN1 _LL, LEN2 _LL, LEN3 _LL);
#else
	CON_TEST_P1(vector<int>, push_back, rand(), LEN1 _L, LEN2 _L, LEN3 _L);
#endif
	std::cout << "\n";
	std::cout << "|---------------------|-------------|-------------|-------------|\n";
	PASSED;
#endif
	std::cout << "[----------------- End container test : vector -----------------]\n";
}

}// namespace vector_test
}// namespace TEST
}// namespace MYSTL


#endif // !MYSTL_VECTOR_TEST_H_
