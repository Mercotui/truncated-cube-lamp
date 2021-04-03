#pragma once

#include <QtHttpServer/QtHttpServer>

Q_DECLARE_LOGGING_CATEGORY(HttpServerLog)

class HttpServer : public QObject {
  Q_OBJECT
 public:
  HttpServer();

  QString serveLanding();

 private:
  QHttpServer server_;
};
