// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

int main()
{
	int* pArr1 = new int[10];
	int* pArr2 = new int[5];
	std::memset(pArr1,0,10);
	std::memset(pArr2, 0, 5);
	pArr1[0] = 1;
	pArr1[0] = 2;
	pArr1[0] = 3;
	pArr1[0] = 4;

	std::memcpy(pArr2,pArr1,5);

	return 0;
}


