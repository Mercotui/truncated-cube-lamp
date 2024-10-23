#pragma once
#include <signal.h>

#include <QtCore/QObject>
#include <QtCore/QSocketNotifier>
#include <vector>

class SignalMonitor : public QObject {
  Q_OBJECT

 public:
  explicit SignalMonitor(QObject *parent = 0);
  ~SignalMonitor() = default;

  bool registerSignals(std::vector<int> signal_list);

 signals:
  void sigInt();
  void sigTerm();

 public slots:
  void handleSignal();

 private:
  QSocketNotifier *proxy_notifier;
};
