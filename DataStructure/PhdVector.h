#pragma once

//线性表顺序存储结构（动态数组）
template <typename T>
class PhdVector
{
public:
	//typedef unsigned int     size_t;
	//typedef size_t size_type;

	explicit PhdVector();	//构造函数
	PhdVector(const PhdVector<T>& obj);	//拷贝构造函数
	~PhdVector();						//析构函数
	
	//	重载 = 运算符
	PhdVector<T>& operator=(const PhdVector<T>& obj);
	//	重载 == 运算符
	bool operator==(const PhdVector<T>& obj);
	//	重载 != 运算符
	bool operator!=(const PhdVector<T>& obj);
	//	重载 [] 运算符
	T& operator[](int nPosIndex);
	const T& operator[](int nPosIndex) const;
	//	重载类型转换运算符
	operator T*();
	operator const T*();

	T& at(int nPosIndex);				//访问指定的元素，同时进行越界检查
	const T& at(int nPosIndex) const;
	T& front();						//访问第一个元素
	const T& front() const;			
	T& back();						//访问最后一个元素
	const T& back() const;
	T* data();						//返回指向内存中数组第一个元素的指针
	const T* data() const;

	bool empty() const;				//检查容器是否为空
	int size() const;				//获取元素数量
	int max_size() const;			//返回可容纳的最大元素数
	int capacity() const;			//获取数组大小（返回当前存储空间能够容纳的元素数）
	
	void resize(int nCount);		//改变容器中可存储元素的个数（既修改capacity大小，也修改size大小）
	void resize(int nCount,const T& value);
	void reserve(int nCapacity);	//预留存储空间（只修改capacity大小，不修改size大小）
	void shrink_to_fit();			//通过释放未使用的内存减少内存的使用

	void clear();					//清除所有元素
	void insert(int nPosIndex,const T& value);//插入元素（在指定位置之前）
	void erase(int nPosIndex);		//擦除元素
	void push_back(const T& value);	//将元素添加到容器末尾
	void pop_back();				//移除末尾元素
	void swap(PhdVector<T>& obj);	//交换元素

private:
	T* m_pList;			//T类型指针，用于存放动态分配的数组内存首地址
	int m_nCapacity;	//数组容量
	int m_nSize;		//元素数量
};

//	构造函数
template <typename T>
PhdVector<T>::PhdVector()
	:m_pList(nullptr)
	, m_nCapacity(0)
	,m_nSize(0)
{
	m_pList = new T[m_nCapacity];		//创建该大小的内存
	assert(m_pList)
	std::memset(m_pList,0, m_nCapacity);	//初始化该内存为0
}

//	拷贝构造函数
template <typename T>
PhdVector<T>::PhdVector(const PhdVector<T>& obj)
{
	m_nCapacity = obj.m_nCapacity;
	m_nSize = obj.m_nSize;
	m_pList = new T[m_nCapacity];
	assert(m_pList);
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
	m_nSize = 0;
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
		}
		//拷贝内存上的值
		std::memcpy(this->m_pList,obj.m_pList,this->m_nCapacity);

		if (this->m_nSize != obj.m_nSize)
			this->m_nSize = obj.m_nSize;
	}

	return *this;
}

//	重载 == 运算符
template <typename T>
bool PhdVector<T>::operator==(const PhdVector<T>& obj)
{
	if (this->m_nSize != obj.m_nSize)
		return false;

	//判断内容是否相等
	for (int i = 0; i < this->m_nSize; ++i)
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
T& PhdVector<T>::operator[](int nPosIndex)
{
	//检查数组下标是否越界
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
}

//	重载 [] 运算符（返回元素const+引用）
template <typename T>
const T& PhdVector<T>::operator[](int nPosIndex) const
{
	//检查数组下标是否越界
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
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

//访问指定的元素，同时进行越界检查
template <typename T>
T& PhdVector<T>::at(int nPosIndex)
{
	//检查数组下标是否越界
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
}

template <typename T>
const T& PhdVector<T>::at(int nPosIndex) const
{
	//检查数组下标是否越界
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
}

//访问第一个元素
template <typename T>
T& PhdVector<T>::front()
{
	assert(m_nSize);
	return m_pList[0];
}

template <typename T>
const T& PhdVector<T>::front() const
{
	assert(m_nSize);
	return m_pList[0];
}

//访问最后一个元素
template <typename T>
T& PhdVector<T>::back()
{
	assert(m_nSize);
	return m_pList[m_nSize-1];
}

template <typename T>
const T& PhdVector<T>::back() const
{
	assert(m_nSize);
	return m_pList[m_nSize-1];
}

//返回指向内存中数组第一个元素的指针
template <typename T>
T* PhdVector<T>::data()
{
	return m_pList;
}

template <typename T>
const T* PhdVector<T>::data() const
{
	return m_pList;
}

//检查容器是否为空
template <typename T>
bool PhdVector<T>::empty() const
{
	return m_nSize;
}

//	获取元素数量
template <typename T>
int PhdVector<T>::size() const
{
	return m_nSize;
}

//返回可容纳的最大元素数
template <typename T>
int PhdVector<T>::max_size() const 
{
	return INT_MAX;
	return int(((unsigned int)(~0)) >> 1);//最大值就是符号位为0，其他位都为1的整数
	//~0把所有位变为1，转换乘无符号数，确保右移是逻辑右移（还是其他名字？:)），
	//也就是高位会因为右移空出个0，这样就作出一个最高位（符号位）为0其他位都为1的整数了
}

//	获取数组大小
template <typename T>
int PhdVector<T>::capacity() const {
	return m_nCapacity;
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
		assert(pNewList);
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

template <typename T>
void PhdVector<T>::resize(int nCount,const T& value)
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
				m_pList[i] = value;
			}
			m_nSize = nCount;
		}
	}
	else
	{//不够
		T* pNewList = new T[nCount];
		assert(pNewList);
		std::memset(pNewList, 0, nCount);

		for (int i = 0; i < nCount; ++i)
		{
			if (i < m_nSize)
			{
				pNewList[i] = m_pList[i];
			}
			else
			{
				m_pList[i] = value;
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
	//增加 vector 的容量到大于或等于 nCapacity 的值。
	//若 nCapacity 大于当前的 capacity() ，则分配新存储，否则该方法不做任何事。
	if (nCapacity <= m_nCapacity)
		return;

	T* pNewList = new T[nCapacity];
	assert(pNewList);
	std::memset(pNewList, 0, nCapacity);
	std::memcpy(pNewList,m_pList,m_nSize);

	delete[] m_pList;
	m_pList = pNewList;
	m_nCapacity = nCapacity;
}

//通过释放未使用的内存减少内存的使用
template <typename T>
void PhdVector<T>::shrink_to_fit()
{
	if (m_nSize == m_nCapacity)
		return;

	T* pNewList = new T[m_nSize];
	assert(pNewList);
	std::memcpy(pNewList, m_pList, m_nSize);

	delete[] m_pList;
	m_pList = pNewList;
	m_nCapacity = m_nSize;
}

//清除所有元素
template <typename T>
void PhdVector<T>::clear()
{
	m_nSize = 0;
}

//插入元素（在指定位置之前）
template <typename T>
void PhdVector<T>::insert(int nPosIndex, const T& value)
{
	//容量是否够用
	if ((m_nSize + 1) > m_nCapacity)
	{//不够
		m_nCapacity *= 2;
		T* pNewList = new T[m_nCapacity];
		assert(pNewList);
		std::memset(pNewList,0,m_nCapacity);

		//是否添加到尾部
		if (nPosIndex >= m_nSize)
		{
			std::memcpy(pNewList, m_pList, m_nSize);
			pNewList[m_nSize] = value;

			delete[] m_pList;
			m_pList = pNewList;
			m_nSize++;
		}
		else
		{
			int nFrontSize = nPosIndex;
			T* pFrontList = new T[nFrontSize];
			assert(pBackList);
			std::memcpy(pFrontList, m_pList, nFrontSize);

			int nBackSize = m_nSize - nPosIndex;
			T* pBackList = new T[nBackSize];
			assert(pBackList);
			std::memcpy(pBackList, m_pList + nPosIndex, nBackSize);

			std::memcpy(pNewList, pFrontList, nFrontSize);
			pNewList[m_nSize] = value;
			std::memcpy(pNewList + nPosIndex + 1, pBackList, nBackSize);

			delete[] pFrontList;
			delete[] pBackList;
			delete[] m_pList;
			m_pList = pNewList;
			m_nSize++;
		}
	}
	else
	{//够
		//是否添加到尾部
		if (nPosIndex >= m_nSize)
		{
			m_pList[m_nSize] = value;
			m_nSize++;
		}
		else
		{
			int nBackSize = m_nSize - nPosIndex;
			T* pBackList = new T[nBackSize];
			assert(pBackList);
			std::memcpy(pBackList, m_pList + nPosIndex, nBackSize);

			m_pList[nPosIndex] = value;
			std::memcpy(m_pList + nPosIndex + 1, pBackList, nBackSize);

			delete[] pBackList;
			m_nSize++;
		}
	}
}

//擦除元素
template <typename T>
void PhdVector<T>::erase(int nPosIndex)
{
	if (m_nSize == 0)
		return;

	//是否删除尾部元素
	if (nPosIndex >= m_nSize)
	{
		m_nSize--;
	}
	else
	{
		int nBackSize = m_nSize - nPosIndex - 1;
		T* pBackList = new T[nBackSize];
		assert(pBackList);
		std::memcpy(pBackList, m_pList + nPosIndex + 1, nBackSize);
		std::memcpy(m_pList + nPosIndex, pBackList, nBackSize);

		delete[] pBackList;
		m_nSize--;
	}
}

//将元素添加到容器末尾
template <typename T>
void PhdVector<T>::push_back(const T& value)
{
	//容量是否够用
	if ((m_nSize + 1) > m_nCapacity)
	{//不够
		m_nCapacity *= 2;
		T* pNewList = new T[m_nCapacity];
		assert(pNewList);
		std::memset(pNewList, 0, m_nCapacity);

		std::memcpy(pNewList, m_pList, m_nSize);
		pNewList[m_nSize] = value;

		delete[] m_pList;
		m_pList = pNewList;
		m_nSize++;
	}
	else
	{//够
		m_pList[m_nSize] = value;
		m_nSize++;
	}
}

//移除末尾元素
template <typename T>
void PhdVector<T>::pop_back()
{
	m_nSize--;
}

//交换元素
template <typename T>
void PhdVector<T>::swap(PhdVector<T>& obj)
{
	T* pListTemp = this->m_pList;
	int nCapacityTemp = this->m_nCapacity;
	int nSizeTemp = this->m_nSize;

	this->m_pList = obj.m_pList;
	this->m_nCapacity = obj.m_nCapacity;
	this->m_nSize = obj.m_nSize;

	obj.m_pList = pListTemp;
	obj.m_nCapacity = nCapacityTemp;
	obj.m_nSize = nSizeTemp;
}