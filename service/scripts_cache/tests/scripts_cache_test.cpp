#include <QtCore/QCoreApplication>
#include <QtCore/QJsonArray>
#include <QtCore/QTimer>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "scripts_cache/script.hpp"

using ::testing::_;
using ::testing::Each;
using ::testing::Return;

TEST(ScriptsCacheTest, Add) { ASSERT_TRUE(true); }

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
