#pragma once

#include <QtCore/QHash>
#include <QtCore/QString>
#include <optional>

class ScriptsCache {
 public:
  void save(const QString& file);
  void load(const QString& file);

  void add(const QString& name, const QString& script);
  void remove(const QString& name);

  std::optional<QString> get(const QString& name);

 private:
  QHash<QString, QString> scripts_;
};
