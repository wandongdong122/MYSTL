//#ifdef _MSC_VER
//#define _SCL_SECURE_NO_WARNINGS  //如果调用 c + + 标准库中任何可能不安全的方法，将导致 编译器警告 (级别 3) C4996。 若要禁用此警告，可在代码中将宏定义为 _SCL_SECURE_NO_WARNINGS：
//#endif
//
//#if defined(_MSC_VER) && defined(_DEBUG)// 如果使用DEBUG就会执行下面的内容
//#define _CRTDBG_MAP_ALLOC   // 启动windows中的内存泄露检测工具
//#include <stdlib.h>
//#include <crtdbg.h>
//#endif // check memory leaks
//
//#include "vector_test.h"
////#include "list_test.h"
////#include "deque_test.h"
////#include "stack_test.h"
////#include "string_test.h"
//int main()
//{
//	using namespace mystl::test;
//
//
//	std::cout.sync_with_stdio(false); 
//	//因为C++中，cin和cout要与stdio同步，中间会有一个缓冲，所以导致cin，cout语句输入输出缓慢，
//	//这时就可以用这个语句，取消cin，cout与stdio的同步，说白了就是提速，效率基本与scanf和printf一致。
//	RUN_ALL_TESTS();
//
//
//	vector_test::vector_test();
//	//string_test::string_test();
//	//deque_test::deque_test();
//	//list_test::list_test();
//	//stack_test::stack_test();
//	//map_test::map_test();
//
//
//#if defined(_MSC_VER) && defined(_DEBUG)
//	_CrtDumpMemoryLeaks(); //发生内存泄漏时，转储调试堆中的所有内存块（仅限调试版本）。
//#endif // check memory leaks
//}

//#ifdef _MSC_VER
//#define _SCL_SECURE_NO_WARNINGS
//#endif
//
//#if defined(_MSC_VER) && defined(_DEBUG)
//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h>
//#include <crtdbg.h>
//#endif // check memory leaks
//
//#include "vector_test.h"
//
//int main()
//{
//	using namespace mystl::test;
//
//	std::cout.sync_with_stdio(false);
//
//	RUN_ALL_TESTS();
//
//	vector_test::vector_test();
//
//#if defined(_MSC_VER) && defined(_DEBUG)
//	_CrtDumpMemoryLeaks();
//#endif // check memory leaks
//}