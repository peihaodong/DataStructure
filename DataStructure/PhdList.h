#pragma once

//���Ա�˳��洢�ṹ��˫������

template <typename T>
class PhdList
{
private:
	//�����
	class PhdNode
	{
	public:
		//���캯��
		PhdNode(const T& data)
			:m_data(data)
			, m_pFront(nullptr)
			, m_pNext(nullptr)
		{}

		//��������
		~PhdNode()
		{
			m_pFront = nullptr;
			m_pNext = nullptr;
		}

		//��ȡ�ڵ�����
		T GetData() const {
			return m_data;
		}

	public:
		T m_data;				//������
		PhdNode<T> *m_pFront;	//ָ����ָ��ǰһ�ڵ㣩
		PhdNode<T> *m_pNext;	//ָ����ָ���һ�ڵ㣩
	};

public:
	PhdList();					//���캯��
	~PhdList();					//��������

	//	���� = �����
	PhdList<T>& operator=(const PhdList<T>& obj);

	void push_back(const T& value);		//��Ԫ����ӵ�����ĩβ
	void push_front(const T& value);	//����Ԫ�ص�������ʼ
	void pop_front();					//�Ƴ���Ԫ��
	void pop_back();					//�Ƴ�ĩԪ��
	const T& front() const;				//���ʵ�һ��Ԫ��
	T& front();
	const T& back() const;				//�������һ��Ԫ��
	T& back();
	bool empty() const;					//�ж������Ƿ�Ϊ��
	int size() const;					//����Ԫ����
	void clear();						//��������ͷ��ڴ�
	void insert(int nPosIndex,const T& value);//����Ԫ��
	

private:
	PhdNode<T>* m_pHead;		//ͷ���ָ��
	PhdNode<T>* m_pTail;		//β�ڵ�ָ��
	int m_nLength;				//������
};

//���캯��
template <typename T>
PhdList<T>::PhdList()
	:m_nLength(0)
	,m_pHead(nullptr)
	,m_pTail(nullptr)
{

}

//��������
template <typename T>
PhdList<T>::~PhdList()
{
	clear();
}

//	���� = �����
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

//��Ԫ����ӵ�����ĩβ
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
	m_nLength++;  //����������1
}

//����Ԫ�ص�������ʼ
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
	m_nLength++; //����������1
}

//�Ƴ���Ԫ��
template <typename T>
void PhdList<T>::pop_front()
{
	if (empty())
		return;
	else
	{
		if (m_pHead == m_pTail)            //ͷ����β���Ϊͬһ�������
		{
			delete m_pHead;
			m_pHead = nullptr;
			m_pTail = nullptr;
			m_nLength--;                //�����ȼ�1
			return;
		}
		else                   //ͷ����β���Ϊ��ͬ�������
		{
			m_pHead = m_pHead->m_pNext;
			delete m_pHead->m_pFront;
			m_pHead->m_pFront = NULL;
			m_nLength--;         //�����ȼ�1
			return;
		}

	}
}

//�Ƴ�ĩԪ��
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
			m_nLength--;           //�����ȼ�1
			return;
		}
		else
		{
			m_pTail = m_pTail->m_pFront;
			delete m_pTail->m_pNext;
			m_pTail->m_pNext = nullptr;
			m_nLength--;         //�����ȼ�1
			return;
		}
	}
}

//���ʵ�һ��Ԫ��
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

//�������һ��Ԫ��
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

//�ж������Ƿ�Ϊ��
template <typename T>
bool PhdList<T>::empty() const
{
	if (m_nLength == 0)
		return true;
	else
		return false;
}

//����Ԫ����
template <typename T>
int PhdList<T>::size() const 
{
	return m_nLength;
}

//��������ͷ��ڴ�
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
		m_nLength = 0;     //���������
		m_pHead = nullptr;
		m_pTail = nullptr;
	}
}

//����Ԫ��
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




