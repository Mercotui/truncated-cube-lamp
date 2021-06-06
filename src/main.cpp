#include <QtCore/QCache>
#include <QtCore/QtCore>

#include "animation_runner/animation_runner.hpp"
#include "http_server/api/runner_api.hpp"
#include "http_server/api/scripts_api.hpp"
#include "http_server/http_server.hpp"
#include "http_server/scripts_cache.hpp"
#include "screen/dummy_screen_controller.hpp"
#include "screen/screen_controller.hpp"

namespace {
constexpr auto kDefaultScriptsLocation = ":/animations";

std::unique_ptr<ScreenControllerInterface> createScreen(bool use_dummy) {
  // decide runtime if the screen should be faked or not
  std::unique_ptr<ScreenControllerInterface> screen;
  if (use_dummy) {
    qInfo() << "Using a Dummy Screen";
    screen = std::make_unique<DummyScreenController>();
  } else {
    screen = std::make_unique<ScreenController>();
  }
  return std::move(screen);
}

}  // namespace

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  // set up command line arguments
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.setApplicationDescription(
      "Truncated Cube Lamp: neat idea for a lamp 👌");
  parser.addOption({{"d", "dummy-screen"}, "Use a dummy screen controller"});
  parser.process(app);

  // setup animation runner in seperate thread
  AnimationRunner runner(createScreen(parser.isSet("dummy-screen")));
  runner.start();

  // cache and persistent storage
  auto scripts_cache = std::make_shared<ScriptsCache>();
  Q_INIT_RESOURCE(animations);
  scripts_cache->loadDefaults(kDefaultScriptsLocation);

  // setup rest APIs
  auto scripts_api = std::make_unique<ScriptsApi>(scripts_cache);
  auto runner_api =
      std::make_unique<RunnerApi>(scripts_cache, runner.getResolution());

  // connect runner API to animation runner
  QObject::connect(runner_api.get(), &RunnerApi::run, &runner,
                   &AnimationRunner::runScript, Qt::DirectConnection);

  // setup http server with webpage and APIs
  HttpServer http_server(std::move(scripts_api), std::move(runner_api));

  return app.exec();
}
