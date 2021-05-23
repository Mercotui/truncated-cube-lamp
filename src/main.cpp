#include <QtCore/QCache>
#include <QtCore/QtCore>

#include "animation_runner/animation_runner.hpp"
#include "http_server/http_server.hpp"
#include "http_server/runner_api.hpp"
#include "http_server/scripts_api.hpp"
#include "http_server/scripts_cache.hpp"
#include "screen/dummy_screen_controller.hpp"
#include "screen/screen_controller.hpp"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  // set up command line arguments
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.setApplicationDescription(
      "Truncated Cube Lamp: neat idea for a lamp 👌");
  parser.addOption({{"d", "dummy-screen"}, "Use a dummy screen controller"});
  parser.process(app);

  // decide runtime if the screen should be faked or not
  std::unique_ptr<ScreenControllerInterface> screen;
  if (parser.isSet("dummy-screen")) {
    qInfo() << "Using a Dummy Screen";
    screen = std::make_unique<DummyScreenController>();
  } else {
    screen = std::make_unique<ScreenController>();
  }

  AnimationRunner runner(std::move(screen));

  auto scripts_cache = std::make_shared<ScriptsCache>();
  auto scripts_api = std::make_unique<ScriptsApi>(scripts_cache);
  auto runner_api =
      std::make_unique<RunnerApi>(scripts_cache, runner.getResolution());

  QObject::connect(runner_api.get(), &RunnerApi::run, &runner,
                   &AnimationRunner::run);

  HttpServer http_server(std::move(scripts_api), std::move(runner_api));

  return app.exec();
}
