#include "pch.h"
#include "CppUnitTest.h"
#include "MCadDriverWindow_sub.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMCadDriverInterface
{
	TEST_CLASS(TestMCadDriverInterface)
	{
	public:
		
		TEST_METHOD(Test_viewportCreate_one)
		{
			MCadDriverWindow_stub stubWin(600,600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::OneViewport);
			
			Assert::AreEqual(1, static_cast<int>(stubWin.viewportCount( )), L"Wrong viewport number");

			auto pViewport = stubWin.viewportAt(0);
			Assert::AreEqual(1.0f, pViewport->top(), L"Wrong viewport top");
			Assert::AreEqual(0.0f, pViewport->bottom(), L"Wrong viewport bottom");
			Assert::AreEqual(0.0f, pViewport->left(), L"Wrong viewport left");
			Assert::AreEqual(1.0f, pViewport->right(), L"Wrong viewport right");
		}

		TEST_METHOD(Test_viewportCreate_OneLeftTwoRight)
		{
			MCadDriverWindow_stub stubWin(600, 600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::OneLeftTwoRight);

			Assert::AreEqual(3, static_cast< int >( stubWin.viewportCount( ) ), L"Wrong viewport number");
			
			auto pViewport = stubWin.viewportAt(0);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[0] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[0] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[0] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[0] right");

			pViewport = stubWin.viewportAt(1);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[1] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[1] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[1] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[1] right");

			pViewport = stubWin.viewportAt(2);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[2] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[2] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[2] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[2] right");

			//TODO
		}

		TEST_METHOD(Test_viewportCreate_TwoLeftTwoRight)
		{
			MCadDriverWindow_stub stubWin(600, 600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::TwoLeftTwoRight);

			Assert::AreEqual(4, static_cast< int >( stubWin.viewportCount( ) ), L"Wrong viewport number");
			
			auto pViewport = stubWin.viewportAt(0);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[0] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[0] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[0] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[0] right");

			pViewport = stubWin.viewportAt(1);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[1] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[1] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[1] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[1] right");


			pViewport = stubWin.viewportAt(2);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[2] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[2] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[2] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[2] right");

			pViewport = stubWin.viewportAt(3);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[3] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[3] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[3] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[3] right");

			//TODO
		}

		TEST_METHOD(Test_viewportCreate_TwoLeftOneRight)
		{
			MCadDriverWindow_stub stubWin(600, 600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::TwoLeftOneRight);

			Assert::AreEqual(3, static_cast< int >( stubWin.viewportCount( ) ), L"Wrong viewport number");

			auto pViewport = stubWin.viewportAt(0);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[0] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[0] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[0] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[0] right");

			pViewport = stubWin.viewportAt(1);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[1] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[1] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[1] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[1] right");

			pViewport = stubWin.viewportAt(2);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[2] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[2] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[2] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[2] right");

			//TODO
		}

		TEST_METHOD(Test_viewportCreate_OneTopTwoBottom)
		{
			MCadDriverWindow_stub stubWin(600, 600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::OneTopTwoBottom);

			Assert::AreEqual(3, static_cast< int >( stubWin.viewportCount( ) ), L"Wrong viewport number");

			auto pViewport = stubWin.viewportAt(0);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[0] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[0] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[0] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[0] right");

			pViewport = stubWin.viewportAt(1);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[1] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[1] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[1] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[1] right");

			pViewport = stubWin.viewportAt(2);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[2] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[2] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[2] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[2] right");
			//TODO
		}

		TEST_METHOD(Test_viewportCreate_TwoTopOneBottom)
		{
			MCadDriverWindow_stub stubWin(600, 600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::TwoTopOneBottom);

			Assert::AreEqual(3, static_cast< int >( stubWin.viewportCount( ) ), L"Wrong viewport number");
			
			auto pViewport = stubWin.viewportAt(0);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[0] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[0] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[0] left");
			Assert::AreEqual(0.5f, pViewport->right( ), L"Wrong viewport[0] right");

			pViewport = stubWin.viewportAt(1);
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport[1] top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport[1] bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport[1] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[1] right");

			pViewport = stubWin.viewportAt(2);
			Assert::AreEqual(0.5f, pViewport->top( ), L"Wrong viewport[2] top");
			Assert::AreEqual(0.0f, pViewport->bottom( ), L"Wrong viewport[2] bottom");
			Assert::AreEqual(0.0f, pViewport->left( ), L"Wrong viewport[2] left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport[2] right");
			//TODO
		}

		TEST_METHOD(Test_viewportSelection)
		{
			MCadDriverWindow_stub stubWin(600, 600);
			stubWin.setupViewport(MCadDriverWindow::ViewportMapping::TwoLeftTwoRight);
			MCadEvent evt{};
			evt = MCadMouseEvent{ .m_type = MouseEventType::Mouse_Press,
				.m_buttons = MCadMouseButton::LeftButton, .m_mouseCoords{
			.m_screenCoords{400, 200}} };
			stubWin.onEvent(evt);
			auto pViewport = stubWin.currentViewport( );
			MCadMouseEvent mouseEvt = std::get<MCadMouseEvent>(evt.m_internalEvent);
			Assert::AreEqual(400.0f / 600.0f, mouseEvt.m_mouseCoords.m_windowCoords.x, L"Wrong X");
			Assert::AreEqual((600.0f - 200.0f) / 600.0f, mouseEvt.m_mouseCoords.m_windowCoords.x, L"Wrong Y");

			Assert::IsNotNull(pViewport.get( ), L"No current viewport");
			Assert::AreEqual(1.0f, pViewport->top( ), L"Wrong viewport top");
			Assert::AreEqual(0.5f, pViewport->bottom( ), L"Wrong viewport bottom");
			Assert::AreEqual(0.5f, pViewport->left( ), L"Wrong viewport left");
			Assert::AreEqual(1.0f, pViewport->right( ), L"Wrong viewport right");

		}

		TEST_METHOD(Test_viewportMove)
		{
		}
	};
}
