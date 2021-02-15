#pragma once

//ջ���Ƚ������
template <typename T>
class PhdStack
{
public:
	PhdStack();					//���캯��
	~PhdStack();				//��������

	const T& top() const;		//����ջ��Ԫ��
	T& top();

	bool empty() const;			//���ײ�������Ƿ�Ϊ��
	int size() const;			//�������ɵ�Ԫ����

	void push(const T& value);	//��ջ������Ԫ��
	void pop();					//ɾ��ջ��Ԫ��

private:
	T* m_pBuffer;			//ջ�ռ�ָ��
	int m_nCapacity;		//��������
	int m_nSize;			//Ԫ��������ջ�����꣩
};

//���캯��
template <typename T>
PhdStack<T>::PhdStack()
	:m_pBuffer(nullptr)
	,m_nSize(0)
	, m_nCapacity(1)
{
	m_pBuffer = new T[m_nCapacity];
	assert(m_pBuffer);
}

//��������
template <typename T>
PhdStack<T>::~PhdStack<T>()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
	m_nSize = 0;
}

//����ջ��Ԫ��
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

//���ײ�������Ƿ�Ϊ��
template <typename T>
bool PhdStack<T>::empty() const
{
	if (m_nSize)
		return true;
	else
		return false;
}

//�������ɵ�Ԫ����
template <typename T>
int PhdStack<T>::size() const 
{
	return m_nSize;
}

//��ջ������Ԫ��
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

//ɾ��ջ��Ԫ��
template <typename T>
void PhdStack<T>::pop()
{
	m_nSize--;
}
