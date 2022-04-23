#include "scripts_cache/script.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonArray>
#include <QtCore/QTimer>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Each;
using ::testing::Return;

TEST(ScriptTest, Deserialize) {
  auto json_object = QJsonObject({{{"name", "testname"},
                                   {"script", "dGVzdHN0cmluZw=="},
                                   {"type", QJsonArray({{"animation"}})}}});
  auto script_result = Script::fromJsonObject(json_object);

  ASSERT_TRUE(script_result.has_value());
  auto script = script_result.value();

  ASSERT_EQ(script.name(), "testname");
  ASSERT_EQ(script.code(), QString("teststring"));
  ASSERT_EQ(script.types().size(), 1);
  ASSERT_TRUE(script.types().contains(Script::ScriptType::kAnimation));
}

TEST(ScriptTest, Serialize) {
  auto serialized =
      Script("testname", "teststring", {Script::ScriptType::kImage})
          .toJsonObject();
  ASSERT_EQ(serialized.size(), 3);
  ASSERT_EQ(serialized.value("name").toString(), "testname");
  ASSERT_EQ(serialized.value("script").toString(), "dGVzdHN0cmluZw==");
  ASSERT_EQ(serialized.value("type").toArray().size(), 1);
  ASSERT_EQ(serialized.value("type").toArray().first().toString(), "image");
}

TEST(ScriptTest, ShouldBeSaved) {
  auto script = Script("testname", "teststring", {Script::ScriptType::kImage});
  ASSERT_TRUE(script.shouldBeSaved());

  // defaults should no be saved
  auto default_script =
      Script("testname", "teststring",
             {Script::ScriptType::kImage, Script::ScriptType::kDefault});
  ASSERT_FALSE(default_script.shouldBeSaved());

  // templates should no be saved
  auto template_script =
      Script("testname", "teststring",
             {Script::ScriptType::kImage, Script::ScriptType::kTemplate});
  ASSERT_FALSE(template_script.shouldBeSaved());
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
