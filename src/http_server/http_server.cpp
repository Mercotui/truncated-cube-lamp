#include "http_server.hpp"

#include <QtCore/QLoggingCategory>
#include <QtCore/QStringLiteral>
#include <string_view>
#include <utility>

Q_LOGGING_CATEGORY(HttpServerLog, "http.server", QtInfoMsg)

namespace {
constexpr int kHttpPort = 8080;
constexpr std::string_view kWebsiteResourceDir = ":/website";
}  // namespace

HttpServer::HttpServer(std::unique_ptr<ScriptsApi> scripts_api,
                       std::unique_ptr<RunnerApi> runner_api)
    : scripts_api_(std::move(scripts_api)), runner_api_(std::move(runner_api)) {
  Q_INIT_RESOURCE(website);

  // serve all website files
  registerWebsiteFiles();

  // serve index.html as page root
  server_.route("/", [this]() {
    return servePageFromResource(QString(kWebsiteResourceDir.data()) +
                                 QDir::separator() + "index.html");
  });

  // serve APIs
  scripts_api_->registerApi(&server_);
  runner_api_->registerApi(&server_);

  // start listening
  const auto port = server_.listen(QHostAddress::Any, kHttpPort);
  if (port != kHttpPort) {
    qCWarning(HttpServerLog)
        << "Server failed to get port" << kHttpPort << "instead using" << port;
  }
}

void HttpServer::registerWebsiteFiles() {
  auto website_dir = QDir(kWebsiteResourceDir.data());
  QDirIterator dir_it(website_dir.path(), {}, QDir::Files,
                      QDirIterator::Subdirectories);
  while (dir_it.hasNext()) {
    auto file_path = dir_it.next();
    auto file_route = file_path.mid(kWebsiteResourceDir.size());

    qCInfo(HttpServerLog) << "Registering page" << file_route << "path"
                          << file_path;
    server_.route(file_route, [this](const QHttpServerRequest &request) {
      return servePageFromResource(QString(kWebsiteResourceDir.data()) +
                                   request.url().path());
    });
  }
}

QHttpServerResponse HttpServer::servePageFromResource(const QString file) {
  auto response = QHttpServerResponse::fromFile(file);
  if (response.statusCode() == QHttpServerResponder::StatusCode::Ok) {
    qCInfo(HttpServerLog) << "Serving" << file;
  } else {
    qCCritical(HttpServerLog) << "Tried to serve unregsitered page" << file;
  }

  // qt sets a stupid content type for HTML files 🙄
  if (response.mimeType() == "application/x-extension-html") {
    response = QHttpServerResponse("text/html", response.data());
  }

  return response;
}
