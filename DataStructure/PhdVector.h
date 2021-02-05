#pragma once

//���Ա�˳��洢�ṹ����̬���飩
template <typename T>
class PhdVector
{
public:
	//typedef unsigned int     size_t;
	//typedef size_t size_type;

	explicit PhdVector();	//���캯��
	PhdVector(const PhdVector<T>& obj);	//�������캯��
	~PhdVector();						//��������
	
	//	���� = �����
	PhdVector<T>& operator=(const PhdVector<T>& obj);
	//	���� == �����
	bool operator==(const PhdVector<T>& obj);
	//	���� != �����
	bool operator!=(const PhdVector<T>& obj);
	//	���� [] �����
	T& operator[](int nPosIndex);
	const T& operator[](int nPosIndex) const;
	//	��������ת�������
	operator T*();
	operator const T*();

	T& at(int nPosIndex);				//����ָ����Ԫ�أ�ͬʱ����Խ����
	const T& at(int nPosIndex) const;
	T& front();						//���ʵ�һ��Ԫ��
	const T& front() const;			
	T& back();						//�������һ��Ԫ��
	const T& back() const;
	T* data();						//����ָ���ڴ��������һ��Ԫ�ص�ָ��
	const T* data() const;

	bool empty() const;				//��������Ƿ�Ϊ��
	int size() const;				//��ȡԪ������
	int max_size() const;			//���ؿ����ɵ����Ԫ����
	int capacity() const;			//��ȡ�����С�����ص�ǰ�洢�ռ��ܹ����ɵ�Ԫ������
	
	void resize(int nCount);		//�ı������пɴ洢Ԫ�صĸ��������޸�capacity��С��Ҳ�޸�size��С��
	void resize(int nCount,const T& value);
	void reserve(int nCapacity);	//Ԥ���洢�ռ䣨ֻ�޸�capacity��С�����޸�size��С��
	void shrink_to_fit();			//ͨ���ͷ�δʹ�õ��ڴ�����ڴ��ʹ��

	void clear();					//�������Ԫ��
	void insert(int nPosIndex,const T& value);//����Ԫ�أ���ָ��λ��֮ǰ��
	void erase(int nPosIndex);		//����Ԫ��
	void push_back(const T& value);	//��Ԫ����ӵ�����ĩβ
	void pop_back();				//�Ƴ�ĩβԪ��
	void swap(PhdVector<T>& obj);	//����Ԫ��

private:
	T* m_pList;			//T����ָ�룬���ڴ�Ŷ�̬����������ڴ��׵�ַ
	int m_nCapacity;	//��������
	int m_nSize;		//Ԫ������
};

//	���캯��
template <typename T>
PhdVector<T>::PhdVector()
	:m_pList(nullptr)
	, m_nCapacity(0)
	,m_nSize(0)
{
	m_pList = new T[m_nCapacity];		//�����ô�С���ڴ�
	assert(m_pList)
	std::memset(m_pList,0, m_nCapacity);	//��ʼ�����ڴ�Ϊ0
}

//	�������캯��
template <typename T>
PhdVector<T>::PhdVector(const PhdVector<T>& obj)
{
	m_nCapacity = obj.m_nCapacity;
	m_nSize = obj.m_nSize;
	m_pList = new T[m_nCapacity];
	assert(m_pList);
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
	m_nSize = 0;
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
		}
		//�����ڴ��ϵ�ֵ
		std::memcpy(this->m_pList,obj.m_pList,this->m_nCapacity);

		if (this->m_nSize != obj.m_nSize)
			this->m_nSize = obj.m_nSize;
	}

	return *this;
}

//	���� == �����
template <typename T>
bool PhdVector<T>::operator==(const PhdVector<T>& obj)
{
	if (this->m_nSize != obj.m_nSize)
		return false;

	//�ж������Ƿ����
	for (int i = 0; i < this->m_nSize; ++i)
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
T& PhdVector<T>::operator[](int nPosIndex)
{
	//��������±��Ƿ�Խ��
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
}

//	���� [] �����������Ԫ��const+���ã�
template <typename T>
const T& PhdVector<T>::operator[](int nPosIndex) const
{
	//��������±��Ƿ�Խ��
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
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

//����ָ����Ԫ�أ�ͬʱ����Խ����
template <typename T>
T& PhdVector<T>::at(int nPosIndex)
{
	//��������±��Ƿ�Խ��
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
}

template <typename T>
const T& PhdVector<T>::at(int nPosIndex) const
{
	//��������±��Ƿ�Խ��
	assert(nPosIndex >= 0 && nPosIndex < m_nCapacity);
	return m_pList[nPosIndex];
}

//���ʵ�һ��Ԫ��
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

//�������һ��Ԫ��
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

//����ָ���ڴ��������һ��Ԫ�ص�ָ��
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

//��������Ƿ�Ϊ��
template <typename T>
bool PhdVector<T>::empty() const
{
	return m_nSize;
}

//	��ȡԪ������
template <typename T>
int PhdVector<T>::size() const
{
	return m_nSize;
}

//���ؿ����ɵ����Ԫ����
template <typename T>
int PhdVector<T>::max_size() const 
{
	return INT_MAX;
	return int(((unsigned int)(~0)) >> 1);//���ֵ���Ƿ���λΪ0������λ��Ϊ1������
	//~0������λ��Ϊ1��ת�����޷�������ȷ���������߼����ƣ������������֣�:)����
	//Ҳ���Ǹ�λ����Ϊ���ƿճ���0������������һ�����λ������λ��Ϊ0����λ��Ϊ1��������
}

//	��ȡ�����С
template <typename T>
int PhdVector<T>::capacity() const {
	return m_nCapacity;
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
				m_pList[i] = value;
			}
			m_nSize = nCount;
		}
	}
	else
	{//����
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

//	Ԥ���洢�ռ�
template <typename T>
void PhdVector<T>::reserve(int nCapacity)
{
	//���� vector �����������ڻ���� nCapacity ��ֵ��
	//�� nCapacity ���ڵ�ǰ�� capacity() ��������´洢������÷��������κ��¡�
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

//ͨ���ͷ�δʹ�õ��ڴ�����ڴ��ʹ��
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

//�������Ԫ��
template <typename T>
void PhdVector<T>::clear()
{
	m_nSize = 0;
}

//����Ԫ�أ���ָ��λ��֮ǰ��
template <typename T>
void PhdVector<T>::insert(int nPosIndex, const T& value)
{
	//�����Ƿ���
	if ((m_nSize + 1) > m_nCapacity)
	{//����
		m_nCapacity *= 2;
		T* pNewList = new T[m_nCapacity];
		assert(pNewList);
		std::memset(pNewList,0,m_nCapacity);

		//�Ƿ���ӵ�β��
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
	{//��
		//�Ƿ���ӵ�β��
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

//����Ԫ��
template <typename T>
void PhdVector<T>::erase(int nPosIndex)
{
	if (m_nSize == 0)
		return;

	//�Ƿ�ɾ��β��Ԫ��
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

//��Ԫ����ӵ�����ĩβ
template <typename T>
void PhdVector<T>::push_back(const T& value)
{
	//�����Ƿ���
	if ((m_nSize + 1) > m_nCapacity)
	{//����
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
	{//��
		m_pList[m_nSize] = value;
		m_nSize++;
	}
}

//�Ƴ�ĩβԪ��
template <typename T>
void PhdVector<T>::pop_back()
{
	m_nSize--;
}

//����Ԫ��
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