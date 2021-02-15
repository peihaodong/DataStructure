#pragma once

//循环队列（先进先出）
template <typename T>
class PhdQueue
{
public:
	PhdQueue(int nCapacity = 10);	//构造函数
	~PhdQueue();					//析构函数

	const T& front() const;			//访问第一个元素
	T& front();
	const T& back() const;			//访问最后一个元素
	T& back();

	bool empty() const;				//检查底层的容器是否为空
	int size() const;				//返回容纳的元素数

	void push(const T& value);		//向队列尾部插入元素
	void pop();						//删除首个元素

private:
	bool IsFull() const;			//容量是否满了

private:
	T* m_pBuffer;			//
	int m_nSize;			//元素数量
	int m_nCapacity;		//队列容量
	int m_nHead;			//头索引
	int m_nTail;			//尾索引

};

//构造函数
template <typename T>
PhdQueue<T>::PhdQueue(int nCapacity /*= 10*/)
{
	m_nSize = 0;
	m_nCapacity = nCapacity;
	m_nHead = m_nTail = 0;
	m_pBuffer = new T[m_nCapacity];
}

//析构函数
template <typename T>
PhdQueue<T>::~PhdQueue()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
	m_nCapacity = m_nSize = m_nHead = m_nTail = 0;
}

//访问第一个元素
template <typename T>
const T& PhdQueue<T>::front() const
{
	assert(!empty());
	
	return m_pBuffer[m_nHead];
}

template <typename T>
T& PhdQueue<T>::front()
{
	assert(!empty());

	return m_pBuffer[m_nHead];
}

//访问最后一个元素
template <typename T>
const T& PhdQueue<T>::back() const
{
	assert(!empty());

	return m_pBuffer[m_nTail];
}

template <typename T>
T& PhdQueue<T>::back()
{
	assert(!empty());

	return m_pBuffer[m_nTail];
}

//检查底层的容器是否为空
template <typename T>
bool PhdQueue<T>::empty() const
{
	return m_nHead == m_nTail;
}

//返回容纳的元素数
template <typename T>
int PhdQueue<T>::size() const
{
	return m_nSize;
}

//向队列尾部插入元素
template <typename T>
void PhdQueue<T>::push(const T& value)
{
	if (IsFull())
		return;

	m_pBuffer[m_nTail] = value;
	m_nTail++;
	m_nSize++;
	if (m_nTail >= m_nCapacity)
		m_nTail = 0;
}

//删除首个元素
template <typename T>
void PhdQueue<T>::pop()
{
	if (empty())
	{
		return;
	}

	m_nHead++;
	m_nSize--;
	if (m_nHead >= m_nCapacity)
		m_nHead = 0;
}

//容量是否满了
template <typename T>
bool PhdQueue<T>::IsFull() const
{
	return (m_nTail + 1) % m_nCapacity == m_nHead;
}


