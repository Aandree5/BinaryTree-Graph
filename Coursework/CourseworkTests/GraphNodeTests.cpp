#include "CppUnitTest.h"
#include "TestsHelper.h"
#include "../GraphEdge.h"
#include "../GraphNode.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(GraphNodeTests)
{
public:

	TEST_METHOD(Constructor_ValidInput_CreatesNode)
	{
		shared_ptr<GraphNode> node = make_shared<GraphNode>(5);

		Assert::IsNotNull(node.get(), L"Valid input but edge not created.");
	}

	TEST_METHOD(CreatedNode_ValidInput_CheckPropertiesValues)
	{
		shared_ptr<GraphNode> node = make_shared<GraphNode>(5);

		Assert::AreEqual(node->value, (size_t)5, L"'Node A' value is not right.");
		Assert::IsNull(node->next.get(), L"'node' next pointer not null.");
	}

	TEST_METHOD(AddEdge_ValidInput_AddsEdge)
	{
		shared_ptr<GraphNode> nodeA = make_shared<GraphNode>(5);
		shared_ptr<GraphNode> nodeB = make_shared<GraphNode>(6);

		nodeA->addEdge(nodeB, 2);

		Assert::AreEqual(1, nodeA->edges.size(), L"'nodeA' edges count is not 1.");
		Assert::AreEqual(1, nodeB->edges.size(), L"'nodeB' edges count is not 1.");
		Assert::AreEqual((size_t)2, nodeB->edges.front()->reference->weight, L"'edge' weight is not 2.");
		Assert::AreEqual(nodeB, nodeB->edges.front()->reference->getToNode(nodeA), L"'nodeA' not connected to 'nodeB'.");
		Assert::AreEqual(nodeA, nodeA->edges.front()->reference->getToNode(nodeB), L"'nodeB' not connected to 'nodeA'.");
	}

	TEST_METHOD(AddEdge_InvalidInput_Fails)
	{
		shared_ptr<GraphNode> nodeA = make_shared<GraphNode>(5);
		bool passed = false;

		try
		{
			nodeA->addEdge(nullptr, 2);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed);
	}

	TEST_METHOD(AddEdge_ValidInput_AlreadyExists)
	{
		shared_ptr<GraphNode> nodeA = make_shared<GraphNode>(5);
		shared_ptr<GraphNode> nodeB = make_shared<GraphNode>(6);

		nodeA->addEdge(nodeB, 2);

		// Shouldn't change anything
		nodeA->addEdge(nodeB, 100);

		Assert::AreEqual(1, nodeA->edges.size(), L"'nodeA' edges count is not 1.");
		Assert::AreEqual(1, nodeB->edges.size(), L"'nodeB' edges count is not 1.");
		Assert::AreEqual((size_t)2, nodeB->edges.front()->reference->weight, L"'edge' weight is not 2.");
		Assert::AreEqual(nodeB, nodeB->edges.front()->reference->getToNode(nodeA), L"'nodeA' not connected to 'nodeB'.");
		Assert::AreEqual(nodeA, nodeA->edges.front()->reference->getToNode(nodeB), L"'nodeB' not connected to 'nodeA'.");
	}

};