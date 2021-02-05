// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <list>
#include <deque>

class CTest
{
public:
	CTest(int nValue) {
		m_nValue = nValue;
	}

	int& Value() {
		return m_nValue;
	}

private:
	int m_nValue;
};

int main()
{
	
	std::vector<int> dequeInt;
	int nCapacity = dequeInt.max_size();

	dequeInt.push_back(1);
	nCapacity = dequeInt.max_size();

	dequeInt.push_back(1);
	nCapacity = dequeInt.max_size();

// 	dequeInt.push_front(1);
// 	nCapacity = dequeInt.max_size();
// 
// 	dequeInt.push_front(1);
// 	nCapacity = dequeInt.max_size();

	return 0;
}


