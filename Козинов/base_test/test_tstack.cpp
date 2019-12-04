#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
  ASSERT_NO_THROW(TStack<int> st());
}
TEST(TStack, can_check_empty)
{
	TStack<int>st;
	EXPECT_EQ(1,st.isEmpty());
}
TEST(TStack, can_check_full)
{
	TStack<int>st;
	for (int i = 0; i < MaxStackSize ; i++)
		st.push(0);
	EXPECT_EQ(1, st.isFull());
}
TEST(TStack, can_push)
{
	TStack<int>st;
	st.push(1);
	EXPECT_EQ(1, st.gettop());
}
TEST(TStack, throw_when_try_push_to_full_stack)
{
	TStack<int>st;
	for (int i = 0; i < MaxStackSize; i++)
		st.push(0);
	ASSERT_ANY_THROW(st.push(0));
}
TEST(TStack, can_pop_to_stack)
{
	TStack<int>st;
	st.push(1);
	EXPECT_EQ(1, st.pop());
}
TEST(TStack, throw_when_try_to_pop_from_empty_stack)
{
	TStack<int>st;
	ASSERT_ANY_THROW(st.pop());

}
TEST(TStack, throw_when_try_get_top_element_from_empty_stack)
{
	TStack<int>st;
	ASSERT_ANY_THROW(st.gettop());
}

