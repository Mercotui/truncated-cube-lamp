#include <QtCore>

#include "animation_runner/animation_runner.hpp"
#include "animation_runner/screen_controller.hpp"
#include "http_server.hpp"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  HttpServer http_server;
  AnimationRunner runner(std::make_unique<ScreenController>());

  QObject::connect(&http_server, &HttpServer::animationSelected, &runner,
                   &AnimationRunner::run);

  return app.exec();
}
