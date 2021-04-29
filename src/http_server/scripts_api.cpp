#include "scripts_api.hpp"

#include <QtCore/QLoggingCategory>
#include <utility>

Q_LOGGING_CATEGORY(ScriptsApiLog, "http.api", QtInfoMsg)

ScriptsApi::ScriptsApi(std::unique_ptr<ScriptsCache> cache,
                       const QSize& screen_resolution, QObject* parent)
    : QObject(parent),
      cache_(std::move(cache)),
      screen_resolution_(screen_resolution) {}

void ScriptsApi::registerApi(QHttpServer* server) {
  server->route("/api", [&](const QHttpServerRequest& request) {
    return postScript(request);
  });
}

QString ScriptsApi::postScript(const QHttpServerRequest& request) {
  QString animation_script = request.body();
  qCCritical(ScriptsApiLog) << animation_script;
  emit animationSelected(animation_script);

  return "";
}
