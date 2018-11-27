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
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();

		Assert::IsNotNull(graph.get(), L"'graph' is null.");
	}

	TEST_METHOD(AddNode)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);

		Assert::IsNotNull(nodeA.get(), L"'nodeA' is null.");
		Assert::IsNotNull(nodeA->next.get(), L"'nodeA' next is null.");
		Assert::AreEqual(nodeB, nodeA->next, L"'nodeA' next is not 'nodeB'");

		Assert::IsNotNull(nodeB.get(), L"'nodeB' is null.");
		Assert::IsNotNull(nodeB->next.get(), L"'nodeB' next is null.");
		Assert::AreEqual(nodeC, nodeB->next, L"'nodeB' next is not 'nodeC'");

		Assert::IsNotNull(nodeC.get(), L"'nodeC' is null.");
		Assert::IsNull(nodeC->next.get(), L"'nodeC' next is not null.");
	}

	TEST_METHOD(AddEdge_NodeValue)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);

		graph->addEdge(10, 20, 20);
		graph->addEdge(20, 30, 10);

		Assert::AreEqual(nodeB, nodeA->edges.front()->reference->getToNode(nodeA), L"'nodeA' should be connected to 'nodeB'");
		Assert::AreEqual(nodeC, nodeB->edges.front()->reference->getToNode(nodeB), L"'nodeB' should be connected to 'nodeC'");
	}

	TEST_METHOD(AddEdge_ValidInput_NodeReference)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);

		graph->addEdge(nodeA, nodeB, 20);
		graph->addEdge(nodeB, nodeC, 10);

		Assert::AreEqual(nodeB, nodeA->edges.front()->reference->getToNode(nodeA), L"'nodeA' should be connected to 'nodeB'");
		Assert::AreEqual(nodeC, nodeB->edges.front()->reference->getToNode(nodeB), L"'nodeB' should be connected to 'nodeC'");
	}

	TEST_METHOD(AddEdge_InvalidInput_Fails)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		bool passed = false;

		try
		{
			graph->addEdge(nullptr, nodeB, 20);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
		passed = false;

		try
		{
			graph->addEdge(nodeB, nullptr, 10);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
		passed = false;

		try
		{
			graph->addEdge(nullptr, nullptr, 10);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
	}

	TEST_METHOD(CountNodes)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		
		Assert::AreEqual((size_t)0, graph->countNodes(), L"There should be 0 nodes in the graph.");

		graph->addNode(10);

		Assert::AreEqual((size_t)1, graph->countNodes(), L"There should be 1 node in the graph.");
		
		graph->addNode(20);

		Assert::AreEqual((size_t)2, graph->countNodes(), L"There should be 2 nodes in the graph.");
		
		graph->addNode(30);

		Assert::AreEqual((size_t)3, graph->countNodes(), L"There should be 3 nodes in the graph.");
	}

	TEST_METHOD(IsPath_NodeValue)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		shared_ptr<UnweightedGraphNode> nodeD = graph->addNode(40);
		shared_ptr<UnweightedGraphNode> nodeE = graph->addNode(50);
		shared_ptr<UnweightedGraphNode> nodeF = graph->addNode(60);
		shared_ptr<UnweightedGraphNode> nodeG = graph->addNode(70);
		shared_ptr<UnweightedGraphNode> nodeH = graph->addNode(80);
		shared_ptr<UnweightedGraphNode> nodeI = graph->addNode(90);
		shared_ptr<UnweightedGraphNode> nodeJ = graph->addNode(1);

		graph->addEdge(nodeA, nodeB, 20);
		graph->addEdge(nodeB, nodeC, 10);
		graph->addEdge(nodeC, nodeD, 10);
		graph->addEdge(nodeD, nodeE, 10);
		graph->addEdge(nodeE, nodeF, 10);
		graph->addEdge(nodeF, nodeG, 10);
		graph->addEdge(nodeG, nodeH, 10);
		graph->addEdge(nodeH, nodeC, 10);
		graph->addEdge(nodeA, nodeI, 10);

		Assert::IsTrue(graph->isPath(10, 60), L"There should exist a path between '10' and '60'");
		Assert::IsTrue(graph->isPath(80, 30), L"There should exist a path between '80' and '30'");
		Assert::IsTrue(graph->isPath(20, 70), L"There should exist a path between '20' and '70'");
		Assert::IsTrue(graph->isPath(10, 90), L"There should exist a path between '10' and '90'");
		Assert::IsTrue(graph->isPath(90, 80), L"There should exist a path between '90' and '80'");

		Assert::IsFalse(graph->isPath(20, 1), L"There should not exist a path between '20' and '1'");
		Assert::IsFalse(graph->isPath(1, 70), L"There should not exist a path between '1' and '70'");
	}

	TEST_METHOD(IsPath_ValidInput_NodeReference)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		shared_ptr<UnweightedGraphNode> nodeD = graph->addNode(40);
		shared_ptr<UnweightedGraphNode> nodeE = graph->addNode(50);
		shared_ptr<UnweightedGraphNode> nodeF = graph->addNode(60);
		shared_ptr<UnweightedGraphNode> nodeG = graph->addNode(70);
		shared_ptr<UnweightedGraphNode> nodeH = graph->addNode(80);
		shared_ptr<UnweightedGraphNode> nodeI = graph->addNode(90);
		shared_ptr<UnweightedGraphNode> nodeJ = graph->addNode(1);

		graph->addEdge(nodeA, nodeB, 20);
		graph->addEdge(nodeB, nodeC, 10);
		graph->addEdge(nodeC, nodeD, 10);
		graph->addEdge(nodeD, nodeE, 10);
		graph->addEdge(nodeE, nodeF, 10);
		graph->addEdge(nodeF, nodeG, 10);
		graph->addEdge(nodeG, nodeH, 10);
		graph->addEdge(nodeH, nodeC, 10);
		graph->addEdge(nodeA, nodeI, 10);

		Assert::IsTrue(graph->isPath(nodeA, nodeF), L"There should exist a path between 'nodeA' and 'nodeF'");
		Assert::IsTrue(graph->isPath(nodeH, nodeC), L"There should exist a path between 'nodeH' and 'nodeC'");
		Assert::IsTrue(graph->isPath(nodeB, nodeG), L"There should exist a path between 'nodeB' and 'nodeG'");
		Assert::IsTrue(graph->isPath(nodeA, nodeI), L"There should exist a path between 'nodeA' and 'nodeI'");
		Assert::IsTrue(graph->isPath(nodeI, nodeH), L"There should exist a path between 'nodeI' and 'nodeH'");

		Assert::IsFalse(graph->isPath(nodeB, nodeJ), L"There should not exist a path between 'nodeB' and 'nodeJ'");
		Assert::IsFalse(graph->isPath(nodeJ, nodeG), L"There should not exist a path between 'nodeJ' and 'nodeG'");
	}

	TEST_METHOD(IsPath_InvalidInput_NodeReference)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		bool passed = false;

		try
		{
			graph->isPath(nullptr, nodeA);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
		passed = false;

		try
		{
			graph->isPath(nodeA, nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
		passed = false;

		try
		{
			graph->isPath(nullptr, nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
	}

	TEST_METHOD(FindNode)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		shared_ptr<UnweightedGraphNode> nodeD = graph->addNode(40);

		shared_ptr<UnweightedGraphNode> result = graph->findNode(10);

		Assert::IsNotNull(result.get(), L"'result' should not be null.");

		result = graph->findNode(40);

		Assert::IsNotNull(result.get(), L"'result' should not be null.");

		result = graph->findNode(400);

		Assert::IsNull(result.get(), L"'result' should be null.");
	}

	TEST_METHOD(IsConnected)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		shared_ptr<UnweightedGraphNode> nodeD = graph->addNode(40);
		shared_ptr<UnweightedGraphNode> nodeE = graph->addNode(50);
		shared_ptr<UnweightedGraphNode> nodeF = graph->addNode(60);
		shared_ptr<UnweightedGraphNode> nodeG = graph->addNode(70);
		shared_ptr<UnweightedGraphNode> nodeH = graph->addNode(80);
		shared_ptr<UnweightedGraphNode> nodeI = graph->addNode(90);
		shared_ptr<UnweightedGraphNode> nodeJ = graph->addNode(1);

		graph->addEdge(nodeA, nodeB, 20);
		graph->addEdge(nodeB, nodeC, 10);
		graph->addEdge(nodeC, nodeD, 10);
		graph->addEdge(nodeD, nodeE, 10);
		graph->addEdge(nodeE, nodeF, 10);
		graph->addEdge(nodeF, nodeG, 10);
		graph->addEdge(nodeG, nodeH, 10);
		graph->addEdge(nodeH, nodeC, 10);
		graph->addEdge(nodeA, nodeI, 10);

		Assert::IsFalse(graph->isConnected(), L"The graph should not be connected.");

		graph->addEdge(nodeJ, nodeI, 30);

		Assert::IsTrue(graph->isConnected(), L"The graph should be connected.");
	}

	TEST_METHOD(DijkstraPath_NodeValue)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		shared_ptr<UnweightedGraphNode> nodeD = graph->addNode(40);
		shared_ptr<UnweightedGraphNode> nodeE = graph->addNode(50);
		shared_ptr<UnweightedGraphNode> nodeF = graph->addNode(60);
		shared_ptr<UnweightedGraphNode> nodeG = graph->addNode(70);
		shared_ptr<UnweightedGraphNode> nodeH = graph->addNode(80);
		shared_ptr<UnweightedGraphNode> nodeI = graph->addNode(90);
		shared_ptr<UnweightedGraphNode> nodeJ = graph->addNode(1);

		graph->addEdge(nodeA, nodeB, 20);
		graph->addEdge(nodeB, nodeC, 10);
		graph->addEdge(nodeC, nodeD, 10);
		graph->addEdge(nodeD, nodeE, 10);
		graph->addEdge(nodeE, nodeF, 10);
		graph->addEdge(nodeF, nodeG, 10);
		graph->addEdge(nodeG, nodeH, 10);
		graph->addEdge(nodeH, nodeC, 10);
		graph->addEdge(nodeA, nodeI, 10);

		Assert::IsTrue(graph->dijkstraPath(10, 60), L"There should exist a path between '10' and '60'");
		Assert::IsTrue(graph->dijkstraPath(80, 30), L"There should exist a path between '80' and '30'");
		Assert::IsTrue(graph->dijkstraPath(20, 70), L"There should exist a path between '20' and '70'");
		Assert::IsTrue(graph->dijkstraPath(10, 90), L"There should exist a path between '10' and '90'");
		Assert::IsTrue(graph->dijkstraPath(90, 80), L"There should exist a path between '90' and '80'");

		Assert::IsFalse(graph->dijkstraPath(20, 1), L"There should not exist a path between '20' and '1'");
		Assert::IsFalse(graph->dijkstraPath(1, 70), L"There should not exist a path between '1' and '70'");
	}

	TEST_METHOD(DijkstraPath_ValidInput_NodeReference)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		shared_ptr<UnweightedGraphNode> nodeB = graph->addNode(20);
		shared_ptr<UnweightedGraphNode> nodeC = graph->addNode(30);
		shared_ptr<UnweightedGraphNode> nodeD = graph->addNode(40);
		shared_ptr<UnweightedGraphNode> nodeE = graph->addNode(50);
		shared_ptr<UnweightedGraphNode> nodeF = graph->addNode(60);
		shared_ptr<UnweightedGraphNode> nodeG = graph->addNode(70);
		shared_ptr<UnweightedGraphNode> nodeH = graph->addNode(80);
		shared_ptr<UnweightedGraphNode> nodeI = graph->addNode(90);
		shared_ptr<UnweightedGraphNode> nodeJ = graph->addNode(1);

		graph->addEdge(nodeA, nodeB, 20);
		graph->addEdge(nodeB, nodeC, 10);
		graph->addEdge(nodeC, nodeD, 10);
		graph->addEdge(nodeD, nodeE, 10);
		graph->addEdge(nodeE, nodeF, 10);
		graph->addEdge(nodeF, nodeG, 10);
		graph->addEdge(nodeG, nodeH, 10);
		graph->addEdge(nodeH, nodeC, 10);
		graph->addEdge(nodeA, nodeI, 10);

		Assert::IsTrue(graph->dijkstraPath(nodeA, nodeF), L"There should exist a path between 'nodeA' and 'nodeF'");
		Assert::IsTrue(graph->dijkstraPath(nodeH, nodeC), L"There should exist a path between 'nodeH' and 'nodeC'");
		Assert::IsTrue(graph->dijkstraPath(nodeB, nodeG), L"There should exist a path between 'nodeB' and 'nodeG'");
		Assert::IsTrue(graph->dijkstraPath(nodeA, nodeI), L"There should exist a path between 'nodeA' and 'nodeI'");
		Assert::IsTrue(graph->dijkstraPath(nodeI, nodeH), L"There should exist a path between 'nodeI' and 'nodeH'");

		Assert::IsFalse(graph->dijkstraPath(nodeB, nodeJ), L"There should not exist a path between 'nodeB' and 'nodeJ'");
		Assert::IsFalse(graph->dijkstraPath(nodeJ, nodeG), L"There should not exist a path between 'nodeJ' and 'nodeG'");
	}

	TEST_METHOD(DijkstraPath_InvalidInput_NodeReference)
	{
		unique_ptr<UnweightedGraph> graph = make_unique<UnweightedGraph>();
		shared_ptr<UnweightedGraphNode> nodeA = graph->addNode(10);
		bool passed = false;

		try
		{
			graph->dijkstraPath(nullptr, nodeA);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
		passed = false;

		try
		{
			graph->dijkstraPath(nodeA, nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
		passed = false;

		try
		{
			graph->dijkstraPath(nullptr, nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
	}
};