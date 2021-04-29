#include "http_server.hpp"

#include <QtCore/QLoggingCategory>
#include <utility>

Q_LOGGING_CATEGORY(HttpServerLog, "http.server", QtInfoMsg)

namespace {
constexpr int kHttpPort = 8080;
}  // namespace

HttpServer::HttpServer(std::unique_ptr<ScriptsApi> scripts_api)
    : scripts_api_(std::move(scripts_api)) {
  Q_INIT_RESOURCE(website);

  // serve all website files
  QDir website_resource_dir(":/website/");
  for (const auto page : website_resource_dir.entryList()) {
    qCInfo(HttpServerLog) << "Registering page" << page;
    server_.route(QString("/") + page,
                  [&, page = page]() { return servePageFromResource(page); });
  }

  server_.route("/", [&]() { return servePageFromResource("index.html"); });
  scripts_api_->registerApi(server_);

  const auto port = server_.listen(QHostAddress::Any, kHttpPort);
  if (port != kHttpPort) {
    qCWarning(HttpServerLog)
        << "Server failed to get port" << kHttpPort << "instead using" << port;
  }
}

QString HttpServer::servePageFromResource(QString page) {
  QString content;
  QFile page_file(page.prepend(":/website/"));
  if (page_file.open(QFile::ReadOnly | QFile::Text)) {
    qCInfo(HttpServerLog) << "Serving" << page;
    QTextStream file_stream(&page_file);
    content = file_stream.readAll();
  } else {
    qCCritical(HttpServerLog) << "Tried to serve unregsitered page" << page;
    content = "Internal server error";
  }
  return content;
}
