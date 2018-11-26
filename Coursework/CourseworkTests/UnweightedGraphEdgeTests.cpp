#include "CppUnitTest.h"
#include "TestsHelper.h"
#include "../UnweightedGraphEdge.h"
#include "../UnweightedGraphNode.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(UnweightedGraphEdgeTests)
{
public:

	TEST_METHOD(Constructor_ValidInput_CreatesEdge)
	{
		shared_ptr<UnweightedGraphNode> nodeA = make_shared<UnweightedGraphNode>(5);
		shared_ptr<UnweightedGraphNode> nodeB = make_shared<UnweightedGraphNode>(6);

		unique_ptr<UnweightedGraphEdge> node = make_unique<UnweightedGraphEdge>(nodeA, nodeB, 50);

		Assert::IsNotNull(node.get(), L"Valid input but edge not created.");
	}

	TEST_METHOD(Constructor_InvalidInput_Fails)
	{
		string value;
		bool passed = false;

		try
		{
			unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(nullptr, nullptr, 50);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument error not thrown.");
	}

	TEST_METHOD(CreatedEdge_ValidInput_CheckPropertiesValues)
	{
		shared_ptr<UnweightedGraphNode> nodeA = make_shared<UnweightedGraphNode>(5);
		shared_ptr<UnweightedGraphNode> nodeB = make_shared<UnweightedGraphNode>(6);

		unique_ptr<UnweightedGraphEdge> node = make_unique<UnweightedGraphEdge>(nodeA, nodeB, 50);

		Assert::IsNotNull(node->nodeA.lock().get(), L"'Node A' is nullptr.");
		Assert::IsNotNull(node->nodeB.lock().get(), L"'Node B' is nullptr.");
		Assert::AreEqual(node->weight, (size_t)50, L"Edge weight is not 50.");
		Assert::AreEqual(node->nodeA.lock()->value, nodeA->value, L"'Node A' value is not right.");
		Assert::AreEqual(node->nodeB.lock()->value, nodeB->value, L"'Node B' value is not right.");
	}

	TEST_METHOD(GetToNode_Returns_RightNode)
	{
		shared_ptr<UnweightedGraphNode> nodeA = make_shared<UnweightedGraphNode>(5);
		shared_ptr<UnweightedGraphNode> nodeB = make_shared<UnweightedGraphNode>(6);

		unique_ptr<UnweightedGraphEdge> node = make_unique<UnweightedGraphEdge>(nodeA, nodeB, 50);

		shared_ptr<UnweightedGraphNode> result = node->getToNode(nodeA);

		Assert::IsNotNull(result.get(), L"'result' is nullptr.");
		Assert::AreEqual(result->value, nodeB->value, L"'result' value is not right.");

		shared_ptr<UnweightedGraphNode> resultB = node->getToNode(nodeB);

		Assert::IsNotNull(resultB.get(), L"'resultB' is nullptr.");
		Assert::AreEqual(resultB->value, nodeA->value, L"'resultB' value is not right.");
	}

};