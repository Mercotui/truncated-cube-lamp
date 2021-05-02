#include "scripts_api.hpp"

#include <QtCore/QLoggingCategory>
#include <utility>

Q_LOGGING_CATEGORY(ScriptsApiLog, "http.api.scripts", QtInfoMsg)

ScriptsApi::ScriptsApi(std::shared_ptr<ScriptsCache> cache, QObject* parent)
    : QObject(parent), cache_(cache) {}

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
