#pragma once

#include <QtHttpServer/QtHttpServer>
#include <memory>

class ScriptsApi;
class RunnerApi;

Q_DECLARE_LOGGING_CATEGORY(HttpServerLog)

class HttpServer : public QObject {
  Q_OBJECT
 public:
  explicit HttpServer(std::unique_ptr<ScriptsApi> scripts_api,
                      std::unique_ptr<RunnerApi> runner_api);

  QHttpServerResponse servePageFromResource(const QString page);

 private:
  void registerWebsiteFiles();

  QHttpServer server_;
  std::unique_ptr<ScriptsApi> scripts_api_;
  std::unique_ptr<RunnerApi> runner_api_;
};
