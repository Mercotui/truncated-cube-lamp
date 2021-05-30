#include "scripts_api.hpp"

#include <QtCore/QLoggingCategory>
#include <utility>

#include "../scripts_cache.hpp"

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
  return {{"scripts", QJsonArray::fromStringList(scripts_cache_->getNames())}};
}

QHttpServerResponse ScriptsApi::handleScriptGet(const QString& name) {
  StatusCode http_status = StatusCode::Ok;
  QJsonDocument response;
  auto script = scripts_cache_->get(name);

  // if script was found, send it in the response
  if (script.has_value()) {
    auto encoded_script = QString(script.value().toUtf8().toBase64());
    response.setObject(QJsonObject{{{"script", encoded_script}}});
  } else {
    http_status = StatusCode::NotFound;
  }
  return QHttpServerResponse("application/json", response.toJson(),
                             http_status);
}

QHttpServerResponse ScriptsApi::handleScriptDelete(const QString& name) {
  StatusCode http_status = StatusCode::Ok;
  // if script was found then delete it
  if (scripts_cache_->get(name)) {
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
    auto script_object = request_json["script"];

    // check if the script value is a string
    if (!script_object.isString()) {
      auto error_message =
          QString("expected \"script\" of type string, but got \"%1\"")
              .arg(QVariant::fromValue(script_object.type()).toString());
      response.setObject(QJsonObject({{"error", error_message}}));
      http_status = StatusCode::UnprocessableEntity;
    } else {
      auto script_encoded = script_object.toString();
      auto decoding_result = QByteArray::fromBase64Encoding(
          script_encoded.toUtf8(), QByteArray::AbortOnBase64DecodingErrors);

      // check if the script value is valid Base64 data
      if (decoding_result.decodingStatus ==
          QByteArray::Base64DecodingStatus::Ok) {
        // add script to cache!
        scripts_cache_->add(name, decoding_result.decoded);
        response.setObject(QJsonObject({{"script", script_encoded}}));
      } else {
        auto error_message =
            QString("the script value was not a valid Base64 encoded string");
        response.setObject(QJsonObject({{"error", error_message}}));
        http_status = StatusCode::UnprocessableEntity;
      }
    }
  }
  return QHttpServerResponse("application/json", response.toJson(),
                             http_status);
}
