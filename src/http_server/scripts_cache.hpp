#pragma once

#include <QtCore/QHash>
#include <QtCore/QString>
#include <optional>

class ScriptsCache {
 public:
  void loadDefaults(const QString& dir);

  void save(const QString& file);
  void load(const QString& file);

  void add(const QString& name, const QString& script);
  void remove(const QString& name);

  bool has(const QString& name) const;
  std::optional<QString> get(const QString& name) const;
  QList<QString> getNames() const;

 private:
  QHash<QString, QString> scripts_;
};
