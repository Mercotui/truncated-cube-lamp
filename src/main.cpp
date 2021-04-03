#include <QtCore>

#include "http_server.hpp"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  HttpServer http_server;

  return app.exec();
}
