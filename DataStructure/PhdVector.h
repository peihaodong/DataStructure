#pragma once

//线性表顺序存储结构（动态数组）
template <typename T>
class PhdVector
{
public:
	explicit PhdVector(int nSize = 50);	//构造函数
	PhdVector(const PhdVector<T>& obj);	//拷贝构造函数
	~PhdVector();						//析构函数
	
	//	重载 = 运算符
	PhdVector<T>& operator=(const PhdVector<T>& obj);
	//	重载 == 运算符
	bool operator==(const PhdVector<T>& obj);
	//	重载 != 运算符
	bool operator!=(const PhdVector<T>& obj);
	//	重载 [] 运算符
	T& operator[](int nIndex);
	const T& operator[](int nIndex) const;
	//	重载类型转换运算符
	operator T*();
	operator const T*();

	int capacity() const;			//获取数组大小（返回当前存储空间能够容纳的元素数）
	int size() const;				//获取元素数量

	void resize(int nCount);		//改变容器中可存储元素的个数（既修改capacity大小，也修改size大小）
	void reserve(int nCapacity);	//预留存储空间（只修改capacity大小，不修改size大小）

// 	void push_back(const T& value);	//将元素添加到容器末尾
// 	void pop_back();				//移除末尾元素

private:
	T* m_pList;			//T类型指针，用于存放动态分配的数组内存首地址
	int m_nCapacity;	//数组容量
	int m_nSize;		//元素数量
};

//	构造函数
template <typename T>
PhdVector<T>::PhdVector(int nSize /*= 50*/)
	:m_pList(nullptr)
	, m_nCapacity(0)
	,m_nSize(0)
{
	assert(nSize >= 0);
	m_nCapacity = nSize;
	m_pList = new T[m_nCapacity];		//创建该大小的内存
	assert(m_pList)
	std::memset(m_pList,0, m_nCapacity);	//初始化该内存为0
}

//	拷贝构造函数
template <typename T>
PhdVector<T>::PhdVector(const PhdVector<T>& obj)
{
	m_nCapacity = obj.m_nCapacity;
	m_pList = new T[m_nCapacity];
	if (m_pList == nullptr)
	{
		std::cout << "alloc err!" << std::endl;
		std::exit(-1);
	}
	//拷贝该内存的值
// 	for (int i = 0; i < m_nCapacity; ++i)
// 	{
// 		m_pList[i] = obj.m_pList[i];
// 	}
	std::memcpy(m_pList,obj.m_pList,m_nCapacity);
}

//	析构函数
template <typename T>
PhdVector<T>::~PhdVector()
{
	delete[] m_pList;
	m_pList = nullptr;
	m_nCapacity = 0;
}

//	重载 = 运算符
template <typename T>
PhdVector<T>& PhdVector<T>::operator=(const PhdVector<T>& obj)
{
	if (this != &obj)
	{
		//如果本对象中数组大小与obj不同，则释放数组原有内存，重新分配
		if (this->m_nCapacity != obj.m_nCapacity)
		{
			delete[] this->m_pList;
			this->m_pList = nullptr;
			this->m_nCapacity = obj.m_nCapacity;
			this->m_pList = new T[this->m_nCapacity];
			assert(m_pList);
			//std::memset(this->m_pList,0,m_nCapacity);
		}
		//拷贝内存上的值
// 		for (int i = 0; i < this->m_nCapacity; ++i)
// 		{
// 			this->m_pList[i] = obj.m_pList[i];
// 		}
		std::memcpy(this->m_pList,obj.m_pList,this->m_nCapacity);
	}

	return *this;
}

//	重载 == 运算符
template <typename T>
bool PhdVector<T>::operator==(const PhdVector<T>& obj)
{
	if (this->m_nCapacity != obj.m_nCapacity)
		return false;

	//判断内容是否相等
	for (int i = 0; i < this->m_nCapacity; ++i)
	{
		if (this->m_pList[i] != obj.m_pList[i])
			return false;
	}

	return true;
}

//	重载 != 运算符
template <typename T>
bool PhdVector<T>::operator!=(const PhdVector<T>& obj)
{
	return !(*this == obj);
}

//	重载 [] 运算符（返回元素引用）
template <typename T>
T& PhdVector<T>::operator[](int nIndex)
{
	//检查数组下标是否越界
	assert(nIndex >= 0 && nIndex < m_nCapacity);
	return m_pList[nIndex];
}

//	重载 [] 运算符（返回元素const+引用）
template <typename T>
const T& PhdVector<T>::operator[](int nIndex) const
{
	//检查数组下标是否越界
	assert(nIndex >= 0 && nIndex < m_nCapacity);
	return m_pList[nIndex];
}

//	重载类型转换运算符（转换为指针）
template <typename T>
PhdVector<T>::operator T*()
{
	return m_pList;// 返回当前对象中私有数组的首地址
}

//	重载类型转换运算符（转换为const指针）
template <typename T>
PhdVector<T>::operator const T*()
{
	return m_pList;// 返回当前对象中私有数组的首地址
}

//	获取数组大小
template <typename T>
int PhdVector<T>::capacity() const {
	return m_nCapacity;
}

//	获取元素数量
template <typename T>
int PhdVector<T>::size() const
{
	return m_nSize;
}

//	改变容器中可存储元素的个数
template <typename T>
void PhdVector<T>::resize(int nCount)
{
	//重设容器大小以容纳 nCount 个元素。
	//若当前元素数量大于 nCount ，则减小数量为 nCount 个元素。
	//若当前元素数量小于 nCount ，增加元素数量为 nCount 个元素。

	if (m_nSize == nCount)
		return;

	//判断当前容量够不够
	if (m_nCapacity >= nCount)
	{//够
		if (nCount > m_nSize)
		{
			for (int i = m_nSize; i < nCount; ++i)
			{
				T t;
				m_pList[i] = t;
			}
			m_nSize = nCount;
		}
	}
	else
	{//不够
		T* pNewList = new T[nCount];
		if (pNewList == nullptr)
		{
			std::cout << "alloc err!" << std::endl;
			std::exit(-1);
		}
		std::memset(pNewList, 0, nCount);
		
		for (int i = 0; i < nCount; ++i)
		{
			if (i < m_nSize)
			{
				pNewList[i] = m_pList[i];
			}
			else
			{
				T t;
				m_pList[i] = t;
			}
		}
		delete[] m_pList;
		m_pList = pNewList;
		m_nCapacity = nCount;
		m_nSize = nCount;
	}
}

//	预留存储空间
template <typename T>
void PhdVector<T>::reserve(int nCapacity)
{
	//增加 vector 的容量到大于或等于 nSize 的值。
	//若 nSize 大于当前的 capacity() ，则分配新存储，否则该方法不做任何事。
	if (nCapacity <= m_nCapacity)
		return;

	T* pNewList = new T[nCapacity];
	assert(pNewList);
	std::memset(pNewList, 0, nCapacity);

	for (int i = 0; i < nCapacity; ++i)
	{
		pNewList[i] = m_pList[i];
	}
	delete[] m_pList;
	m_pList = pNewList;
	m_nCapacity = nCapacity;
}