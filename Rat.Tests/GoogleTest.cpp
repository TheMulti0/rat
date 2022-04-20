#include "GoogleTest.h"

void MessageEquals(Message lhs, Message rhs)
{
	EXPECT_EQ(
		lhs.GetType(),
		lhs.GetType());
	EXPECT_ARRAY_EQ(
		char,
		lhs.GetContent().data(),
		rhs.GetContent().data(),
		lhs.GetContent().size());
}