#ifndef VariableMonitor_h_
#define VariableMonitor_h_

template <typename T>
class VariableMonitor
{
public:
	VariableMonitor(const T * target, size_t objectSize = 0);
	~VariableMonitor();

	void SetTarget(const T * newTarget, size_t objectSize = 0);
	void Update();
	bool IsModified();

protected:
	const T * m_Target;
	size_t m_ObjectSize;
	char * m_Data;
	char * m_SnapshotData;
};

#include "VariableMonitor.inl"

#endif
