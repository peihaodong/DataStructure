#pragma once

//栈（先进后出）
template <typename T>
class PhdStack
{
public:
	PhdStack();					//构造函数
	~PhdStack();				//析构函数

	const T& top() const;		//返回栈顶元素
	T& top();

	bool empty() const;			//检查底层的容器是否为空
	int size() const;			//返回容纳的元素数

	void push(const T& value);	//向栈顶插入元素
	void pop();					//删除栈顶元素

private:
	T* m_pBuffer;			//栈空间指针
	int m_nCapacity;		//数组容量
	int m_nSize;			//元素数量（栈顶坐标）
};

//构造函数
template <typename T>
PhdStack<T>::PhdStack()
	:m_pBuffer(nullptr)
	,m_nSize(0)
	, m_nCapacity(1)
{
	m_pBuffer = new T[m_nCapacity];
	assert(m_pBuffer);
}

//析构函数
template <typename T>
PhdStack<T>::~PhdStack<T>()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
	m_nSize = 0;
}

//返回栈顶元素
template <typename T>
const T& PhdStack<T>::top() const
{
	assert(m_nSize);

	return m_pBuffer[m_nSize-1];
}

template <typename T>
T& PhdStack<T>::top()
{
	assert(m_nSize);

	return m_pBuffer[m_nSize-1];
}

//检查底层的容器是否为空
template <typename T>
bool PhdStack<T>::empty() const
{
	if (m_nSize)
		return true;
	else
		return false;
}

//返回容纳的元素数
template <typename T>
int PhdStack<T>::size() const 
{
	return m_nSize;
}

//向栈顶插入元素
template <typename T>
void PhdStack<T>::push(const T& value)
{
	if (m_nSize >= m_nCapacity)
	{
		m_nCapacity *= 2;
		T* pNewBuffer = new T[m_nCapacity];
		assert(pNewBuffer);
		std::memset(pNewBuffer, 0, m_nCapacity);

		std::memcpy(pNewBuffer, m_pBuffer, m_nSize);
		pNewBuffer[m_nSize] = value;

		delete[] m_pBuffer;
		m_pBuffer = pNewBuffer;
		m_nSize++;
	}
	else
	{
		m_pBuffer[m_nSize] = value;
		m_nSize++;
	}
}

//删除栈顶元素
template <typename T>
void PhdStack<T>::pop()
{
	m_nSize--;
}
