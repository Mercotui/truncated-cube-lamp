#include <http_server.hpp>

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(HttpServerLog, "http.server", QtInfoMsg)

namespace {
constexpr int kHttpPort = 8080;
}  // namespace

HttpServer::HttpServer() {
  server_.route("/", [&]() { return serveLanding(); });

  const auto port = server_.listen(QHostAddress::Any, kHttpPort);
  if (port != kHttpPort) {
    qCWarning(HttpServerLog)
        << "Server failed to get port" << kHttpPort << "instead using" << port;
  }
}

QString HttpServer::serveLanding() {
  qCInfo(HttpServerLog) << "Serving /";

  return "<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta "
         "charset=\"utf-8\"><title>Truncated "
         "Cube</title></head><body><h1>Truncated Cube Lamp</h1>This is the "
         "landing page!</body></html>";
}
