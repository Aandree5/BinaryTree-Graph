#include "CppUnitTest.h"
#include "../BinaryTreeNode.h"

/* ToString specialisation */
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<BinaryTreeNode>(BinaryTreeNode * t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}