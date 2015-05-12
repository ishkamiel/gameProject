#include "resources/Resource.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace pdEngine
{

class test_Resource : public ::testing::Test
{
protected:
	static void SetUpTestCase()
	{ }

	static void TearDownTestCase()
	{ }

	virtual void SetUp()
	{ }

	virtual void TearDown()
	{ }
};

TEST_F(test_Resource, nameWorksWhenConstructedWithLowercaseValue)
{
	Resource r("container/path");
	ASSERT_EQ(r.getName(), "container/path");
}

TEST_F(test_Resource, nameWorksWhenConstructedWithMIxEdCAse)
{
	Resource r("cOnTaInEr/PAth");
	ASSERT_EQ(r.getName(), "container/path");
}

TEST_F(test_Resource, getContainerNameSeemsToWork)
{
	Resource r("cOnTaInEr/PAth");
	ASSERT_EQ(r.getContainerName(), "container");
}

}


