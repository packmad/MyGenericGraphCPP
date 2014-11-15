#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MGGCPPUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Graph g;
			g.t = 5;
			Assert::IsTrue(true);
		}

	};
}
