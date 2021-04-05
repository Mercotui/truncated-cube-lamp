#include <QtCore>

#include "animation_runner.hpp"
#include "http_server.hpp"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  HttpServer http_server;
  AnimationRunner runner;

  QObject::connect(&http_server, &HttpServer::animationSelected, &runner,
                   &AnimationRunner::run);

  return app.exec();
}
