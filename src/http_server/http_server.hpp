#pragma once

#include <QtHttpServer/QtHttpServer>
#include <memory>

#include "scripts_api.hpp"

Q_DECLARE_LOGGING_CATEGORY(HttpServerLog)

class HttpServer : public QObject {
  Q_OBJECT
 public:
  explicit HttpServer(std::unique_ptr<ScriptsApi> scripts_api);

  QString servePageFromResource(QString page);

 private:
  QHttpServer server_;
  std::unique_ptr<ScriptsApi> scripts_api_;
};
