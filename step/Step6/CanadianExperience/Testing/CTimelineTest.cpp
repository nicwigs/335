/**
 * \file CTimelineTest.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCTimelineNumFrames)
		{
			CTimeline timeline;
			//default
			Assert::AreEqual(300, timeline.GetNumFrames());

			timeline.SetNumFrames(10);
			Assert::AreEqual(10, timeline.GetNumFrames());
			timeline.SetNumFrames(223);
			Assert::AreEqual(223, timeline.GetNumFrames());
		}
		TEST_METHOD(TestCTimelineFrameRate)
		{
			CTimeline timeline;
			//default
			Assert::AreEqual(30, timeline.GetFrameRate());

			timeline.SetFrameRate(10);
			Assert::AreEqual(10, timeline.GetFrameRate());
			timeline.SetFrameRate(40);
			Assert::AreEqual(40, timeline.GetFrameRate());
		}
		TEST_METHOD(TestCTImelineCurrentTime)
		{
			CTimeline timeline;
			//default
			Assert::AreEqual(0, timeline.GetCurrentTime(), 0.0001);

			timeline.SetCurrentTime(3.45);
			Assert::AreEqual(3.45, timeline.GetCurrentTime(), 0.0001);
			timeline.SetCurrentTime(9.78);
			Assert::AreEqual(9.78, timeline.GetCurrentTime(), 0.0001);
		}
		TEST_METHOD(TestCTimelineGetDuration)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

			// Changed duration
			timeline.SetFrameRate(375);
			Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

			timeline.SetNumFrames(789);
			Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
		}

		TEST_METHOD(TestCTimelineGetCurrentFrame)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(0, timeline.GetCurrentFrame());

			// Changed time
			timeline.SetCurrentTime(9.27);
			Assert::AreEqual(278, timeline.GetCurrentFrame());
		}
		TEST_METHOD(TestCTimelineAdd)
		{
			CTimeline timeline;
			CAnimChannelAngle channel;

			timeline.AddChannel(&channel);
			Assert::IsTrue(&timeline == channel.GetTimeline());
		}
	};
}