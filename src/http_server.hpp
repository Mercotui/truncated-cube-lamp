#pragma once

#include <QtHttpServer/QtHttpServer>

Q_DECLARE_LOGGING_CATEGORY(HttpServerLog)

class HttpServer : public QObject {
  Q_OBJECT
 public:
  HttpServer();

  QString servePageFromResource(QString page);
  QString postScript(const QHttpServerRequest &request);

 signals:
  void animationSelected(QString animation);

 private:
  QHttpServer server_;
};
