#include "stdafx.h"
#include "CppUnitTest.h"
#include "Scoreboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CScoreboardTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCScoreboardReset)
		{
			CScoreboard scoreboard;

			scoreboard.AddJuicerPoints(1);
			scoreboard.AddAryaPoints(1);
			scoreboard.AddPokeballPoints(1);

			//assert that points were added
			Assert::AreNotEqual(scoreboard.GetAryaPoints(), 0);
			Assert::AreNotEqual(scoreboard.GetJuicerPoints(), 0);
			Assert::AreNotEqual(scoreboard.GetPokeballPoints(), 0);

			scoreboard.Reset();

			//assert that points are back to zero and check that timer is zero
			Assert::IsTrue(scoreboard.GetTime() == 0);

			Assert::AreEqual(scoreboard.GetAryaPoints(), 0);
			Assert::AreEqual(scoreboard.GetJuicerPoints(), 0);
			Assert::AreEqual(scoreboard.GetPokeballPoints(), 0);
		}
	};
}