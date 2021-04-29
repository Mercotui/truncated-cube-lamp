#include <QtCore/QCache>
#include <QtCore/QtCore>

#include "animation_runner/animation_runner.hpp"
#include "animation_runner/screen_controller.hpp"
#include "http_server/http_server.hpp"
#include "http_server/scripts_api.hpp"
#include "http_server/scripts_cache.hpp"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  AnimationRunner runner(std::make_unique<ScreenController>());

  auto scripts_cache = std::make_unique<ScriptsCache>();
  auto scripts_api = std::make_unique<ScriptsApi>(std::move(scripts_cache),
                                                  runner.getResolution());

  QObject::connect(scripts_api.get(), &ScriptsApi::animationSelected, &runner,
                   &AnimationRunner::run);
  HttpServer http_server(std::move(scripts_api));

  return app.exec();
}
