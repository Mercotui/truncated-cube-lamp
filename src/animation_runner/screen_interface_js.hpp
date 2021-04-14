#pragma once

#include <QColor>
#include <QObject>
#include <QSize>
#include <vector>

class ScreenInterfaceJs : public QObject {
  Q_OBJECT

  Q_PROPERTY(QSize resolution MEMBER resolution_ CONSTANT)

 public:
  explicit ScreenInterfaceJs(QSize resolution, QObject* parent = nullptr)
      : pixels_(resolution.width() * resolution.width(), "black"),
        test_(resolution.width() * resolution.width(), 12),
        resolution_(resolution),
        QObject(parent) {}

  const std::vector<QColor>& pixels() { return pixels_; }

 public slots:
  void setPixel(const int x, const int y, QColor color) {
    pixels_[(x * resolution_.width()) + y] = color;
  }

  QColor getPixel(const int x, const int y) {
    return pixels_[(x * resolution_.width()) + y];
  }

 signals:
  void draw();

 private:
  QVector<int> test_;
  std::vector<QColor> pixels_;
  QSize resolution_;
};
