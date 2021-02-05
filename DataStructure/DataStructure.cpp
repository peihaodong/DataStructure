// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <assert.h>

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
	std::vector<int> vecInt1, vecInt2;
	vecInt1.push_back(1);
	vecInt1.push_back(2);
	vecInt2.push_back(1);
	vecInt2.push_back(2);
	vecInt2.push_back(3);
	vecInt2.push_back(4);

	int nCapacity1 = vecInt1.capacity();
	int nCapacity2 = vecInt2.capacity();
	auto a1 = vecInt1.data();
	auto a2 = vecInt2.data();

	vecInt1.swap(vecInt2);

	nCapacity1 = vecInt1.capacity();
	nCapacity2 = vecInt2.capacity();
	a1 = vecInt1.data();
	a2 = vecInt2.data();

	return 0;
}


