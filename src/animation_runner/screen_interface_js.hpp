#pragma once

#include <QColor>
#include <QObject>
#include <QSize>
#include <vector>

class ScreenInterfaceJs : public QObject {
  Q_OBJECT

  Q_PROPERTY(QSize resolution MEMBER resolution_ CONSTANT)

 public:
  explicit ScreenInterfaceJs(QSize resolution, QObject* parent = nullptr);
  const std::vector<QColor>& pixels();

 public slots:
  void setPixel(const int x, const int y, QColor color);

  QColor getPixel(const int x, const int y);

 signals:
  void draw();

 private:
  QVector<int> test_;
  std::vector<QColor> pixels_;
  QSize resolution_;

  int wrapCoordinates(const int x, const int y);
};
