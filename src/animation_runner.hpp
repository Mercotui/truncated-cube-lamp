#pragma once

#include <QJSEngine>

class AnimationRunner : public QObject {
  Q_OBJECT
 public:
  AnimationRunner();

  void run(QString animation_script);

 private:
  QJSEngine engine_;
};
