#include "CppUnitTest.h"
#include "TestsHelper.h"
#include "../UnweightedGraph.h"
#include "../UnweightedGraphEdge.h"
#include "../UnweightedGraphNode.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(UnweightedGraphTests)
{
public:

	TEST_METHOD(Constructor_ValidInput_CreatesGraph)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>(5);

		Assert::IsNotNull(graph.get(), L"Valid input but edge not created.");
	}

};