#pragma once

#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtHttpServer/QtHttpServer>
#include <memory>

#include "scripts_cache.hpp"

class ScriptsApi : public QObject {
  Q_OBJECT
 public:
  ScriptsApi(std::unique_ptr<ScriptsCache> cache,
             const QSize& screen_resolution, QObject* parent = nullptr);

  void registerApi(QHttpServer* server);

  QString postScript(const QHttpServerRequest& request);

 signals:
  void animationSelected(QString animation);

 private:
  std::unique_ptr<ScriptsCache> cache_;
  QSize screen_resolution_;
};
