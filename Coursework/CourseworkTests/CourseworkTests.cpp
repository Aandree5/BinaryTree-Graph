#include "CppUnitTest.h"
#include "BinaryTreeNode.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/* ToString specialisation */
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<BinaryTreeNode> (BinaryTreeNode * t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}

TEST_CLASS(BinaryTreeNodeTests)
{
public:
		
	TEST_METHOD(Constructor_ValidInput_CreatesNode)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);

		Assert::IsNotNull(node.get(), L"Valid input but, node not created.");
	}

	TEST_METHOD(Constructor_InvalidInput_Fails)
	{
		string value;
		bool passed = false;

		try 
		{
			unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		}
		catch (invalid_argument)
		{
			passed = true;
		}
		
		Assert::IsTrue(passed, L"Invalid argument error not thrown.");
	}

	TEST_METHOD(CreatedNode_CheckProperties_Values)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);

		Assert::IsNull(node->left.get(), L"Node left is not nullptr.");
		Assert::IsNull(node->right.get(), L"Node right is not nullptr.");
		Assert::AreEqual(node->depth, 1, L"Node depth is not 1.");
		Assert::AreEqual(node->frequency, 1, L"Node frequency is not 1.");
	}

	TEST_METHOD(IsLeaf_NoChildren)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);

		Assert::IsTrue(node->isLeaf(), L"No children, should be a leaf.");
	}

	TEST_METHOD(IsLeaf_OneChild_Left)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		shared_ptr<BinaryTreeNode> tester = make_shared<BinaryTreeNode>(value);

		node->left = tester;

		
		Assert::IsFalse(node->isLeaf(), L"Has left child, should not be a leaf.");
	}

	TEST_METHOD(IsLeaf_OneChild_Right)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		shared_ptr<BinaryTreeNode> tester = make_shared<BinaryTreeNode>(value);

		node->right = tester;

		Assert::IsFalse(node->isLeaf(), L"Has right child, should not be a leaf.");
	}

	TEST_METHOD(IsLeaf_TwoChildren)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		shared_ptr<BinaryTreeNode> tester = make_shared<BinaryTreeNode>(value);

		node->left = tester;
		node->right = tester;

		Assert::IsFalse(node->isLeaf(), L"Has both children, should not be a leaf.");
	}

	TEST_METHOD(HasOnlyOneChild_NoChildren)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		shared_ptr<BinaryTreeNode> tester = node->hasOnlyOnechild();

		Assert::IsNull(tester.get(), L"No children, should return nullptr for hasOnlyOneChild.");
	}

	TEST_METHOD(HasOnlyOneChild_OneChild_Left)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		node->left = make_unique<BinaryTreeNode>("left");

		shared_ptr<BinaryTreeNode> tester = node->hasOnlyOnechild();

		Assert::IsNotNull(tester.get(), L"Has left child, should return the child for hasOnlyOneChild.");
		Assert::AreEqual(tester.get(), node->left.get(), L"The returned wasn't the left child.");
	}

	TEST_METHOD(HasOnlyOneChild_OneChild_right)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		node->right = make_unique<BinaryTreeNode>("right");

		shared_ptr<BinaryTreeNode> tester = node->hasOnlyOnechild();

		Assert::IsNotNull(tester.get(), L"Has right child, should return the child for hasOnlyOneChild.");
		Assert::AreEqual(tester.get(), node->right.get(), L"The returned wasn't the right child.");
	}

	TEST_METHOD(HasOnlyOneChild_TwoChildren)
	{
		string value = "Test";

		unique_ptr<BinaryTreeNode> node = make_unique<BinaryTreeNode>(value);
		shared_ptr<BinaryTreeNode> left = make_unique<BinaryTreeNode>("left");
		shared_ptr<BinaryTreeNode> right = make_unique<BinaryTreeNode>("right");

		node->left = left;
		node->right = right;

		shared_ptr<BinaryTreeNode> tester = node->hasOnlyOnechild();

		Assert::IsNull(tester.get(), L"Has both children, should return a nullptr.");
	}
};