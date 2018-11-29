#include "CppUnitTest.h"
#include "../BinaryTreeNode.h"
#include "../GraphNode.h"

/* ToString specialisation */
namespace Microsoft{ namespace VisualStudio{ namespace CppUnitTestFramework
{
			template<> static std::wstring ToString<BinaryTreeNode>(BinaryTreeNode *t)
			{
				RETURN_WIDE_STRING(*t);
			}

			template<> static std::wstring ToString<shared_ptr<BinaryTreeNode>>(const shared_ptr<BinaryTreeNode> &t)
			{
				RETURN_WIDE_STRING(*t);
			}

			template<> static std::wstring ToString<shared_ptr<GraphNode>>(const shared_ptr<GraphNode> &t)
			{
				RETURN_WIDE_STRING(*t);
			}
		}
	}
}