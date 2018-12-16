#include "CppUnitTest.h"
#include "TestsHelper.h"
#include "../GraphEdge.h"
#include "../GraphNode.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(GraphEdgeTests)
{
public:

	TEST_METHOD(Constructor_ValidInput_CreatesEdge)
	{
		shared_ptr<GraphNode> nodeA = make_shared<GraphNode>(5);
		shared_ptr<GraphNode> nodeB = make_shared<GraphNode>(6);

		unique_ptr<GraphEdge> edge = make_unique<GraphEdge>(nodeA, nodeB, 50);

		Assert::IsNotNull(edge.get(), L"Valid input but edge not created.");
	}

	TEST_METHOD(Constructor_InvalidInput_Fails)
	{
		string value;
		bool passed = false;

		try
		{
			unique_ptr<GraphEdge> edge = make_unique<GraphEdge>(nullptr, nullptr, 50);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument error not thrown.");
	}

	TEST_METHOD(CreatedEdge_ValidInput_CheckPropertiesValues)
	{
		shared_ptr<GraphNode> nodeA = make_shared<GraphNode>(5);
		shared_ptr<GraphNode> nodeB = make_shared<GraphNode>(6);

		unique_ptr<GraphEdge> edge = make_unique<GraphEdge>(nodeA, nodeB, 50);

		Assert::IsNotNull(edge->nodeA.lock().get(), L"'Node A' is nullptr.");
		Assert::IsNotNull(edge->nodeB.lock().get(), L"'Node B' is nullptr.");
		Assert::AreEqual(edge->weight, (size_t)50, L"Edge weight is not 50.");
		Assert::AreEqual(edge->nodeA.lock()->value, nodeA->value, L"'Node A' value is not right.");
		Assert::AreEqual(edge->nodeB.lock()->value, nodeB->value, L"'Node B' value is not right.");
	}

	TEST_METHOD(GetToNode_Returns_RightNode)
	{
		shared_ptr<GraphNode> nodeA = make_shared<GraphNode>(5);
		shared_ptr<GraphNode> nodeB = make_shared<GraphNode>(6);

		unique_ptr<GraphEdge> edge = make_unique<GraphEdge>(nodeA, nodeB, 50);

		shared_ptr<GraphNode> result = edge->getToNode(nodeA);

		Assert::IsNotNull(result.get(), L"'result' is nullptr.");
		Assert::AreEqual(result->value, nodeB->value, L"'result' value is not right.");

		shared_ptr<GraphNode> resultB = edge->getToNode(nodeB);

		Assert::IsNotNull(resultB.get(), L"'resultB' is nullptr.");
		Assert::AreEqual(resultB->value, nodeA->value, L"'resultB' value is not right.");
	}

};