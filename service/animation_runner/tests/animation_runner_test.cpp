#include "animation_runner/animation_runner.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <memory>
#include <utility>

#include "animation_runner/tests/screen_controller_mock.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

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

TEST(AnimationRunnerTest, DrawOne) {
  auto mock_screen = std::make_unique<ScreenControllerMock>();
  EXPECT_CALL(*mock_screen.get(), getResolution())
      .WillRepeatedly(Return(QSize(1, 1)));
  EXPECT_CALL(*mock_screen.get(), draw(Each(QColor("white")))).Times(1);
  EXPECT_CALL(*mock_screen.get(), clear()).Times(1);
  AnimationRunner animation_runner(std::move(mock_screen));

  animation_runner.runScript(
      "class Animation {"
      "  update (ctx) {"
      "    ctx.screen.setPixel(0,0, \"white\"); "
      "    ctx.screen.draw();"
      "    return undefined;"
      "  }"
      "}");
}

TEST(AnimationRunnerTest, DrawHundred) {
  auto mock_screen = std::make_unique<ScreenControllerMock>();
  EXPECT_CALL(*mock_screen.get(), getResolution())
      .WillRepeatedly(Return(QSize(10, 10)));
  EXPECT_CALL(*mock_screen.get(), draw(Each(QColor("green")))).Times(1);
  EXPECT_CALL(*mock_screen.get(), clear()).Times(1);
  AnimationRunner animation_runner(std::move(mock_screen));

  animation_runner.runScript(
      "class Animation {"
      "  update (ctx) {"
      "    for (let x = 0; x < ctx.screen.resolution.width; x++) {"
      "      for (let y = 0; y < ctx.screen.resolution.height; y++) {"
      "        ctx.screen.setPixel(x,y, \"green\");"
      "      }"
      "    }"
      "    ctx.screen.draw();"
      "    return undefined;"
      "  }"
      "}");
}

TEST(AnimationRunnerTest, DrawOutOfBounds) {
  auto mock_screen = std::make_unique<ScreenControllerMock>();
  EXPECT_CALL(*mock_screen.get(), getResolution())
      .WillRepeatedly(Return(QSize(10, 10)));
  EXPECT_CALL(*mock_screen.get(), draw(Each(QColor("red")))).Times(1);
  EXPECT_CALL(*mock_screen.get(), clear()).Times(1);
  AnimationRunner animation_runner(std::move(mock_screen));

  animation_runner.runScript(
      "class Animation {"
      "  update (ctx) {"
      "    for (let x = -5; x < (ctx.screen.resolution.width + 5); x++) {"
      "      for (let y = -5; y < (ctx.screen.resolution.height + 5); y++) {"
      "        ctx.screen.setPixel(x,y, \"red\");"
      "      }"
      "    }"
      "    ctx.screen.draw();"
      "    return undefined;"
      "  }"
      "}");
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
