#include <string>
#include <iostream>
#include "gtest/gtest.h"
#include "Test_Event.h"
#include "Event.h"

/*
 * CFunc Tests
 */
TEST_F(Test_Event, Listener_CFunc_Add_Void)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(&func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(&func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(&func2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.AddListener(&func2);
	ASSERT_EQ(2, event.GetListenersCount());
}

TEST_F(Test_Event, Listener_CFunc_Add_String)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(&funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(&funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(&funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.AddListener(&funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
}

TEST_F(Test_Event, Listeners_CFunc_Remove_Void)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(&func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(&func2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.RemoveListener(&func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener(&func);
	ASSERT_EQ(1, event.GetListenersCount());
}

TEST_F(Test_Event, Listeners_CFunc_Remove_String)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(&funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(&funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.RemoveListener(&funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener(&funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
}

TEST_F(Test_Event_Exec_CFunc, Listeners_CFunc_Exec_Void)
{
	ASSERT_EQ(-1, g_witness);
	event.Invoke();
	ASSERT_EQ(42, g_witness);
}

TEST_F(Test_Event_Exec_CFunc, Listeners_CFunc_Exec_String)
{
	ASSERT_EQ(-1, g_witness);
	eventString.Invoke("789551");
	ASSERT_EQ(789551, g_witness);
}
/*
 * !CFunc Tests
 */

/*
 * Lambda Tests
 */
TEST_F(Test_Event, Listener_Lambda_Add_Void_NoCapture)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener([]() { func(); });
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener([]() { func(); });
	ASSERT_EQ(2, event.GetListenersCount());
}

TEST_F(Test_Event, Listener_Lambda_Add_String_NoCapture)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener([](const std::string & str) { funcString(str); });
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener([](const std::string & str) { funcString(str); });
	ASSERT_EQ(2, eventString.GetListenersCount());
}

TEST_F(Test_Event, Listener_Lambda_Add_Void_Capture)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener([this]() { dummy.func(); });
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener([this]() { dummy.func(); });
	ASSERT_EQ(2, event.GetListenersCount());
}

TEST_F(Test_Event, Listener_Lambda_Add_String_Capture)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener([this](const std::string & str) { dummy.funcString(str); });
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener([this](const std::string & str) { dummy.funcString(str); });
	ASSERT_EQ(2, eventString.GetListenersCount());
}

TEST_F(Test_Event, Listeners_Lambda_Remove_Void_NoCapture)
{
	auto funcObj = []() { func(); };
	auto funcObj2 = []() { func(); };

	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(funcObj);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(funcObj2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.RemoveListener(funcObj);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener(funcObj);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener([]() { func(); });
	ASSERT_EQ(1, event.GetListenersCount());
}

TEST_F(Test_Event, Listeners_Lambda_Remove_String_NoCapture)
{
	auto funcObj = [](const std::string & str) { funcString(str); };
	auto funcObj2 = [](const std::string & str) { funcString(str); };

	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(funcObj);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(funcObj2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.RemoveListener(funcObj);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener(funcObj);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener([](const std::string & str) { funcString(str); });
	ASSERT_EQ(1, eventString.GetListenersCount());
}

TEST_F(Test_Event, Listeners_Lambda_Remove_Void_Capture)
{
	auto funcObj = [this]() { dummy.func(); };
	auto funcObj2 = [this]() { dummy.func(); };

	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(funcObj);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(funcObj2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.RemoveListener(funcObj);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener(funcObj);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener([this]() { dummy.func(); });
	ASSERT_EQ(1, event.GetListenersCount());
}

TEST_F(Test_Event, Listeners_Lambda_Remove_String_Capture)
{
	auto funcObj = [this](const std::string & str) { dummy.funcString(str); };
	auto funcObj2 = [this](const std::string & str) { dummy.funcString(str); };

	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(funcObj);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(funcObj2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.RemoveListener(funcObj);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener(funcObj);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener([this](const std::string & str) { dummy.funcString(str); });
	ASSERT_EQ(1, eventString.GetListenersCount());
}

TEST_F(Test_Event_Exec_Lambda_NoCapture, Listeners_Lambda_Exec_Void_NoCapture)
{
	ASSERT_EQ(-1, g_witness);
	event.Invoke();
	ASSERT_EQ(42, g_witness);
}

TEST_F(Test_Event_Exec_Lambda_NoCapture, Listeners_Lambda_Exec_String_NoCapture)
{
	ASSERT_EQ(-1, g_witness);
	eventString.Invoke("4865");
	ASSERT_EQ(4865, g_witness);
}

TEST_F(Test_Event_Exec_Lambda, Listeners_Lambda_Exec_Void_Capture)
{
	ASSERT_EQ(-1, dummy.witness);
	event.Invoke();
	ASSERT_EQ(42, dummy.witness);
}

TEST_F(Test_Event_Exec_Lambda, Listeners_Lambda_Exec_String_Capture)
{
	ASSERT_EQ(-1, dummy.witness);
	eventString.Invoke("4865");
	ASSERT_EQ(4865, dummy.witness);
}
/*
 * !Lambda Tests
 */



/*
 * Method Object Pointer Tests
 */
TEST_F(Test_Event, Listener_MethodPtr_Add_Void)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(&dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(&dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(&dummy, &Dummy::func2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.AddListener(&dummy, &Dummy::func2);
	ASSERT_EQ(2, event.GetListenersCount());
}

TEST_F(Test_Event, Listener_MethodPtr_Add_String)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(&dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(&dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(&dummy, &Dummy::funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.AddListener(&dummy, &Dummy::funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
}

TEST_F(Test_Event, Listeners_MethodPtr_Remove_Void)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(&dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(&dummy, &Dummy::func2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.RemoveListener(&dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener(&dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
}

TEST_F(Test_Event, Listeners_MethodPtr_Remove_String)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(&dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(&dummy, &Dummy::funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.RemoveListener(&dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener(&dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
}

TEST_F(Test_Event_Exec_MethodPtr, Listeners_MethodPtr_Exec_Void)
{
	ASSERT_EQ(-1, dummy.witness);
	event.Invoke();
	ASSERT_EQ(42, dummy.witness);
}

TEST_F(Test_Event_Exec_MethodPtr, Listeners_MethodPtr_Exec_String)
{
	ASSERT_EQ(-1, dummy.witness);
	eventString.Invoke("45887");
	ASSERT_EQ(45887, dummy.witness);
}
/*
 * !Method Object Pointer Tests
 */



/*
 * Method Object Reference Tests
 */
TEST_F(Test_Event, Listener_MethodRef_Add_Void)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(dummy, &Dummy::func2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.AddListener(dummy, &Dummy::func2);
	ASSERT_EQ(2, event.GetListenersCount());
}

TEST_F(Test_Event, Listener_MethodRef_Add_String)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(dummy, &Dummy::funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.AddListener(dummy, &Dummy::funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
}

TEST_F(Test_Event, Listeners_MethodRef_Remove_Void)
{
	ASSERT_EQ(0, event.GetListenersCount());
	event.AddListener(dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.AddListener(dummy, &Dummy::func2);
	ASSERT_EQ(2, event.GetListenersCount());
	event.RemoveListener(dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
	event.RemoveListener(dummy, &Dummy::func);
	ASSERT_EQ(1, event.GetListenersCount());
}

TEST_F(Test_Event, Listeners_MethodRef_Remove_String)
{
	ASSERT_EQ(0, eventString.GetListenersCount());
	eventString.AddListener(dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.AddListener(dummy, &Dummy::funcString2);
	ASSERT_EQ(2, eventString.GetListenersCount());
	eventString.RemoveListener(dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
	eventString.RemoveListener(dummy, &Dummy::funcString);
	ASSERT_EQ(1, eventString.GetListenersCount());
}

TEST_F(Test_Event_Exec_MethodRef, Listeners_MethodRef_Exec_Void)
{
	ASSERT_EQ(-1, dummy.witness);
	event.Invoke();
	ASSERT_EQ(42, dummy.witness);
}

TEST_F(Test_Event_Exec_MethodRef, Listeners_MethodRef_Exec_String)
{
	ASSERT_EQ(-1, dummy.witness);
	eventString.Invoke("45887");
	ASSERT_EQ(45887, dummy.witness);
}
// TODO: Add exec
/*
 * !Method Object Pointer Tests
 */

/*
 * Empty invoke tests
 */
TEST_F(Test_Event_EmptyInvoke, Listeners_MethodRef_EmptyInvoke_Void)
{
	ASSERT_NO_THROW(event.Invoke());
}

TEST_F(Test_Event_EmptyInvoke, Listeners_MethodRef_EmptyInvoke_String)
{
	ASSERT_NO_THROW(eventString.Invoke("4891539"));
}
/*
 * !Empty invoke tests
 */

void func()
{
	g_witness = 42;
}

void funcString(const std::string & str)
{
	g_witness = std::stoi(str);
}

void func2()
{
	g_witness = 42;
}

void funcString2(const std::string & str)
{
	g_witness = std::stoi(str);
}