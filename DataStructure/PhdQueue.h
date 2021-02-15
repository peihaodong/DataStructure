#pragma once

//ѭ�����У��Ƚ��ȳ���
template <typename T>
class PhdQueue
{
public:
	PhdQueue(int nCapacity = 10);	//���캯��
	~PhdQueue();					//��������

	const T& front() const;			//���ʵ�һ��Ԫ��
	T& front();
	const T& back() const;			//�������һ��Ԫ��
	T& back();

	bool empty() const;				//���ײ�������Ƿ�Ϊ��
	int size() const;				//�������ɵ�Ԫ����

	void push(const T& value);		//�����β������Ԫ��
	void pop();						//ɾ���׸�Ԫ��

private:
	bool IsFull() const;			//�����Ƿ�����

private:
	T* m_pBuffer;			//
	int m_nSize;			//Ԫ������
	int m_nCapacity;		//��������
	int m_nHead;			//ͷ����
	int m_nTail;			//β����

};

//���캯��
template <typename T>
PhdQueue<T>::PhdQueue(int nCapacity /*= 10*/)
{
	m_nSize = 0;
	m_nCapacity = nCapacity;
	m_nHead = m_nTail = 0;
	m_pBuffer = new T[m_nCapacity];
}

//��������
template <typename T>
PhdQueue<T>::~PhdQueue()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
	m_nCapacity = m_nSize = m_nHead = m_nTail = 0;
}

//���ʵ�һ��Ԫ��
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

//�������һ��Ԫ��
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

//���ײ�������Ƿ�Ϊ��
template <typename T>
bool PhdQueue<T>::empty() const
{
	return m_nHead == m_nTail;
}

//�������ɵ�Ԫ����
template <typename T>
int PhdQueue<T>::size() const
{
	return m_nSize;
}

//�����β������Ԫ��
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

//ɾ���׸�Ԫ��
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

//�����Ƿ�����
template <typename T>
bool PhdQueue<T>::IsFull() const
{
	return (m_nTail + 1) % m_nCapacity == m_nHead;
}


