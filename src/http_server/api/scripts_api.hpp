#pragma once

#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtHttpServer/QtHttpServer>
#include <memory>

class ScriptsCache;

class ScriptsApi : public QObject {
  Q_OBJECT
 public:
  explicit ScriptsApi(std::shared_ptr<ScriptsCache> cache,
                      QObject* parent = nullptr);

  void registerApi(QHttpServer* server);

  QJsonObject handleRoot();
  QHttpServerResponse handleScriptGet(const QString& name);
  QHttpServerResponse handleScriptDelete(const QString& name);
  QHttpServerResponse handleScriptPut(const QString& name,
                                      const QHttpServerRequest& request);

 private:
  std::shared_ptr<ScriptsCache> scripts_cache_;
};
