#include <QtCore/QCache>
#include <QtCore/QtCore>
#include <QtNetwork/QHostAddress>

#include "animation_runner/animation_runner.hpp"
#include "animation_runner/animation_thread.hpp"
#include "http_server/api/runner_api.hpp"
#include "http_server/api/scripts_api.hpp"
#include "http_server/http_server.hpp"
#include "screen/dummy_screen_controller.hpp"
#include "screen/screen_controller.hpp"
#include "scripts_cache/script.hpp"
#include "scripts_cache/scripts_cache.hpp"

namespace {
constexpr auto kDefaultScriptsLocation = ":/animations";
constexpr int kDefaultHttpPort = 3080;

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
  parser.addOption({{"a", "address"},
                    "IP address to listen to. Default is localhost IPv6",
                    "host-address"});
  parser.addOption(
      {{"p", "port"}, "TCP port to listen on. Default is 8080", "host-port"});
  parser.process(app);

  // setup animation runner in seperate thread
  AnimationRunner animation_runner(createScreen(parser.isSet("dummy-screen")));
  AnimationThread animation_thread(&animation_runner);

  // cache and persistent storage
  auto scripts_cache = std::make_shared<ScriptsCache>();
  Q_INIT_RESOURCE(animations);
  scripts_cache->loadDefaults(kDefaultScriptsLocation);

  // setup rest APIs
  auto scripts_api = std::make_unique<ScriptsApi>(scripts_cache);
  auto runner_api = std::make_unique<RunnerApi>(
      scripts_cache, animation_runner.getResolution());

  // connect runner API to animation runner
  QObject::connect(runner_api.get(), &RunnerApi::run, &animation_runner,
                   &AnimationRunner::runScript);

  // decide host IP and port
  QHostAddress host_address(QHostAddress::LocalHost);
  if (parser.isSet("address")) {
    host_address = QHostAddress(parser.value("address"));
  }
  int port = kDefaultHttpPort;
  if (parser.isSet("port")) {
    port = parser.value("port").toInt();
  }

  // setup http server with webpage and APIs
  HttpServer http_server(host_address, port, std::move(scripts_api),
                         std::move(runner_api));

  return app.exec();
}
