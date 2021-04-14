#include <QCoreApplication>
#include <QTimer>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../animation_runner.hpp"
#include "screen_controller_mock.hpp"

using ::testing::_;
using ::testing::Each;
using ::testing::Return;

TEST(AnimationRunnerTest, GetResolution) {
  auto mock_screen = std::make_unique<ScreenControllerMock>();
  EXPECT_CALL(*mock_screen.get(), getResolution())
      .WillRepeatedly(Return(QSize(42, 41)));
  AnimationRunner animation_runner(std::move(mock_screen));

  QSize test_size = animation_runner.getResolution();
  ASSERT_EQ(test_size.width(), 42);
  ASSERT_EQ(test_size.height(), 41);
}

TEST(AnimationRunnerTest, AnimateOnce) {
  auto mock_screen = std::make_unique<ScreenControllerMock>();
  EXPECT_CALL(*mock_screen.get(), getResolution())
      .WillRepeatedly(Return(QSize(1, 1)));
  EXPECT_CALL(*mock_screen.get(), draw(Each(QColor("white")))).Times(1);
  AnimationRunner animation_runner(std::move(mock_screen));

  animation_runner.run("screen.setPixel(0,0, \"white\"); screen.draw()");
}

TEST(AnimationRunnerTest, AnimateRGB) {
  auto mock_screen = std::make_unique<ScreenControllerMock>();
  EXPECT_CALL(*mock_screen.get(), getResolution())
      .WillRepeatedly(Return(QSize(1, 1)));
  EXPECT_CALL(*mock_screen.get(), draw(Each(QColor("white")))).Times(1);
  AnimationRunner animation_runner(std::move(mock_screen));

  animation_runner.run("screen.setPixel(0,0, \"white\"); screen.draw()");
}

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();

  QTimer exitTimer;
  QObject::connect(&exitTimer, &QTimer::timeout, &app, QCoreApplication::quit);
  exitTimer.start();
  app.exec();
  return ret;
}
