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

	TEST_METHOD(Insert_ValidInput_IncreasesDepth)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();

		shared_ptr<BinaryTreeNode> T = tree->insert("T");
		shared_ptr<BinaryTreeNode> U = tree->insert("U");
		shared_ptr<BinaryTreeNode> V = tree->insert("V");
		shared_ptr<BinaryTreeNode> G = tree->insert("G");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> E = tree->insert("E");
		shared_ptr<BinaryTreeNode> H = tree->insert("H");


		/*          G
				   /  \
				  F	   U
				/     / \
			  E		 T   V
					/
				  H					*/

		Assert::AreEqual(1, H->depth, L"'H' wrong depth.");
		Assert::AreEqual(1, E->depth, L"'E' wrong depth.");
		Assert::AreEqual(2, T->depth, L"'T' wrong depth.");
		Assert::AreEqual(1, V->depth, L"'V' wrong depth.");
		Assert::AreEqual(2, F->depth, L"'F' wrong depth.");
		Assert::AreEqual(3, U->depth, L"'U' wrong depth.");
		Assert::AreEqual(4, G->depth, L"'G' wrong depth.");
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

	TEST_METHOD(CheckBalance_InvalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		bool passed = false;

		try
		{
			tree->checkBalance(tree->root);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Root is nullptr, should throw invalid argument.");
	}

	TEST_METHOD(CheckBalance_NoChildren_ReturnBalanced)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> node = make_shared<BinaryTreeNode>("Node");

		Assert::AreEqual(0, tree->checkBalance(node), L"No children should return 0 for balanced.");
	}

	TEST_METHOD(CheckBalance_OneChildLeft_LeftHeavy)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> node = make_shared<BinaryTreeNode>("Node");
		node->left = make_shared<BinaryTreeNode>("Left");

		Assert::AreEqual(-1, tree->checkBalance(node), L"Only has left child should return -1 for left heavy.");
	}

	TEST_METHOD(CheckBalance_OneChildRight_RightHeavy)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> node = make_shared<BinaryTreeNode>("Node");
		node->right = make_shared<BinaryTreeNode>("Right");

		Assert::AreEqual(1, tree->checkBalance(node), L"Only has right child should return 1 for right heavy.");
	}

	TEST_METHOD(CheckBalance_BothChildren_ReturnBalanced)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> node = make_shared<BinaryTreeNode>("Node");
		node->left = make_shared<BinaryTreeNode>("Left");
		node->right = make_shared<BinaryTreeNode>("Right");

		Assert::AreEqual(0, tree->checkBalance(node), L"Has both children should return 0 for balanced.");
	}

	TEST_METHOD(CheckBalance_LeftHeavy)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> node = make_shared<BinaryTreeNode>("Node");
		node->left = make_shared<BinaryTreeNode>("Left");
		node->left->left = make_shared<BinaryTreeNode>("LeftLeft");
		node->left->depth = 2;

		Assert::AreEqual(-2, tree->checkBalance(node), L"Is left heavy.");
	}

	TEST_METHOD(CheckBalance_RightHeavy)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> node = make_shared<BinaryTreeNode>("Node");
		node->right = make_shared<BinaryTreeNode>("Right");
		node->right->right = make_shared<BinaryTreeNode>("Right");
		node->right->depth = 2;

		Assert::AreEqual(2, tree->checkBalance(node), L"Is right heavy.");
	}

	TEST_METHOD(GetCorrectDepth_CheckResults)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();

		shared_ptr<BinaryTreeNode> T = tree->insert("T");
		shared_ptr<BinaryTreeNode> U = tree->insert("U");
		shared_ptr<BinaryTreeNode> V = tree->insert("V");
		shared_ptr<BinaryTreeNode> G = tree->insert("G");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> E = tree->insert("E");
		shared_ptr<BinaryTreeNode> H = tree->insert("H");


		/*          G
				   /  \
				  F	   U
				/     / \
			  E		 T   V
					/
				  H					*/

		Assert::AreEqual(1, tree->getCorrectDepth(H), L"'H' wrong depth.");
		Assert::AreEqual(1, tree->getCorrectDepth(E), L"'E' wrong depth.");
		Assert::AreEqual(2, tree->getCorrectDepth(T), L"'T' wrong depth.");
		Assert::AreEqual(1, tree->getCorrectDepth(V), L"'V' wrong depth.");
		Assert::AreEqual(2, tree->getCorrectDepth(F), L"'F' wrong depth.");
		Assert::AreEqual(3, tree->getCorrectDepth(U), L"'U' wrong depth.");
		Assert::AreEqual(4, tree->getCorrectDepth(G), L"'G' wrong depth.");
	}

	TEST_METHOD(GetCorrectDepth_InvalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		bool passed = false;

		try 
		{
			tree->getCorrectDepth(nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument not thrown.");
	}

	TEST_METHOD(BalanceTree_InvalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		bool passed = false;

		try
		{
			tree->balanceTree(nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument not thrown.");
	}

	TEST_METHOD(BalanceTree_ValidInput_NoChildren)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> T = make_shared<BinaryTreeNode>("T");

		tree->balanceTree(T);

		Assert::IsNull(T->left.get(), L"'T' left should be null.");
		Assert::IsNull(T->right.get(), L"'T' right should be null.");
	}

	TEST_METHOD(BalanceTree_ValidInput_OneChildLeft)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> T = make_shared<BinaryTreeNode>("T");
		shared_ptr<BinaryTreeNode> M = make_shared<BinaryTreeNode>("M");
		T->left = M;
		M->parent = T;

		tree->balanceTree(M);

		Assert::AreEqual(M, T->left, L"'T' left should be 'M'.");
		Assert::IsNull(T->right.get(), L"'T' right should be null.");

		Assert::AreEqual(T, M->parent.lock(), L"'M' parent should be 'T'.");
		Assert::IsNull(M->left.get(), L"'M' left should be null.");
		Assert::IsNull(M->right.get(), L"'M' right should be null.");
	}

	TEST_METHOD(BalanceTree_ValidInput_OneChildRight)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> T = make_shared<BinaryTreeNode>("T");
		shared_ptr<BinaryTreeNode> X = make_shared<BinaryTreeNode>("X");
		T->right = X;
		X->parent = T;

		tree->balanceTree(X);

		Assert::IsNull(T->left.get(), L"'T' left should be null.");
		Assert::AreEqual(X, T->right, L"'T' right should be 'X'.");

		Assert::AreEqual(T, X->parent.lock(), L"'X' parent should be 'T'.");
		Assert::IsNull(X->left.get(), L"'X' left should be null.");
		Assert::IsNull(X->right.get(), L"'X' right should be null.");
	}

	TEST_METHOD(BalanceTree_ValidInput_Balanced)
	{
		/* Balanced 1
				    T	 	 ->        T
				  /   \	 	 ->      /   \
				 M     X	 ->     M     X		*/

		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> T = make_shared<BinaryTreeNode>("T");
		shared_ptr<BinaryTreeNode> M = make_shared<BinaryTreeNode>("M");
		shared_ptr<BinaryTreeNode> X = make_shared<BinaryTreeNode>("X");
		T->left = M;
		M->parent = T;
		T->right = X;
		X->parent = T;

		tree->balanceTree(X);

		Assert::AreEqual(M, T->left, L"'T' left should be 'M' (Balanced 1).");
		Assert::AreEqual(X, T->right, L"'T' right should be 'X' (Balanced 1).");

		Assert::AreEqual(T, M->parent.lock(), L"'M' parent should be 'T' (Balanced 1).");
		Assert::IsNull(M->left.get(), L"'M' left should be null (Balanced 1).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Balanced 1).");

		Assert::AreEqual(T, X->parent.lock(), L"'X' parent should be 'T' (Balanced 1).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Balanced 1).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Balanced 1).");

		/* Balanced 2
					T	 	 ->            T
				  /   \	 	 ->          /   \
				 M     X	 ->         M     X		
				/			 -> 	   /
			   I			 -> 	  I					*/

		shared_ptr<BinaryTreeNode> I = make_shared<BinaryTreeNode>("I");
		M->left = I;
		I->parent = M;

		tree->balanceTree(I);

		Assert::AreEqual(M, T->left, L"'T' left should be 'M' (Balanced 2).");
		Assert::AreEqual(X, T->right, L"'T' right should be 'X' (Balanced 2).");

		Assert::AreEqual(T, M->parent.lock(), L"'M' parent should be 'T' (Balanced 2).");
		Assert::AreEqual(I, M->left, L"'M' left should be 'I' (Balanced 2).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Balanced 2).");

		Assert::AreEqual(T, X->parent.lock(), L"'X' parent should be 'T' (Balanced 2).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Balanced 2).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Balanced 2).");

		Assert::AreEqual(M, I->parent.lock(), L"'I' parent should be 'M' (Balanced 2).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Balanced 2).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Balanced 2).");

		/* Balanced 3	
					T	 	 ->            T
				  /   \	 	 ->          /   \
				 M     X	 ->         M     X
				/	  / 	 -> 	   /	 /
			   I	 U		 -> 	  I		U			*/

		shared_ptr<BinaryTreeNode> U = make_shared<BinaryTreeNode>("U");
		X->left = U;
		U->parent = X;

		tree->balanceTree(U);

		Assert::AreEqual(M, T->left, L"'T' left should be 'M' (Balanced 3).");
		Assert::AreEqual(X, T->right, L"'T' right should be 'X' (Balanced 3).");

		Assert::AreEqual(T, M->parent.lock(), L"'M' parent should be 'T' (Balanced 3).");
		Assert::AreEqual(I, M->left, L"'M' left should be 'I' (Balanced 3).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Balanced 3).");

		Assert::AreEqual(T, X->parent.lock(), L"'X' parent should be 'T' (Balanced 3).");
		Assert::AreEqual(U, X->left, L"'X' left should be 'U' (Balanced 3).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Balanced 3).");

		Assert::AreEqual(M, I->parent.lock(), L"'I' parent should be 'M' (Balanced 3).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Balanced 3).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Balanced 3).");

		Assert::AreEqual(X, U->parent.lock(), L"'U' parent should be 'X' (Balanced 3).");
		Assert::IsNull(U->left.get(), L"'U' left should be null (Balanced 3).");
		Assert::IsNull(U->right.get(), L"'U' right should be null (Balanced 3).");

		/* Left Right Heavy
				    T	 	 ->            T
				  /   \	 	 ->          /   \
				 M     X	 ->         M     V
				/	  / 	 -> 	   /	 / \
			   I	 U		 -> 	  I		U   X
					  \		 ->			   
					   V     ->							*/

		shared_ptr<BinaryTreeNode> V = make_shared<BinaryTreeNode>("V");
		U->right = V;
		V->parent = U;

		tree->balanceTree(V);

		Assert::AreEqual(M, T->left, L"'T' left should be 'M' (Left Right Heavy).");
		Assert::AreEqual(V, T->right, L"'T' right should be 'V' (Left Right Heavy).");

		Assert::AreEqual(T, M->parent.lock(), L"'M' parent should be 'T' (Left Right Heavy).");
		Assert::AreEqual(I, M->left, L"'M' left should be 'I' (Left Right Heavy).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Left Right Heavy).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Left Right Heavy).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Left Right Heavy).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Left Right Heavy).");

		Assert::AreEqual(M, I->parent.lock(), L"'I' parent should be 'M' (Left Right Heavy).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Left Right Heavy).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Left Right Heavy).");

		Assert::AreEqual(V, U->parent.lock(), L"'U' parent should be 'X' (Left Right Heavy).");
		Assert::IsNull(U->left.get(), L"'U' left should be null (Left Right Heavy).");
		Assert::IsNull(U->right.get(), L"'U' right should be null (Left Right Heavy).");

		Assert::AreEqual(T, V->parent.lock(), L"'V' parent should be 'T' (Left Right Heavy).");
		Assert::AreEqual(U, V->left, L"'V' left should be 'U' (Left Right Heavy).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Left Right Heavy).");

		/* Left Left Heavy
					T	 	 ->            T
				  /   \	 	 ->          /   \
				 M     V	 ->         I     V
				/	  / \	 -> 	   / \	 / \
			   I	 U   X	 -> 	  H	  M	U   X
			  /		  		 ->
			 H		         ->							*/

		shared_ptr<BinaryTreeNode> H = make_shared<BinaryTreeNode>("H");
		I->left = H;
		H->parent = I;

		tree->balanceTree(H);

		Assert::AreEqual(I, T->left, L"'T' left should be 'I' (Left Left Heavy).");
		Assert::AreEqual(V, T->right, L"'T' right should be 'V' (Left Left Heavy).");

		Assert::AreEqual(I, M->parent.lock(), L"'M' parent should be 'I' (Left Left Heavy).");
		Assert::IsNull(M->left.get(), L"'M' left should be null (Left Left Heavy).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Left Left Heavy).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Left Left Heavy).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Left Left Heavy).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Left Left Heavy).");

		Assert::AreEqual(T, I->parent.lock(), L"'I' parent should be 'T' (Left Left Heavy).");
		Assert::AreEqual(H, I->left, L"'I' left should be 'H' (Left Left Heavy).");
		Assert::AreEqual(M, I->right, L"'I' right should be 'M' (Left Left Heavy).");

		Assert::AreEqual(V, U->parent.lock(), L"'U' parent should be 'X' (Left Left Heavy).");
		Assert::IsNull(U->left.get(), L"'U' left should be null (Left Left Heavy).");
		Assert::IsNull(U->right.get(), L"'U' right should be null (Left Left Heavy).");

		Assert::AreEqual(T, V->parent.lock(), L"'V' parent should be 'T' (Left Left Heavy).");
		Assert::AreEqual(U, V->left, L"'V' left should be 'U' (Left Left Heavy).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Left Left Heavy).");

		Assert::AreEqual(I, H->parent.lock(), L"'H' parent should be 'I' (Left Left Heavy).");
		Assert::IsNull(H->left.get(), L"'H' left should be null (Left Left Heavy).");
		Assert::IsNull(H->right.get(), L"'H' right should be null (Left Left Heavy).");

		/* Right Left Heavy
					T	 	 ->            T
				  /   \	 	 ->          /   \
				 I     V	 ->         I     V
				/ \	  / \	 -> 	   / \	 / \
			   H   M U   X	 -> 	  H	  O	U   X
			 	    \  		 ->			 / \
			 	     P       ->			M   P				
				    /		 ->
				   O		 ->							*/
					
		shared_ptr<BinaryTreeNode> P = make_shared<BinaryTreeNode>("P");
		shared_ptr<BinaryTreeNode> O = make_shared<BinaryTreeNode>("O");
		M->right = P;
		P->parent = M;
		P->left = O;
		O->parent = P;

		tree->balanceTree(O);

		Assert::AreEqual(I, T->left, L"'T' left should be 'I' (Right Left Heavy).");
		Assert::AreEqual(V, T->right, L"'T' right should be 'V' (Right Left Heavy).");

		Assert::AreEqual(O, M->parent.lock(), L"'M' parent should be 'O' (Right Left Heavy).");
		Assert::IsNull(M->left.get(), L"'M' left should be null (Right Left Heavy).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Right Left Heavy).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Right Left Heavy).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Right Left Heavy).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Right Left Heavy).");

		Assert::AreEqual(T, I->parent.lock(), L"'I' parent should be 'T' (Left Left Heavy).");
		Assert::AreEqual(H, I->left, L"'I' left should be 'H' (Right Left Heavy).");
		Assert::AreEqual(O, I->right, L"'I' right should be O' (Right Left Heavy).");

		Assert::AreEqual(V, U->parent.lock(), L"'U' parent should be 'X' (Right Left Heavy).");
		Assert::IsNull(U->left.get(), L"'U' left should be null (Right Left Heavy).");
		Assert::IsNull(U->right.get(), L"'U' right should be null (Right Left Heavy).");

		Assert::AreEqual(T, V->parent.lock(), L"'V' parent should be 'T' (Right Left Heavy).");
		Assert::AreEqual(U, V->left, L"'V' left should be 'U' (Right Left Heavy).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Right Left Heavy).");

		Assert::AreEqual(I, H->parent.lock(), L"'H' parent should be 'I' (Right Left Heavy).");
		Assert::IsNull(H->left.get(), L"'H' left should be null (Right Left Heavy).");
		Assert::IsNull(H->right.get(), L"'H' right should be null (Right Left Heavy).");

		Assert::AreEqual(O, P->parent.lock(), L"'P' parent should be 'L' (Right Left Heavy).");
		Assert::IsNull(P->left.get(), L"'P' left should be null (Right Left Heavy).");
		Assert::IsNull(P->right.get(), L"'P' right should be null (Right Left Heavy).");

		Assert::AreEqual(I, O->parent.lock(), L"'O' parent should be 'I' (Right Left Heavy).");
		Assert::AreEqual(M, O->left, L"'O' left should be 'M' (Right Left Heavy).");
		Assert::AreEqual(P, O->right, L"'O' right should be 'P' (Right Left Heavy).");

		/* Right Right Heavy
					T	 		->            T
				  /   \	 		->          /   \
				 I     V		->         I     V
				/ \	  / \		-> 		  / \   / \
			   H   O U   X		-> 	     H	 O U   Y
				  / \ 	  \		->			/ \   / \
				 M   P     Y	->			M  P X   Z
				  			\	->
							 Z	->							*/
					
		shared_ptr<BinaryTreeNode> Y= make_shared<BinaryTreeNode>("Y");
		shared_ptr<BinaryTreeNode> Z = make_shared<BinaryTreeNode>("Z");
		X->right = Y;
		Y->parent = X;
		Y->right = Z;
		Z->parent = Y;

		tree->balanceTree(Z);

		Assert::AreEqual(I, T->left, L"'T' left should be 'I' (Right Right Heavy).");
		Assert::AreEqual(V, T->right, L"'T' right should be 'V' (Right Right Heavy).");

		Assert::AreEqual(O, M->parent.lock(), L"'M' parent should be 'O' (Right Right Heavy).");
		Assert::IsNull(M->left.get(), L"'M' left should be null (Right Right Heavy).");
		Assert::IsNull(M->right.get(), L"'M' right should be null (Right Right Heavy).");

		Assert::AreEqual(Y, X->parent.lock(), L"'X' parent should be 'Y' (Right Right Heavy).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Right Right Heavy).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Right Right Heavy).");

		Assert::AreEqual(T, I->parent.lock(), L"'I' parent should be 'T' (Left Left Heavy).");
		Assert::AreEqual(H, I->left, L"'I' left should be 'H' (Right Right Heavy).");
		Assert::AreEqual(O, I->right, L"'I' right should be O' (Right Right Heavy).");

		Assert::AreEqual(V, U->parent.lock(), L"'U' parent should be 'X' (Right Right Heavy).");
		Assert::IsNull(U->left.get(), L"'U' left should be null (Right Right Heavy).");
		Assert::IsNull(U->right.get(), L"'U' right should be null (Right Right Heavy).");

		Assert::AreEqual(T, V->parent.lock(), L"'V' parent should be 'T' (Right Right Heavy).");
		Assert::AreEqual(U, V->left, L"'V' left should be 'U' (Right Right Heavy).");
		Assert::AreEqual(Y, V->right, L"'V' right should be 'Y' (Right Right Heavy).");

		Assert::AreEqual(I, H->parent.lock(), L"'H' parent should be 'I' (Right Right Heavy).");
		Assert::IsNull(H->left.get(), L"'H' left should be null (Right Right Heavy).");
		Assert::IsNull(H->right.get(), L"'H' right should be null (Right Right Heavy).");

		Assert::AreEqual(O, P->parent.lock(), L"'P' parent should be 'L' (Right Right Heavy).");
		Assert::IsNull(P->left.get(), L"'P' left should be null (Right Right Heavy).");
		Assert::IsNull(P->right.get(), L"'P' right should be null (Right Right Heavy).");

		Assert::AreEqual(I, O->parent.lock(), L"'O' parent should be 'I' (Right Right Heavy).");
		Assert::AreEqual(M, O->left, L"'O' left should be 'M' (Right Right Heavy).");
		Assert::AreEqual(P, O->right, L"'O' right should be 'P' (Right Right Heavy).");

		Assert::AreEqual(V, Y->parent.lock(), L"'Y' parent should be 'V' (Right Right Heavy).");
		Assert::AreEqual(X, Y->left, L"'Y' left should be 'X' (Right Right Heavy).");
		Assert::AreEqual(Z, Y->right, L"'Y' right should be 'Z' (Right Right Heavy).");

		Assert::AreEqual(Y, Z->parent.lock(), L"'Z' parent should be 'Y' (Right Right Heavy).");
		Assert::IsNull(Z->left.get(), L"'Z' left should be null (Right Right Heavy).");
		Assert::IsNull(Z->right.get(), L"'Z' right should be null (Right Right Heavy).");
	}

	TEST_METHOD(Find_InvalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		string test;
		bool passed = false;

		try
		{
			tree->find(test);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument not thrown.");
	}

	TEST_METHOD(Find_ValidInput_Exists)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> A = tree->insert("A");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> H = tree->insert("H");
		shared_ptr<BinaryTreeNode> B = tree->insert("B");
		shared_ptr<BinaryTreeNode> R = tree->insert("R");
		shared_ptr<BinaryTreeNode> T = tree->insert("T");
		shared_ptr<BinaryTreeNode> W = tree->insert("W");
		shared_ptr<BinaryTreeNode> K = tree->insert("K");

		shared_ptr<BinaryTreeNode> tester = tree->find("F");
		Assert::AreEqual(F, tester, L"Tester should be 'F'.");

		tester = tree->find("T");
		Assert::AreEqual(T, tester, L"Tester should be 'T'.");

		tester = tree->find("B");
		Assert::AreEqual(B, tester, L"Tester should be 'B'.");

		tester = tree->find("W");
		Assert::AreEqual(W, tester, L"Tester should be 'W'.");

		tester = tree->find("K");
		Assert::AreEqual(K, tester, L"Tester should be 'K'.");
	}

	TEST_METHOD(Find_ValidInput_NotExists)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> A = tree->insert("A");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> H = tree->insert("H");
		shared_ptr<BinaryTreeNode> B = tree->insert("B");
		shared_ptr<BinaryTreeNode> R = tree->insert("R");
		shared_ptr<BinaryTreeNode> T = tree->insert("T");
		shared_ptr<BinaryTreeNode> W = tree->insert("W");
		shared_ptr<BinaryTreeNode> K = tree->insert("K");

		shared_ptr<BinaryTreeNode> tester = tree->find("V");
		Assert::IsNull(tester.get(), L"Tester should be null (V).");

		tester = tree->find("D");
		Assert::IsNull(tester.get(), L"Tester should be null (D).");

		tester = tree->find("Z");
		Assert::IsNull(tester.get(), L"Tester should be null (Z).");

		tester = tree->find("E");
		Assert::IsNull(tester.get(), L"Tester should be null (E).");

		tester = tree->find("I");
		Assert::IsNull(tester.get(), L"Tester should be null (I).");
	}

	TEST_METHOD(RemoveByValue_InalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		string test;
		bool passed = false;

		try
		{
			tree->remove(test);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument not thrown.");
	}

	TEST_METHOD(RemoveByValue_ValidInput_NoExists)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> H = tree->insert("H");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");

		shared_ptr<BinaryTreeNode> removed = tree->remove("B");

		Assert::IsNull(removed.get(), L"Should return null.");
	}

	TEST_METHOD(RemoveByValue_ValidInput_CheckResults)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> H = tree->insert("H");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> L = tree->insert("L");
		shared_ptr<BinaryTreeNode> C = tree->insert("C");
		shared_ptr<BinaryTreeNode> G = tree->insert("G");
		shared_ptr<BinaryTreeNode> I = tree->insert("I");
		shared_ptr<BinaryTreeNode> V = tree->insert("V");
		shared_ptr<BinaryTreeNode> E = tree->insert("E");
		shared_ptr<BinaryTreeNode> J = tree->insert("J");
		shared_ptr<BinaryTreeNode> X = tree->insert("X");

		/* Remove Leaf
							 H					->			H
						   /   \				->		  /   \
						  F	    L				->		 F	   L
						 / \   / \				->		/ \	  / \
					    C	G I   V				->	   C   G I   V
						 \     \   \			->			  \   \
						  E     J   X			->			   J   X		*/

		shared_ptr<BinaryTreeNode> removed = tree->remove("E");

		Assert::AreEqual(E, removed, L"Node returned wasn't 'E' (Remove Leaf).");

		Assert::AreEqual(H, tree->root, L"The tree root should be 'H' (Remove Leaf).");

		Assert::IsNull(H->parent.lock().get(), L"'H' parent should be null (Remove Leaf).");
		Assert::AreEqual(F, H->left, L"'H' left should be 'F' (Remove Leaf).");
		Assert::AreEqual(L, H->right, L"'H' right should be 'L' (Remove Leaf).");

		Assert::AreEqual(H, F->parent.lock(), L"'F' parent should be 'H' (Remove Leaf).");
		Assert::AreEqual(C, F->left, L"'F' left should be 'C' (Remove Leaf).");
		Assert::AreEqual(G, F->right, L"'F' right should be 'G' (Remove Leaf).");

		Assert::AreEqual(H, L->parent.lock(), L"'L' parent should be 'H' (Remove Leaf).");
		Assert::AreEqual(I, L->left, L"'L' left should be 'I' (Remove Leaf).");
		Assert::AreEqual(V, L->right, L"'L' right should be 'V' (Remove Leaf).");

		Assert::AreEqual(F, C->parent.lock(), L"'C' parent should be 'F' (Remove Leaf).");
		Assert::IsNull(C->left.get(), L"'C' left should be null (Remove Leaf).");
		Assert::IsNull(C->right.get(), L"'C' right should be null (Remove Leaf).");

		Assert::AreEqual(F, G->parent.lock(), L"'G' parent should be 'F' (Remove Leaf).");
		Assert::IsNull(G->left.get(), L"'G' left should be null (Remove Leaf).");
		Assert::IsNull(G->right.get(), L"'G' right should be null (Remove Leaf).");

		Assert::AreEqual(L, I->parent.lock(), L"'I' parent should be 'L' (Remove Leaf).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Remove Leaf).");
		Assert::AreEqual(J, I->right, L"'I' right should be 'J' (Remove Leaf).");

		Assert::AreEqual(L, V->parent.lock(), L"'V' parent should be 'L' (Remove Leaf).");
		Assert::IsNull(V->left.get(), L"'V' left should be null (Remove Leaf).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Remove Leaf).");

		Assert::AreEqual(I, J->parent.lock(), L"'J' parent should be 'I' (Remove Leaf).");
		Assert::IsNull(J->left.get(), L"'J' left should be null (Remove Leaf).");
		Assert::IsNull(J->right.get(), L"'J' right should be null (Remove Leaf).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Remove Leaf).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Remove Leaf).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Remove Leaf).");

		/* Remove With Two Children
							 H					->			H
						   /   \				->		  /   \
						  F	    L				->		 F	   J
						 / \   / \				->		/ \	  / \
						C	G I   V				->	   C   G I   V
							   \   \			->			      \
								J   X			->			       X		*/

		removed = tree->remove("L");

		Assert::AreEqual(L, removed, L"Node returned wasn't 'L' (Remove With Two Children).");

		Assert::AreEqual(H, tree->root, L"The tree root should be 'H' (Remove With Two Children).");

		Assert::IsNull(H->parent.lock().get(), L"'H' parent should be null (Remove With Two Children).");
		Assert::AreEqual(F, H->left, L"'H' left should be 'F' (Remove With Two Children).");
		Assert::AreEqual(J, H->right, L"'H' right should be 'J' (Remove With Two Children).");

		Assert::AreEqual(H, F->parent.lock(), L"'F' parent should be 'H' (Remove With Two Children).");
		Assert::AreEqual(C, F->left, L"'F' left should be 'C' (Remove With Two Children).");
		Assert::AreEqual(G, F->right, L"'F' right should be 'G' (Remove With Two Children).");

		Assert::AreEqual(F, C->parent.lock(), L"'C' parent should be 'F' (Remove With Two Children).");
		Assert::IsNull(C->left.get(), L"'C' left should be null (Remove With Two Children).");
		Assert::IsNull(C->right.get(), L"'C' right should be null (Remove With Two Children).");

		Assert::AreEqual(F, G->parent.lock(), L"'G' parent should be 'F' (Remove With Two Children).");
		Assert::IsNull(G->left.get(), L"'G' left should be null (Remove With Two Children).");
		Assert::IsNull(G->right.get(), L"'G' right should be null (Remove With Two Children).");

		Assert::AreEqual(J, I->parent.lock(), L"'I' parent should be 'J' (Remove With Two Children).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Remove With Two Children).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Remove With Two Children).");

		Assert::AreEqual(J, V->parent.lock(), L"'V' parent should be 'J' (Remove With Two Children).");
		Assert::IsNull(V->left.get(), L"'V' left should be null (Remove With Two Children).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Remove With Two Children).");

		Assert::AreEqual(H, J->parent.lock(), L"'J' parent should be 'H' (Remove With Two Children).");
		Assert::AreEqual(I, J->left, L"'J' left should be 'I' (Remove With Two Children).");
		Assert::AreEqual(V, J->right, L"'J' right should be 'V' (Remove With Two Children).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Remove With Two Children).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Remove With Two Children).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Remove With Two Children).");

		/* Remove With One Child
							 H					->			H
						   /   \				->		  /   \
						  F	    J				->		 F	   J
						 / \   / \				->		/ \	  / \
						C	G I   V				->	   C   G I   X
							       \			->			      
								    X			->			       		*/

		removed = tree->remove("V");

		Assert::AreEqual(V, removed, L"Node returned wasn't 'V' (Remove With One Child).");

		Assert::AreEqual(H, tree->root, L"The tree root should be 'H' (Remove With One Child).");

		Assert::IsNull(H->parent.lock().get(), L"'H' parent should be null (Remove With One Child).");
		Assert::AreEqual(F, H->left, L"'H' left should be 'F' (Remove With One Child).");
		Assert::AreEqual(J, H->right, L"'H' right should be 'J' (Remove With One Child).");

		Assert::AreEqual(H, F->parent.lock(), L"'F' parent should be 'H' (Remove With One Child).");
		Assert::AreEqual(C, F->left, L"'F' left should be 'C' (Remove With One Child).");
		Assert::AreEqual(G, F->right, L"'F' right should be 'G' (Remove With One Child).");

		Assert::AreEqual(F, C->parent.lock(), L"'C' parent should be 'F' (Remove With One Child).");
		Assert::IsNull(C->left.get(), L"'C' left should be null (Remove With One Child).");
		Assert::IsNull(C->right.get(), L"'C' right should be null (Remove With One Child).");

		Assert::AreEqual(F, G->parent.lock(), L"'G' parent should be 'F' (Remove With One Child).");
		Assert::IsNull(G->left.get(), L"'G' left should be null (Remove With One Child).");
		Assert::IsNull(G->right.get(), L"'G' right should be null (Remove With One Child).");

		Assert::AreEqual(J, I->parent.lock(), L"'I' parent should be 'J' (Remove With One Child).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Remove With One Child).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Remove With One Child).");

		Assert::AreEqual(H, J->parent.lock(), L"'J' parent should be 'H' (Remove With One Child).");
		Assert::AreEqual(I, J->left, L"'J' left should be 'I' (Remove With One Child).");
		Assert::AreEqual(X, J->right, L"'J' right should be 'X' (Remove With One Child).");

		Assert::AreEqual(J, X->parent.lock(), L"'X' parent should be 'J' (Remove With One Child).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Remove With One Child).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Remove With One Child).");
	}

	TEST_METHOD(RemoveByNode_InalidInput_Fails)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		bool passed = false;

		try
		{
			tree->remove((shared_ptr<BinaryTreeNode>) nullptr);
		}
		catch (invalid_argument)
		{
			passed = true;
		}

		Assert::IsTrue(passed, L"Invalid argument not thrown.");
	}
	
	TEST_METHOD(RemoveByNode_ValidInput_CheckResults)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> H = tree->insert("H");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> L = tree->insert("L");
		shared_ptr<BinaryTreeNode> C = tree->insert("C");
		shared_ptr<BinaryTreeNode> G = tree->insert("G");
		shared_ptr<BinaryTreeNode> I = tree->insert("I");
		shared_ptr<BinaryTreeNode> V = tree->insert("V");
		shared_ptr<BinaryTreeNode> E = tree->insert("E");
		shared_ptr<BinaryTreeNode> J = tree->insert("J");
		shared_ptr<BinaryTreeNode> X = tree->insert("X");

		/* Remove Leaf
							 H					->			H
						   /   \				->		  /   \
						  F	    L				->		 F	   L
						 / \   / \				->		/ \	  / \
						C	G I   V				->	   C   G I   V
						 \     \   \			->			  \   \
						  E     J   X			->			   J   X		*/

		shared_ptr<BinaryTreeNode> removed = tree->remove(E);

		Assert::AreEqual(E, removed, L"Node returned wasn't 'E' (Remove Leaf).");

		Assert::AreEqual(H, tree->root, L"The tree root should be 'H' (Remove Leaf).");

		Assert::IsNull(H->parent.lock().get(), L"'H' parent should be null (Remove Leaf).");
		Assert::AreEqual(F, H->left, L"'H' left should be 'F' (Remove Leaf).");
		Assert::AreEqual(L, H->right, L"'H' right should be 'L' (Remove Leaf).");

		Assert::AreEqual(H, F->parent.lock(), L"'F' parent should be 'H' (Remove Leaf).");
		Assert::AreEqual(C, F->left, L"'F' left should be 'C' (Remove Leaf).");
		Assert::AreEqual(G, F->right, L"'F' right should be 'G' (Remove Leaf).");

		Assert::AreEqual(H, L->parent.lock(), L"'L' parent should be 'H' (Remove Leaf).");
		Assert::AreEqual(I, L->left, L"'L' left should be 'I' (Remove Leaf).");
		Assert::AreEqual(V, L->right, L"'L' right should be 'V' (Remove Leaf).");

		Assert::AreEqual(F, C->parent.lock(), L"'C' parent should be 'F' (Remove Leaf).");
		Assert::IsNull(C->left.get(), L"'C' left should be null (Remove Leaf).");
		Assert::IsNull(C->right.get(), L"'C' right should be null (Remove Leaf).");

		Assert::AreEqual(F, G->parent.lock(), L"'G' parent should be 'F' (Remove Leaf).");
		Assert::IsNull(G->left.get(), L"'G' left should be null (Remove Leaf).");
		Assert::IsNull(G->right.get(), L"'G' right should be null (Remove Leaf).");

		Assert::AreEqual(L, I->parent.lock(), L"'I' parent should be 'L' (Remove Leaf).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Remove Leaf).");
		Assert::AreEqual(J, I->right, L"'I' right should be 'J' (Remove Leaf).");

		Assert::AreEqual(L, V->parent.lock(), L"'V' parent should be 'L' (Remove Leaf).");
		Assert::IsNull(V->left.get(), L"'V' left should be null (Remove Leaf).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Remove Leaf).");

		Assert::AreEqual(I, J->parent.lock(), L"'J' parent should be 'I' (Remove Leaf).");
		Assert::IsNull(J->left.get(), L"'J' left should be null (Remove Leaf).");
		Assert::IsNull(J->right.get(), L"'J' right should be null (Remove Leaf).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Remove Leaf).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Remove Leaf).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Remove Leaf).");

		/* Remove With Two Children
							 H					->			H
						   /   \				->		  /   \
						  F	    L				->		 F	   J
						 / \   / \				->		/ \	  / \
						C	G I   V				->	   C   G I   V
							   \   \			->			      \
								J   X			->			       X		*/

		removed = tree->remove(L);

		Assert::AreEqual(L, removed, L"Node returned wasn't 'L' (Remove With Two Children).");

		Assert::AreEqual(H, tree->root, L"The tree root should be 'H' (Remove With Two Children).");

		Assert::IsNull(H->parent.lock().get(), L"'H' parent should be null (Remove With Two Children).");
		Assert::AreEqual(F, H->left, L"'H' left should be 'F' (Remove With Two Children).");
		Assert::AreEqual(J, H->right, L"'H' right should be 'J' (Remove With Two Children).");

		Assert::AreEqual(H, F->parent.lock(), L"'F' parent should be 'H' (Remove With Two Children).");
		Assert::AreEqual(C, F->left, L"'F' left should be 'C' (Remove With Two Children).");
		Assert::AreEqual(G, F->right, L"'F' right should be 'G' (Remove With Two Children).");

		Assert::AreEqual(F, C->parent.lock(), L"'C' parent should be 'F' (Remove With Two Children).");
		Assert::IsNull(C->left.get(), L"'C' left should be null (Remove With Two Children).");
		Assert::IsNull(C->right.get(), L"'C' right should be null (Remove With Two Children).");

		Assert::AreEqual(F, G->parent.lock(), L"'G' parent should be 'F' (Remove With Two Children).");
		Assert::IsNull(G->left.get(), L"'G' left should be null (Remove With Two Children).");
		Assert::IsNull(G->right.get(), L"'G' right should be null (Remove With Two Children).");

		Assert::AreEqual(J, I->parent.lock(), L"'I' parent should be 'J' (Remove With Two Children).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Remove With Two Children).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Remove With Two Children).");

		Assert::AreEqual(J, V->parent.lock(), L"'V' parent should be 'J' (Remove With Two Children).");
		Assert::IsNull(V->left.get(), L"'V' left should be null (Remove With Two Children).");
		Assert::AreEqual(X, V->right, L"'V' right should be 'X' (Remove With Two Children).");

		Assert::AreEqual(H, J->parent.lock(), L"'J' parent should be 'H' (Remove With Two Children).");
		Assert::AreEqual(I, J->left, L"'J' left should be 'I' (Remove With Two Children).");
		Assert::AreEqual(V, J->right, L"'J' right should be 'V' (Remove With Two Children).");

		Assert::AreEqual(V, X->parent.lock(), L"'X' parent should be 'V' (Remove With Two Children).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Remove With Two Children).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Remove With Two Children).");

		/* Remove With One Child
							 H					->			H
						   /   \				->		  /   \
						  F	    J				->		 F	   J
						 / \   / \				->		/ \	  / \
						C	G I   V				->	   C   G I   X
								   \			->
									X			->			       		*/

		removed = tree->remove(V);

		Assert::AreEqual(V, removed, L"Node returned wasn't 'V' (Remove With One Child).");

		Assert::AreEqual(H, tree->root, L"The tree root should be 'H' (Remove With One Child).");

		Assert::IsNull(H->parent.lock().get(), L"'H' parent should be null (Remove With One Child).");
		Assert::AreEqual(F, H->left, L"'H' left should be 'F' (Remove With One Child).");
		Assert::AreEqual(J, H->right, L"'H' right should be 'J' (Remove With One Child).");

		Assert::AreEqual(H, F->parent.lock(), L"'F' parent should be 'H' (Remove With One Child).");
		Assert::AreEqual(C, F->left, L"'F' left should be 'C' (Remove With One Child).");
		Assert::AreEqual(G, F->right, L"'F' right should be 'G' (Remove With One Child).");

		Assert::AreEqual(F, C->parent.lock(), L"'C' parent should be 'F' (Remove With One Child).");
		Assert::IsNull(C->left.get(), L"'C' left should be null (Remove With One Child).");
		Assert::IsNull(C->right.get(), L"'C' right should be null (Remove With One Child).");

		Assert::AreEqual(F, G->parent.lock(), L"'G' parent should be 'F' (Remove With One Child).");
		Assert::IsNull(G->left.get(), L"'G' left should be null (Remove With One Child).");
		Assert::IsNull(G->right.get(), L"'G' right should be null (Remove With One Child).");

		Assert::AreEqual(J, I->parent.lock(), L"'I' parent should be 'J' (Remove With One Child).");
		Assert::IsNull(I->left.get(), L"'I' left should be null (Remove With One Child).");
		Assert::IsNull(I->right.get(), L"'I' right should be null (Remove With One Child).");

		Assert::AreEqual(H, J->parent.lock(), L"'J' parent should be 'H' (Remove With One Child).");
		Assert::AreEqual(I, J->left, L"'J' left should be 'I' (Remove With One Child).");
		Assert::AreEqual(X, J->right, L"'J' right should be 'X' (Remove With One Child).");

		Assert::AreEqual(J, X->parent.lock(), L"'X' parent should be 'J' (Remove With One Child).");
		Assert::IsNull(X->left.get(), L"'X' left should be null (Remove With One Child).");
		Assert::IsNull(X->right.get(), L"'X' right should be null (Remove With One Child).");
	}

	TEST_METHOD(RemoveByNode_ValidInput_DecreasesFrequency)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();

		// 1
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> V = tree->insert("V");
		shared_ptr<BinaryTreeNode> E = tree->insert("E");

		// 2
		tree->insert("F");

		// 3
		tree->insert("V");
		tree->insert("V");

		// 4
		tree->insert("E");
		tree->insert("E");
		tree->insert("E");

		Assert::AreEqual(2, F->frequency, L"'F' frequency should be 2.");
		Assert::AreEqual(3, V->frequency, L"'V' frequency should be 3.");
		Assert::AreEqual(4, E->frequency, L"'E' frequency should be 4.");

		tree->remove(E);

		Assert::AreEqual(2, F->frequency, L"'F' frequency should be 2.");
		Assert::AreEqual(3, V->frequency, L"'V' frequency should be 3.");
		Assert::AreEqual(3, E->frequency, L"'E' frequency should be 3.");

		tree->remove(E);

		Assert::AreEqual(2, F->frequency, L"'F' frequency should be 2.");
		Assert::AreEqual(3, V->frequency, L"'V' frequency should be 3.");
		Assert::AreEqual(2, E->frequency, L"'E' frequency should be 2.");

		tree->remove(F);

		Assert::AreEqual(1, F->frequency, L"'F' frequency should be 1.");
		Assert::AreEqual(3, V->frequency, L"'V' frequency should be 3.");
		Assert::AreEqual(2, E->frequency, L"'E' frequency should be 2.");

		tree->remove(V);

		Assert::AreEqual(1, F->frequency, L"'F' frequency should be 1.");
		Assert::AreEqual(2, V->frequency, L"'V' frequency should be 2.");
		Assert::AreEqual(2, E->frequency, L"'E' frequency should be 2.");

		tree->remove(E);

		Assert::AreEqual(1, F->frequency, L"'F' frequency should be 1.");
		Assert::AreEqual(2, V->frequency, L"'V' frequency should be 2.");
		Assert::AreEqual(1, E->frequency, L"'E' frequency should be 1.");

		tree->remove(F);

		// F removed, E goes to root V to child
		Assert::IsNull(E->parent.lock().get(), L"'E' parent should null.");
		Assert::AreEqual(E, V->parent.lock(), L"'V' parent should be 'E'.");
		Assert::AreEqual(2, V->frequency, L"'V' frequency should be 2.");
		Assert::AreEqual(1, E->frequency, L"'E' frequency should be 1.");
	}

	TEST_METHOD(RemoveByNode_ValidInput_DecreasesDepth)
	{
		unique_ptr<BinaryTree> tree = make_unique<BinaryTree>();
		shared_ptr<BinaryTreeNode> H = tree->insert("H");
		shared_ptr<BinaryTreeNode> F = tree->insert("F");
		shared_ptr<BinaryTreeNode> L = tree->insert("L");
		shared_ptr<BinaryTreeNode> C = tree->insert("C");
		shared_ptr<BinaryTreeNode> G = tree->insert("G");
		shared_ptr<BinaryTreeNode> I = tree->insert("I");
		shared_ptr<BinaryTreeNode> V = tree->insert("V");
		shared_ptr<BinaryTreeNode> E = tree->insert("E");
		shared_ptr<BinaryTreeNode> J = tree->insert("J");
		shared_ptr<BinaryTreeNode> X = tree->insert("X");

		/*                   H					
						   /   \			
						  F	    L			
						 / \   / \			
						C	G I   V				
						 \     \   \			
						  E     J   X				*/

		Assert::AreEqual(4, H->depth, L"'H' depth should be 4.");
		Assert::AreEqual(3, F->depth, L"'F' depth should be 3.");
		Assert::AreEqual(3, L->depth, L"'L' depth should be 3.");
		Assert::AreEqual(2, C->depth, L"'C' depth should be 2.");
		Assert::AreEqual(1, G->depth, L"'G' depth should be 1.");
		Assert::AreEqual(2, I->depth, L"'I' depth should be 2.");
		Assert::AreEqual(2, V->depth, L"'V' depth should be 2.");
		Assert::AreEqual(1, E->depth, L"'E' depth should be 1.");
		Assert::AreEqual(1, J->depth, L"'J' depth should be 1.");
		Assert::AreEqual(1, X->depth, L"'X' depth should be 1.");

		tree->remove(E);

		/*                   H
						   /   \
						  F	    L
						 / \   / \
						C	G I   V
						       \   \
						        J   X				*/

		Assert::AreEqual(4, H->depth, L"'H' depth should be 4.");
		Assert::AreEqual(2, F->depth, L"'F' depth should be 2.");
		Assert::AreEqual(3, L->depth, L"'L' depth should be 3.");
		Assert::AreEqual(1, C->depth, L"'C' depth should be 1.");
		Assert::AreEqual(1, G->depth, L"'G' depth should be 1.");
		Assert::AreEqual(2, I->depth, L"'I' depth should be 2.");
		Assert::AreEqual(2, V->depth, L"'V' depth should be 2.");
		Assert::AreEqual(1, J->depth, L"'J' depth should be 1.");
		Assert::AreEqual(1, X->depth, L"'X' depth should be 1.");

		tree->remove(L);

		/*                   H
						   /   \
						  F	    J
						 / \   / \
						C	G I   V
							       \
								    X				*/

		Assert::AreEqual(4, H->depth, L"'H' depth should be 4.");
		Assert::AreEqual(2, F->depth, L"'F' depth should be 2.");
		Assert::AreEqual(1, C->depth, L"'C' depth should be 1.");
		Assert::AreEqual(1, G->depth, L"'G' depth should be 1.");
		Assert::AreEqual(1, I->depth, L"'I' depth should be 1.");
		Assert::AreEqual(2, V->depth, L"'V' depth should be 2.");
		Assert::AreEqual(3, J->depth, L"'J' depth should be 3.");
		Assert::AreEqual(1, X->depth, L"'X' depth should be 1.");

		tree->remove(V);

		/*                   H
						   /   \
						  F	    J
						 / \   / \
						C	G I   X				*/

		Assert::AreEqual(3, H->depth, L"'H' depth should be 3.");
		Assert::AreEqual(2, F->depth, L"'F' depth should be 2.");
		Assert::AreEqual(1, C->depth, L"'C' depth should be 1.");
		Assert::AreEqual(1, G->depth, L"'G' depth should be 1.");
		Assert::AreEqual(1, I->depth, L"'I' depth should be 1.");
		Assert::AreEqual(2, J->depth, L"'J' depth should be 2.");
		Assert::AreEqual(1, X->depth, L"'X' depth should be 1.");
	}
};