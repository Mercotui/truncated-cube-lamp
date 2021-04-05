#include <http_server.hpp>

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(HttpServerLog, "http.server", QtInfoMsg)

namespace {
constexpr int kHttpPort = 8080;
}  // namespace

HttpServer::HttpServer() {
  Q_INIT_RESOURCE(website);

  // serve all website files
  QDir website_resource_dir(":/website/");
  for (const auto page : website_resource_dir.entryList()) {
    qCInfo(HttpServerLog) << "Registering page" << page;
    server_.route(QString("/") + page,
                  [&, page = page]() { return servePageFromResource(page); });
  }

  server_.route("/", [&]() { return servePageFromResource("index.html"); });
  server_.route("/script", [&](const QHttpServerRequest &request) {
    return postScript(request);
  });

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

QString HttpServer::postScript(const QHttpServerRequest &request) {
  QString animation_script = request.body();
  qCCritical(HttpServerLog) << animation_script;
  emit animationSelected(animation_script);

  return animation_script;
}
