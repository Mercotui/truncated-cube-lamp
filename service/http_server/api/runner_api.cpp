#include "http_server/api/runner_api.hpp"

#include <QtCore/QJsonObject>
#include <QtCore/QLoggingCategory>
#include <utility>

#include "scripts_cache/scripts_cache.hpp"

using StatusCode = QHttpServerResponse::StatusCode;

Q_LOGGING_CATEGORY(RunnerApiLog, "http.api.runner", QtInfoMsg)
Q_DECLARE_METATYPE(QJsonValue::Type)

RunnerApi::RunnerApi(std::shared_ptr<ScriptsCache> cache,
                     const QSize& screen_resolution, QObject* parent)
    : QObject(parent),
      script_cache_(cache),
      screen_resolution_(screen_resolution) {}

void RunnerApi::registerApi(QHttpServer* server) {
  server->route("/api/runner/", [this]() { return handleInfo(); });
  server->route("/api/runner/run/", [this](const QHttpServerRequest& request) {
    return handleRun(request);
  });
}

QJsonObject RunnerApi::handleInfo() {
  return QJsonObject{{{"screen_resolution",
                       QJsonObject{{"width", screen_resolution_.width()},
                                   {"height", screen_resolution_.height()}}},
                      {"current_script", current_script_}}};
}

QHttpServerResponse RunnerApi::handleRun(const QHttpServerRequest& request) {
  StatusCode http_status = StatusCode::Ok;
  QJsonDocument response;

  QJsonParseError parsing_status;
  auto request_json = QJsonDocument::fromJson(request.body(), &parsing_status);

  if (parsing_status.error != QJsonParseError::NoError) {
    auto error_message = QString("malformed request JSON: \"%1\"")
                             .arg(parsing_status.errorString());
    response.setObject(QJsonObject({{"error", error_message}}));
    http_status = StatusCode::BadRequest;
  } else {
    auto name_object = request_json["name"];
    if (!name_object.isString()) {
      auto error_message =
          QString("expected \"name\" of type string, but got \"%1\"")
              .arg(QVariant::fromValue(name_object.type()).toString());
      response.setObject(QJsonObject({{"error", error_message}}));
      http_status = StatusCode::UnprocessableEntity;
    } else {
      auto name = name_object.toString();
      auto script = script_cache_->get(name);
      if (script.has_value()) {
        qCDebug(RunnerApiLog) << "requesting script to be run:" << name;
        current_script_ = name;
        response.setObject(QJsonObject({{"current_script", current_script_}}));

        emit run(script.value().code());
      } else {
        auto error_message =
            QString("no script found for \"name\"=\"%1\"").arg(name);
        response.setObject(QJsonObject({{"error", error_message}}));
        http_status = StatusCode::NotFound;
      }
    }
  }

  return QHttpServerResponse("application/json", response.toJson(),
                             http_status);
}
