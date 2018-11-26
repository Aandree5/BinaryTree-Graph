#include "CppUnitTest.h"
#include "TestsHelper.h"
#include "../UnweightedGraphEdge.h"
#include "../UnweightedGraphNode.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(UnweightedGraphNodeTests)
{
public:

	TEST_METHOD(Constructor_ValidInput_CreatesNode)
	{
		shared_ptr<UnweightedGraphNode> node = make_shared<UnweightedGraphNode>(5);

		Assert::IsNotNull(node.get(), L"Valid input but edge not created.");
	}

	TEST_METHOD(CreatedNode_ValidInput_CheckPropertiesValues)
	{
		shared_ptr<UnweightedGraphNode> node = make_shared<UnweightedGraphNode>(5);

		Assert::AreEqual(node->value, (size_t)5, L"'Node A' value is not right.");
		Assert::IsNull(node->next.get(), L"'node' next pointer not null.");
	}

	TEST_METHOD(AddEdge_ValidInput_AddsEdge)
	{
		shared_ptr<UnweightedGraphNode> nodeA = make_shared<UnweightedGraphNode>(5);
		shared_ptr<UnweightedGraphNode> nodeB = make_shared<UnweightedGraphNode>(6);

		nodeA->addEdge(nodeB, 2);

		Assert::AreEqual(nodeA->edges.size(), 1, L"'nodeA' edges count is not 1.");
		Assert::AreEqual(nodeB->edges.size(), 1, L"'nodeB' edges count is not 1.");
		Assert::AreEqual(nodeB->edges.front()->reference->weight, (size_t)2, L"'edge' weight is not 2.");
		Assert::AreEqual(nodeB->edges.front()->reference->getToNode(nodeA), nodeB, L"'nodeA' not connected to 'nodeB'.");
		Assert::AreEqual(nodeA->edges.front()->reference->getToNode(nodeB), nodeA, L"'nodeB' not connected to 'nodeA'.");
	}

	TEST_METHOD(AddEdge_InvalidInput_Fails)
	{
		shared_ptr<UnweightedGraphNode> nodeA = make_shared<UnweightedGraphNode>(5);
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
		shared_ptr<UnweightedGraphNode> nodeA = make_shared<UnweightedGraphNode>(5);
		shared_ptr<UnweightedGraphNode> nodeB = make_shared<UnweightedGraphNode>(6);

		nodeA->addEdge(nodeB, 2);

		// Shouldn't change anything
		nodeA->addEdge(nodeB, 100);

		Assert::AreEqual(nodeA->edges.size(), 1, L"'nodeA' edges count is not 1.");
		Assert::AreEqual(nodeB->edges.size(), 1, L"'nodeB' edges count is not 1.");
		Assert::AreEqual(nodeB->edges.front()->reference->weight, (size_t)2, L"'edge' weight is not 2.");
		Assert::AreEqual(nodeB->edges.front()->reference->getToNode(nodeA), nodeB, L"'nodeA' not connected to 'nodeB'.");
		Assert::AreEqual(nodeA->edges.front()->reference->getToNode(nodeB), nodeA, L"'nodeB' not connected to 'nodeA'.");
	}

};