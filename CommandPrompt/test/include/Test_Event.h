#ifndef Test_Event_h_
#define Test_Event_h_

#include "gtest/gtest.h"
#include "Event.h"

int g_witness = -1;
void func();
void funcString(const std::string & str);
void func2();
void funcString2(const std::string & str);

class Test_Event : public testing::Test
{
public:
	class Dummy
	{
	public:
		Dummy() :
			witness(-1)
		{
		}

		void func()
		{
			witness = 42;
		}

		void funcString(const std::string & str)
		{
			witness = std::stoi(str);
		}

		void func2()
		{
			witness = 42;
		}

		void funcString2(const std::string & str)
		{
			witness = std::stoi(str);
		}

		int witness;
	};

	Event<> event;
	Event<const std::string &> eventString;
	Dummy dummy;

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

class Test_Event_Exec_CFunc : public Test_Event
{
	virtual void SetUp()
	{
		event.AddListener(&func);
		eventString.AddListener(&funcString);
		g_witness = -1;
	}

	virtual void TearDown()
	{
	}
};


class Test_Event_Exec_MethodPtr : public Test_Event
{
	virtual void SetUp()
	{
		event.AddListener(&dummy, &Dummy::func);
		eventString.AddListener(&dummy, &Dummy::funcString);
		dummy.witness = -1;
	}

	virtual void TearDown()
	{
	}
};

class Test_Event_Exec_MethodRef : public Test_Event
{
	virtual void SetUp()
	{
		event.AddListener(dummy, &Dummy::func);
		eventString.AddListener(dummy, &Dummy::funcString);
		dummy.witness = -1;
	}

	virtual void TearDown()
	{
	}
};

class Test_Event_Exec_Lambda : public Test_Event
{
	virtual void SetUp()
	{
		event.AddListener([this]() { dummy.func(); });
		eventString.AddListener([this](const std::string & str) { dummy.funcString(str); });
		dummy.witness = -1;
	}

	virtual void TearDown()
	{
	}
};

class Test_Event_Exec_Lambda_NoCapture : public Test_Event
{
	virtual void SetUp()
	{
		event.AddListener([]() { func(); });
		eventString.AddListener([](const std::string & str) { funcString(str); });
		g_witness = -1;
	}

	virtual void TearDown()
	{
	}
};

class Test_Event_EmptyInvoke : public Test_Event
{ };

#endif