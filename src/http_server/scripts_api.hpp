#pragma once

#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtHttpServer/QtHttpServer>
#include <memory>

#include "scripts_cache.hpp"

class ScriptsApi : public QObject {
  Q_OBJECT
 public:
  explicit ScriptsApi(std::shared_ptr<ScriptsCache> cache,
                      QObject* parent = nullptr);

  void registerApi(QHttpServer* server);

  QString postScript(const QHttpServerRequest& request);

 signals:
  void animationSelected(QString animation);

 private:
  std::shared_ptr<ScriptsCache> cache_;
};
