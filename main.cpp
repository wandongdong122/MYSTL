//#ifdef _MSC_VER
//#define _SCL_SECURE_NO_WARNINGS  //������� c + + ��׼�����κο��ܲ���ȫ�ķ����������� ���������� (���� 3) C4996�� ��Ҫ���ô˾��棬���ڴ����н��궨��Ϊ _SCL_SECURE_NO_WARNINGS��
//#endif
//
//#if defined(_MSC_VER) && defined(_DEBUG)// ���ʹ��DEBUG�ͻ�ִ�����������
//#define _CRTDBG_MAP_ALLOC   // ����windows�е��ڴ�й¶��⹤��
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
//	//��ΪC++�У�cin��coutҪ��stdioͬ�����м����һ�����壬���Ե���cin��cout����������������
//	//��ʱ�Ϳ����������䣬ȡ��cin��cout��stdio��ͬ����˵���˾������٣�Ч�ʻ�����scanf��printfһ�¡�
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
//	_CrtDumpMemoryLeaks(); //�����ڴ�й©ʱ��ת�����Զ��е������ڴ�飨���޵��԰汾����
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