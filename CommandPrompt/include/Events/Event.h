#ifndef Event_h_
#define Event_h_

#include <functional>
#include <vector>
#include <algorithm>
#include "EasyBind.h"

template <typename ...Args>
class Event
{
protected:
	typedef std::function<void(Args...)> Function;

	class EventDelegate
	{
	public:
		EventDelegate(Function funcInvoke, std::uintptr_t * funcPtr);

		Function FunctionInvoke;
		// Force conversion to uintptr_t * so we can check the actual pointer fo the function without having to care about its actual type
		std::uintptr_t * FunctionPointer;
	};

public:
	void AddListener(Function func);
	template <class C>
	void AddListener(C * obj, void (C::*method)(Args...));
	template <class C>
	void AddListener(C & obj, void (C::*method)(Args...));

	void RemoveListener(Function func);
	template <class C>
	void RemoveListener(C * obj, void (C::*method)(Args...));
	template <class C>
	void RemoveListener(C & obj, void (C::*method)(Args...));

	void ClearListeners();

	void Invoke(Args... args);

	int GetListenersCount() const;

protected:
	void AddListener(EventDelegate delegate);
	void RemoveListener(EventDelegate delegate);

	std::vector<EventDelegate> m_Listeners;
};

using EventV = Event<>;

// Implementation
#include "Event.inl"

#endif