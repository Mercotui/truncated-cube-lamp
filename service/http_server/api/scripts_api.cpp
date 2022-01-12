#include "scripts_api.hpp"

#include <QtCore/QLoggingCategory>
#include <utility>

#include "script.hpp"
#include "scripts_cache.hpp"

using StatusCode = QHttpServerResponse::StatusCode;
using Method = QHttpServerRequest::Method;

Q_LOGGING_CATEGORY(ScriptsApiLog, "http.api.scripts", QtInfoMsg)
Q_DECLARE_METATYPE(QJsonValue::Type)

ScriptsApi::ScriptsApi(std::shared_ptr<ScriptsCache> cache, QObject* parent)
    : QObject(parent), scripts_cache_(cache) {}

void ScriptsApi::registerApi(QHttpServer* server) {
  server->route("/api/scripts/", [this]() { return handleRoot(); });
  server->route("/api/scripts/<arg>/", Method::Get,
                [this](QString name) { return handleScriptGet(name); });
  server->route("/api/scripts/<arg>/", Method::Put,
                [this](QString name, const QHttpServerRequest& request) {
                  return handleScriptPut(name, request);
                });
  server->route("/api/scripts/<arg>/", Method::Delete,
                [this](QString name) { return handleScriptDelete(name); });
}

QJsonObject ScriptsApi::handleRoot() {
  QJsonArray script_list;
  for (const auto& script_name : scripts_cache_->getNames()) {
    QJsonArray type_names;
    const auto& types = scripts_cache_->getTypesForScript(script_name);
    for (const auto& type : types) {
      type_names.append(Script::scriptTypeToString(type));
    }
    script_list.append(
        QJsonObject({{{"name", script_name}, {"type", type_names}}}));
  }
  return {{"scripts", script_list}};
}

QHttpServerResponse ScriptsApi::handleScriptGet(const QString& name) {
  StatusCode http_status = StatusCode::Ok;
  QJsonDocument response;
  auto script = scripts_cache_->get(name);

  // if script was found, send it in the response
  if (script.has_value()) {
    response.setObject(script.value().toJsonObject());
  } else {
    http_status = StatusCode::NotFound;
  }
  return QHttpServerResponse("application/json", response.toJson(),
                             http_status);
}

QHttpServerResponse ScriptsApi::handleScriptDelete(const QString& name) {
  StatusCode http_status = StatusCode::Ok;
  // if script was found then delete it
  if (scripts_cache_->has(name)) {
    scripts_cache_->remove(name);
  } else {
    http_status = StatusCode::NotFound;
  }
  return QHttpServerResponse(http_status);
}

QHttpServerResponse ScriptsApi::handleScriptPut(
    const QString& name, const QHttpServerRequest& request) {
  StatusCode http_status = StatusCode::Ok;
  QJsonDocument response;

  QJsonParseError parsing_status;
  auto request_json = QJsonDocument::fromJson(request.body(), &parsing_status);

  // check if the request is valid json
  if (parsing_status.error != QJsonParseError::NoError) {
    auto error_message = QString("malformed request JSON: \"%1\"")
                             .arg(parsing_status.errorString());
    response.setObject(QJsonObject({{"error", error_message}}));
    http_status = StatusCode::BadRequest;
  } else {
    auto script_object = Script::fromJsonObject(request_json.object());

    // check if the script could be parsed
    if (!script_object.has_value()) {
      response.setObject(QJsonObject({{"error", "malformed script object"}}));
      http_status = StatusCode::UnprocessableEntity;
    } else {
      auto script = script_object.value();
      if (script.name() == name && !name.isEmpty()) {
        scripts_cache_->add(script_object.value());
      } else {
        response.setObject(QJsonObject({{"error", "name didn't match uri"}}));
        http_status = StatusCode::UnprocessableEntity;
      }
    }
  }
  return QHttpServerResponse("application/json", response.toJson(),
                             http_status);
}
