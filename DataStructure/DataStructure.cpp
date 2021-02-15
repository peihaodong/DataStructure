// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <list>
#include <deque>



int main()
{
	std::list<int> listInt;
	listInt.push_back(1);
	listInt.push_back(2);
	std::list<int> listInt2 = listInt;
	auto a = listInt2.size();
	std::cout << a << std::endl;

	return 0;
}


