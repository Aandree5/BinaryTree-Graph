#include "CppUnitTest.h"
#include "TestsHelper.h"
#include "../BinaryTree.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(BinaryTreeTests)
{

public:
	TEST_METHOD(Constructor)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();

		Assert::IsNotNull(tree.get(), L"Tree wasn't created.");
	}

	TEST_METHOD(CreatedTree_CheckPropertiesValues)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();

		Assert::IsNull(tree->root.get(), L"Root should be null.");
	}

	TEST_METHOD(Insert_ValidInput_AddsNode)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();


		/*                  T                   */

		shared_ptr<BinaryTreeNode> T = tree->insert("T");

		Assert::IsNotNull(T.get(), L"Insert didn't return the new node 'T'.");
		Assert::AreEqual((string)"T", T->value, L"'T' doens't have the right value.");

		Assert::IsNotNull(tree->root.get(), L"'Root' is null.");


		/*                  T                  
							  \
								U				*/

		shared_ptr<BinaryTreeNode> U = tree->insert("U");

		Assert::IsNotNull(U.get(), L"Insert didn't return the new node 'U'.");
		Assert::AreEqual((string)"U", U->value, L"'U' doens't have the right value.");

		Assert::AreEqual(T->value, tree->root->value, L"Wrong 'root' value.");
		Assert::AreEqual(U->value, tree->root->right->value, L"Wrong right node of 'root'.");


		/*                  U                  
						   /  \
						  T	   V				*/

		shared_ptr<BinaryTreeNode> V = tree->insert("V");

		Assert::IsNotNull(V.get(), L"Insert didn't return the new node 'V'.");
		Assert::AreEqual((string)"V", V->value, L"'V' doens't have the right value.");

		Assert::AreEqual(U->value, tree->root->value, L"Wrong 'root' value.");
		Assert::AreEqual(T->value, tree->root->left->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(V->value, tree->root->right->value,L"Wrong right node of 'root'.");


		/*                  U                  
						   /  \
						  T	   V
						/
					  G							*/

		shared_ptr<BinaryTreeNode> G = tree->insert("G");

		Assert::IsNotNull(G.get(), L"Insert didn't return the new node 'G'.");
		Assert::AreEqual((string)"G", G->value, L"'G' doens't have the right value.");

		Assert::AreEqual(U->value, tree->root->value, L"Wrong 'root' value.");
		Assert::AreEqual(T->value, tree->root->left->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(V->value, tree->root->right->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(G->value, T->left->value, L"Wrong left node of 'T'.");


		/*                  U                  
						   /  \
						  G	   V
						/  \
					  F		T					*/

		shared_ptr<BinaryTreeNode> F = tree->insert("F");

		Assert::IsNotNull(F.get(), L"Insert didn't return the new node 'F'.");
		Assert::AreEqual((string)"F", F->value, L"'F' doens't have the right value.");

		Assert::AreEqual(U->value, tree->root->value, L"Wrong 'root' value.");
		Assert::AreEqual(G->value, tree->root->left->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(V->value, tree->root->right->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(F->value, G->left->value, L"Wrong left node of 'G'.");
		Assert::AreEqual(T->value, G->right->value, L"Wrong right node of 'G'.");


		/*                  G                  
						   /  \
						  F	   U
						/     / \
					  E		 T   V				 */

		shared_ptr<BinaryTreeNode> E = tree->insert("E");

		Assert::IsNotNull(E.get(), L"Insert didn't return the new node 'E'.");
		Assert::AreEqual((string)"E", E->value, L"'E' doens't have the right value.");

		Assert::AreEqual(G->value, tree->root->value, L"Wrong 'root' value.");
		Assert::AreEqual(F->value, tree->root->left->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(U->value, tree->root->right->value, L"Wrong right node of 'root'.");
		Assert::AreEqual(T->value, U->left->value, L"Wrong left node of 'U'.");
		Assert::AreEqual(V->value, U->right->value, L"Wrong right node of 'U'.");
		Assert::AreEqual(E->value, F->left->value, L"Wrong right node of 'F'.");
	}

	TEST_METHOD(Insert_ValidInput_IncreasesFrequency)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();

		// 1
		shared_ptr<BinaryTreeNode> T = tree->insert("T");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> G = tree->insert("G");
		shared_ptr<BinaryTreeNode> A = tree->insert("A");
		shared_ptr<BinaryTreeNode> Y = tree->insert("Y");
		shared_ptr<BinaryTreeNode> B = tree->insert("B");

		// 2
		tree->insert("F");

		// 3
		tree->insert("G");
		tree->insert("G");

		// 4
		tree->insert("B");
		tree->insert("B");
		tree->insert("B");

		// 5
		tree->insert("Y");
		tree->insert("Y");
		tree->insert("Y");
		tree->insert("Y");

		Assert::AreEqual(1, T->frequency, L"'T' has the wrong frequency.");
		Assert::AreEqual(2, F->frequency, L"'F' has the wrong frequency.");
		Assert::AreEqual(3, G->frequency, L"'G' has the wrong frequency.");
		Assert::AreEqual(1, A->frequency, L"'A' has the wrong frequency.");
		Assert::AreEqual(5, Y->frequency, L"'Y' has the wrong frequency.");
		Assert::AreEqual(4, B->frequency, L"'B' has the wrong frequency.");
	}

	TEST_METHOD(Insert_InvalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		string test;
		bool passed = false;

		try
		{
			tree->insert(test);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument exception not thrown.");
	}
};