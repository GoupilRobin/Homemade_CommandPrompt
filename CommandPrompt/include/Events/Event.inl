#ifndef Event_inl_
#define Event_inl_

/*
* Event<Args...>
*/
template <typename ...Args>
Event<Args...>::EventDelegate::EventDelegate(Function funcInvoke, std::uintptr_t * funcPtr) :
	FunctionInvoke(funcInvoke), FunctionPointer(funcPtr)
{
}


// Add a listener with func (catch anything convertible to std::function, from c-style func to lambdas
template <typename ...Args>
void Event<Args...>::AddListener(Function func)
{
	// func.target already return a pointer to the function and the function pointer type is predictable
	if (func.target<void(*)(Args...)>() != 0x0)
	{
		AddListener(EventDelegate(func, (uintptr_t *)func.target<void(*)(Args...)>()));
	}
	else
	{
		// For lambdas
		// We cast func into a (uintptr_t *) by tricking a bit the compiler
		AddListener(EventDelegate(func, *((uintptr_t **)&func)));
	}
}

// Add a listener with method with a pointer on the object
template <typename ...Args>
template <class C>
void Event<Args...>::AddListener(C * obj, void (C::*method)(Args...))
{
	// Function type is not predictable through std::function.target
	// We cast method into a (uintptr_t *) by tricking a bit the compiler
	AddListener(EventDelegate(easy_bind(Function(), method, obj), *((uintptr_t **)&method)));
}

// Add a listener with method with a reference on the object
template <typename ...Args>
template <class C>
void Event<Args...>::AddListener(C & obj, void (C::*method)(Args...))
{
	// Function type is not predictable through std::function.target
	// We cast method into a (uintptr_t *) by tricking a bit the compiler
	AddListener(EventDelegate(easy_bind(Function(), method, &obj), *((uintptr_t **)&method)));
}


// Remove a listener with func (catch anything convertible to std::function, from c-style func to lambdas
template <typename ...Args>
void Event<Args...>::RemoveListener(Function func)
{
	// func.target already return a pointer to the function and the function pointer type is predictable
	if (func.target<void(*)(Args...)>() != 0x0)
	{
		RemoveListener(EventDelegate(func, (uintptr_t *)func.target<void(*)(Args...)>()));
	}
	else
	{
		// For lambdas
		// We cast func into a (uintptr_t *) by tricking a bit the compiler
		RemoveListener(EventDelegate(func, *((uintptr_t **)&func)));
	}
}

// Remove a listener with method with a poitner on the object
template <typename ...Args>
template <class C>
void Event<Args...>::RemoveListener(C * obj, void (C::*method)(Args...))
{
	// Function type is not predictable through std::function.target
	// We cast method into a (uintptr_t *) by tricking a bit the compiler
	RemoveListener(EventDelegate(easy_bind(Function(), method, obj), *((uintptr_t **)&method)));
}

// Remove a listener with method with a reference on the object
template <typename ...Args>
template <class C>
void Event<Args...>::RemoveListener(C & obj, void (C::*method)(Args...))
{
	// Function type is not predictable through std::function.target
	// We cast method into a (uintptr_t *) by tricking a bit the compiler
	RemoveListener(EventDelegate(easy_bind(Function(), method, &obj), *((uintptr_t **)&method)));
}


template <typename ...Args>
void Event<Args...>::ClearListeners()
{
	m_Listeners.clear();
}


template <typename ...Args>
void Event<Args...>::Invoke(Args... args)
{
	for (int i = 0; i < GetListenersCount(); ++i)
	{
		if (m_Listeners[i].FunctionInvoke)
		{
			m_Listeners[i].FunctionInvoke(args...);
		}
	}
}


template <typename ...Args>
int Event<Args...>::GetListenersCount() const
{
	return (int)m_Listeners.size();
}


template <typename ...Args>
void Event<Args...>::AddListener(EventDelegate delegate)
{
	// Make sure the delegate is valid
	if (!delegate.FunctionInvoke || delegate.FunctionPointer == 0x0)
	{
		return;
	}

	// Check if the delegate is already registered
	for (int i = 0; i < m_Listeners.size(); ++i)
	{
		// Make sure 'm_Listeners[i]' is STILL valid (just in case)
		// TODO: should probably so something about the delegate not being valid anymore
		if (!m_Listeners[i].FunctionInvoke || m_Listeners[i].FunctionPointer == 0x0)
		{
			if (i + 1 < m_Listeners.size())
			{
				continue;
			}
			else
			{
				return;
			}
		}

		// Stop here if the pointers match, the delegate is already registered
		if (*delegate.FunctionPointer == *m_Listeners[i].FunctionPointer || delegate.FunctionPointer == m_Listeners[i].FunctionPointer)
		{
			return;
		}
	}
	m_Listeners.push_back(delegate);
}


template <typename ...Args>
void Event<Args...>::RemoveListener(EventDelegate delegate)
{
	// Make sure the delegate is valid
	if (!delegate.FunctionInvoke || delegate.FunctionPointer == 0x0)
	{
		return;
	}

	// Look for the delegate in m_Listeners
	for (int i = 0; i < m_Listeners.size(); ++i)
	{
		// Make sure 'm_Listeners[i]' is STILL valid (just in case)
		// TODO: should probably so something about the element not being valid anymore
		if (!m_Listeners[i].FunctionInvoke || m_Listeners[i].FunctionPointer == 0x0)
		{
			if (i + 1 < m_Listeners.size())
			{
				continue;
			}
			else
			{
				return;
			}
		}

		// We just found the delegate, remove it
		if (*delegate.FunctionPointer == *m_Listeners[i].FunctionPointer || delegate.FunctionPointer == m_Listeners[i].FunctionPointer)
		{
			m_Listeners.erase(m_Listeners.begin() + i);
			return;
		}
	}
}
/*
* !Event<Args...>
*/

#endif