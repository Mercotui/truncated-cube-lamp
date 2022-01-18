#include "signal_monitor.hpp"

#include <sys/socket.h>

#include <QtCore/QLoggingCategory>
#include <QtCore/QSocketNotifier>

Q_LOGGING_CATEGORY(SignalMonitorLog, "signalmonitor", QtInfoMsg)

extern "C" {
static int signalProxySocket[2];

static void staticSignalHandler(int signal) {
  ::write(signalProxySocket[0], &signal, sizeof(signal));
}
}

SignalMonitor::SignalMonitor(QObject* parent) : QObject(parent) {
  // create proxy socket
  if (::socketpair(AF_UNIX, SOCK_STREAM, 0, signalProxySocket)) {
    qCCritical(SignalMonitorLog) << "Couldn't create socketpair";
  }

  proxy_notifier =
      new QSocketNotifier(signalProxySocket[1], QSocketNotifier::Read, this);

  QObject::connect(proxy_notifier, &QSocketNotifier::activated, this,
                   &SignalMonitor::handleSignal);
}

bool SignalMonitor::registerSignals(std::vector<int> signal_list) {
  struct sigaction options;
  sigemptyset(&options.sa_mask);
  options.sa_handler = staticSignalHandler;
  options.sa_flags = 0;
  options.sa_flags |= SA_RESTART;

  for (const auto signal : signal_list) {
    if (sigaction(signal, &options, 0)) {
      qCWarning(SignalMonitorLog) << "Couldn't register signal" << signal;
      return false;
    }
  }

  return true;
}

void SignalMonitor::handleSignal() {
  proxy_notifier->setEnabled(false);
  int signal = 0;
  auto read_size = ::read(signalProxySocket[1], &signal, sizeof(signal));

  if (read_size != sizeof(signal)) {
    qCWarning(SignalMonitorLog) << "read incomplete signal from proxy socket";
  }

  switch (signal) {
    case SIGINT: {
      qCDebug(SignalMonitorLog) << "handled SIGINT";
      emit sigInt();
      break;
    }
    case SIGTERM: {
      qCDebug(SignalMonitorLog) << "handled SIGTERM";
      emit sigTerm();
      break;
    }
    default: {
      qCWarning(SignalMonitorLog)
          << "Tried to handle unknown signal:" << signal;
      break;
    }
  }

  proxy_notifier->setEnabled(true);
}
