#pragma once

//线性表顺序存储结构（双向链表）

template <typename T>
class PhdList
{
private:
	//结点类
	class PhdNode
	{
	public:
		//构造函数
		PhdNode(const T& data)
			:m_data(data)
			, m_pFront(nullptr)
			, m_pNext(nullptr)
		{}

		//析构函数
		~PhdNode()
		{
			m_pFront = nullptr;
			m_pNext = nullptr;
		}

		//获取节点数据
		T GetData() const {
			return m_data;
		}

	public:
		T m_data;				//数据域
		PhdNode<T> *m_pFront;	//指针域（指向前一节点）
		PhdNode<T> *m_pNext;	//指针域（指向后一节点）
	};

public:
	PhdList();					//构造函数
	~PhdList();					//析构函数

	//	重载 = 运算符
	PhdList<T>& operator=(const PhdList<T>& obj);

	void push_back(const T& value);		//将元素添加到容器末尾
	void push_front(const T& value);	//插入元素到容器起始
	void pop_front();					//移除首元素
	void pop_back();					//移除末元素
	const T& front() const;				//访问第一个元素
	T& front();
	const T& back() const;				//访问最后一个元素
	T& back();
	bool empty() const;					//判断链表是否为空
	int size() const;					//返回元素数
	void clear();						//清空链表，释放内存
	void insert(int nPosIndex,const T& value);//插入元素
	

private:
	PhdNode<T>* m_pHead;		//头结点指针
	PhdNode<T>* m_pTail;		//尾节点指针
	int m_nLength;				//链表长度
};

//构造函数
template <typename T>
PhdList<T>::PhdList()
	:m_nLength(0)
	,m_pHead(nullptr)
	,m_pTail(nullptr)
{

}

//析构函数
template <typename T>
PhdList<T>::~PhdList()
{
	clear();
}

//	重载 = 运算符
template <typename T>
PhdList<T>& PhdList<T>::operator=(const PhdList<T>& obj)
{
	if (this != &obj)
	{
		clear();

		this->m_nLength = obj.m_nLength;
		auto iter = obj.m_pHead;
		if (m_nLength == 0)
		{
			return;
		}
		else if (m_nLength == 1)
		{
			PhdNode<T>* pNewNode = new PhdNode<T>(iter->m_data);
			this->m_pHead = pNewNode;
			this->m_pTail = pNewNode;
		}
		else
		{
			for (int i = 0; i < m_nLength; i++)
			{
				PhdNode<T>* pNewNode = new PhdNode<T>(iter->m_data);
				if (i == 0)
				{
					this->m_pHead = pNewNode;
					this->m_pTail = pNewNode;
				}
				else
				{
					this->m_pTail->m_pNext = pNewNode;
					pNewNode->m_pFront = this->m_pTail;
					this->m_pTail = pNewNode;
				}
			}
		}
	}

	return *this;
}

//将元素添加到容器末尾
template <typename T>
void PhdList<T>::push_back(const T& value)
{
	PhdNode<T>* pNewNode = new PhdNode<T>(value);

	if (empty() == true)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		m_pTail->m_pNext = pNewNode;
		pNewNode->m_pFront = m_pTail;
		m_pTail = pNewNode;
	}
	m_nLength++;  //链表长度增加1
}

//插入元素到容器起始
template <typename T>
void PhdList<T>::push_front(const T& value)
{
	PhdNode<T>* pNewNode = new PhdNode<T>(value);

	if (empty() == true)
	{
		m_pTail = pNewNode;
		m_pHead = pNewNode;
	}
	else
	{
		m_pHead->m_pFront = pNewNode;
		pNewNode->m_pNext = m_pHead;
		m_pHead = pNewNode;
	}
	m_nLength++; //链表长度增加1
}

//移除首元素
template <typename T>
void PhdList<T>::pop_front()
{
	if (empty())
		return;
	else
	{
		if (m_pHead == m_pTail)            //头结点和尾结点为同一结点的情况
		{
			delete m_pHead;
			m_pHead = nullptr;
			m_pTail = nullptr;
			m_nLength--;                //链表长度减1
			return;
		}
		else                   //头结点和尾结点为不同结点的情况
		{
			m_pHead = m_pHead->m_pNext;
			delete m_pHead->m_pFront;
			m_pHead->m_pFront = NULL;
			m_nLength--;         //链表长度减1
			return;
		}

	}
}

//移除末元素
template <typename T>
void PhdList<T>::pop_back()
{
	if (empty())
	{
		return;
	}
	else
	{
		if (m_pHead == m_pTail)
		{
			delete m_pHead;
			m_pHead = nullptr;
			m_pTail = nullptr;
			m_nLength--;           //链表长度减1
			return;
		}
		else
		{
			m_pTail = m_pTail->m_pFront;
			delete m_pTail->m_pNext;
			m_pTail->m_pNext = nullptr;
			m_nLength--;         //链表长度减1
			return;
		}
	}
}

//访问第一个元素
template <typename T>
const T& PhdList<T>::front() const
{
	assert(m_nLength);
	return m_pHead->m_data;
}

template <typename T>
T& PhdList<T>::front() 
{
	assert(m_nLength);
	return m_pHead->m_data;
}

//访问最后一个元素
template <typename T>
const T& PhdList<T>::back() const 
{
	assert(m_nLength);
	return m_pTail->m_data;
}

template <typename T>
T& PhdList<T>::back() 
{
	assert(m_nLength);
	return m_pTail->m_data;
}

//判断链表是否为空
template <typename T>
bool PhdList<T>::empty() const
{
	if (m_nLength == 0)
		return true;
	else
		return false;
}

//返回元素数
template <typename T>
int PhdList<T>::size() const 
{
	return m_nLength;
}

//清空链表，释放内存
template <typename T>
void PhdList<T>::clear()
{
	if (empty())
		return;
	else
	{
		while (m_pHead != m_pTail)
		{
			m_pHead = m_pHead->m_pNext;
			delete m_pHead->m_pFront;
			m_pHead->m_pFront = nullptr;
		}
		delete m_pHead;
		m_nLength = 0;     //清空链表长度
		m_pHead = nullptr;
		m_pTail = nullptr;
	}
}

//插入元素
template <typename T>
void PhdList<T>::insert(int nPosIndex, const T& value)
{
	if (nPosIndex < 0 || nPosIndex > m_nLength)
		return;

	if (nPosIndex == m_nLength)
	{
		push_back(value);
	}
	if (nPosIndex == 0)
	{
		push_front(value);
	}
	else
	{
		PhdNode<T>* pNewNode = new PhdNode<T>(value);
		PhdNode<T>* pFrontNode = this->m_pHead;
		PhdNode<T>* pNextNode = nullptr;

		for (int i = 1; i < m_nLength-1; i++)
		{
			if (nPosIndex == i-1)
			{
				pNextNode = pFrontNode->m_pNext;
				//
				pFrontNode->m_pNext = pNewNode;
				pNewNode->m_pNext = pNextNode;
				pNextNode->m_pFront = pNewNode;
				pNewNode->m_pFront = pFrontNode;
				m_nLength++;
				break;
			}
			else
			{
				pFrontNode = pFrontNode->m_pNext;
			}
		}
	}
}




