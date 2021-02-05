#pragma once

//���Ա�˳��洢�ṹ����̬���飩
template <typename T>
class PhdVector
{
public:
	explicit PhdVector(int nSize = 50);	//���캯��
	PhdVector(const PhdVector<T>& obj);	//�������캯��
	~PhdVector();						//��������
	
	//	���� = �����
	PhdVector<T>& operator=(const PhdVector<T>& obj);
	//	���� == �����
	bool operator==(const PhdVector<T>& obj);
	//	���� != �����
	bool operator!=(const PhdVector<T>& obj);
	//	���� [] �����
	T& operator[](int nIndex);
	const T& operator[](int nIndex) const;
	//	��������ת�������
	operator T*();
	operator const T*();

	int capacity() const;			//��ȡ�����С�����ص�ǰ�洢�ռ��ܹ����ɵ�Ԫ������
	int size() const;				//��ȡԪ������

	void resize(int nCount);		//�ı������пɴ洢Ԫ�صĸ��������޸�capacity��С��Ҳ�޸�size��С��
	void reserve(int nCapacity);	//Ԥ���洢�ռ䣨ֻ�޸�capacity��С�����޸�size��С��

// 	void push_back(const T& value);	//��Ԫ����ӵ�����ĩβ
// 	void pop_back();				//�Ƴ�ĩβԪ��

private:
	T* m_pList;			//T����ָ�룬���ڴ�Ŷ�̬����������ڴ��׵�ַ
	int m_nCapacity;	//��������
	int m_nSize;		//Ԫ������
};

//	���캯��
template <typename T>
PhdVector<T>::PhdVector(int nSize /*= 50*/)
	:m_pList(nullptr)
	, m_nCapacity(0)
	,m_nSize(0)
{
	assert(nSize >= 0);
	m_nCapacity = nSize;
	m_pList = new T[m_nCapacity];		//�����ô�С���ڴ�
	assert(m_pList)
	std::memset(m_pList,0, m_nCapacity);	//��ʼ�����ڴ�Ϊ0
}

//	�������캯��
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
	//�������ڴ��ֵ
// 	for (int i = 0; i < m_nCapacity; ++i)
// 	{
// 		m_pList[i] = obj.m_pList[i];
// 	}
	std::memcpy(m_pList,obj.m_pList,m_nCapacity);
}

//	��������
template <typename T>
PhdVector<T>::~PhdVector()
{
	delete[] m_pList;
	m_pList = nullptr;
	m_nCapacity = 0;
}

//	���� = �����
template <typename T>
PhdVector<T>& PhdVector<T>::operator=(const PhdVector<T>& obj)
{
	if (this != &obj)
	{
		//����������������С��obj��ͬ�����ͷ�����ԭ���ڴ棬���·���
		if (this->m_nCapacity != obj.m_nCapacity)
		{
			delete[] this->m_pList;
			this->m_pList = nullptr;
			this->m_nCapacity = obj.m_nCapacity;
			this->m_pList = new T[this->m_nCapacity];
			assert(m_pList);
			//std::memset(this->m_pList,0,m_nCapacity);
		}
		//�����ڴ��ϵ�ֵ
// 		for (int i = 0; i < this->m_nCapacity; ++i)
// 		{
// 			this->m_pList[i] = obj.m_pList[i];
// 		}
		std::memcpy(this->m_pList,obj.m_pList,this->m_nCapacity);
	}

	return *this;
}

//	���� == �����
template <typename T>
bool PhdVector<T>::operator==(const PhdVector<T>& obj)
{
	if (this->m_nCapacity != obj.m_nCapacity)
		return false;

	//�ж������Ƿ����
	for (int i = 0; i < this->m_nCapacity; ++i)
	{
		if (this->m_pList[i] != obj.m_pList[i])
			return false;
	}

	return true;
}

//	���� != �����
template <typename T>
bool PhdVector<T>::operator!=(const PhdVector<T>& obj)
{
	return !(*this == obj);
}

//	���� [] �����������Ԫ�����ã�
template <typename T>
T& PhdVector<T>::operator[](int nIndex)
{
	//��������±��Ƿ�Խ��
	assert(nIndex >= 0 && nIndex < m_nCapacity);
	return m_pList[nIndex];
}

//	���� [] �����������Ԫ��const+���ã�
template <typename T>
const T& PhdVector<T>::operator[](int nIndex) const
{
	//��������±��Ƿ�Խ��
	assert(nIndex >= 0 && nIndex < m_nCapacity);
	return m_pList[nIndex];
}

//	��������ת���������ת��Ϊָ�룩
template <typename T>
PhdVector<T>::operator T*()
{
	return m_pList;// ���ص�ǰ������˽��������׵�ַ
}

//	��������ת���������ת��Ϊconstָ�룩
template <typename T>
PhdVector<T>::operator const T*()
{
	return m_pList;// ���ص�ǰ������˽��������׵�ַ
}

//	��ȡ�����С
template <typename T>
int PhdVector<T>::capacity() const {
	return m_nCapacity;
}

//	��ȡԪ������
template <typename T>
int PhdVector<T>::size() const
{
	return m_nSize;
}

//	�ı������пɴ洢Ԫ�صĸ���
template <typename T>
void PhdVector<T>::resize(int nCount)
{
	//����������С������ nCount ��Ԫ�ء�
	//����ǰԪ���������� nCount �����С����Ϊ nCount ��Ԫ�ء�
	//����ǰԪ������С�� nCount ������Ԫ������Ϊ nCount ��Ԫ�ء�

	if (m_nSize == nCount)
		return;

	//�жϵ�ǰ����������
	if (m_nCapacity >= nCount)
	{//��
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
	{//����
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

//	Ԥ���洢�ռ�
template <typename T>
void PhdVector<T>::reserve(int nCapacity)
{
	//���� vector �����������ڻ���� nSize ��ֵ��
	//�� nSize ���ڵ�ǰ�� capacity() ��������´洢������÷��������κ��¡�
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