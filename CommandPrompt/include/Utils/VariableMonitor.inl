#ifndef VariableMonitor_inl_
#define VariableMonitor_inl_

#include "VariableMonitor.h"

template<typename T>
VariableMonitor<T>::VariableMonitor(const T * target, size_t objectSize) :
	m_Target(target), m_ObjectSize(objectSize == 0 ? sizeof(T) : objectSize), m_Data(new char[m_ObjectSize]), m_SnapshotData(new char[m_ObjectSize])
{
	Update();
}

template<typename T>
VariableMonitor<T>::~VariableMonitor()
{
	delete[] m_Data;
	delete[] m_SnapshotData;
}

template<typename T>
void VariableMonitor<T>::SetTarget(const T * newTarget, size_t objectSize)
{
	m_Target = newTarget;
	m_ObjectSize = objectSize == 0 ? sizeof(T) : objectSize;
}

template<typename T>
void VariableMonitor<T>::Update()
{
	if (m_Data == 0x0 || m_Target == 0x0) return;

	memcpy_s(m_Data, m_ObjectSize, m_Target, m_ObjectSize);
}

template<typename T>
bool VariableMonitor<T>::IsModified()
{
	if (m_SnapshotData == 0x0 || m_Target == 0x0) return false;

	memcpy_s(m_SnapshotData, m_ObjectSize, m_Target, m_ObjectSize);
	return memcmp(m_Data, m_SnapshotData, m_ObjectSize) != 0;
}

#endif