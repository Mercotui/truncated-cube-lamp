#pragma once

#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtHttpServer/QtHttpServer>
#include <memory>

#include "scripts_cache.hpp"

class RunnerApi : public QObject {
  Q_OBJECT
 public:
  RunnerApi(std::shared_ptr<ScriptsCache> cache, const QSize& screen_resolution,
            QObject* parent = nullptr);

  void registerApi(QHttpServer* server);

  QJsonObject handleInfo();
  QHttpServerResponse handleRun(const QHttpServerRequest& request);

 signals:
  void run(QString script);

 private:
  std::shared_ptr<ScriptsCache> script_cache_;
  QString current_script_;
  QSize screen_resolution_;
};
