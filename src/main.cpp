#include <QtCore/QCache>
#include <QtCore/QtCore>

#include "animation_runner/animation_runner.hpp"
#include "animation_runner/screen_controller.hpp"
#include "http_server/http_server.hpp"
#include "http_server/runner_api.hpp"
#include "http_server/scripts_api.hpp"
#include "http_server/scripts_cache.hpp"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  AnimationRunner runner(std::make_unique<ScreenController>());

  auto scripts_cache = std::make_shared<ScriptsCache>();
  auto scripts_api = std::make_unique<ScriptsApi>(scripts_cache);
  auto runner_api =
      std::make_unique<RunnerApi>(scripts_cache, runner.getResolution());

  QObject::connect(runner_api.get(), &RunnerApi::run, &runner,
                   &AnimationRunner::run);

  HttpServer http_server(std::move(scripts_api), std::move(runner_api));

  return app.exec();
}
