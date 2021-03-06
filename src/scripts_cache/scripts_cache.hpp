#pragma once

#include <QtCore/QHash>
#include <QtCore/QString>
#include <optional>
#include <unordered_set>

#include "script.hpp"

class ScriptsCache {
 public:
  explicit ScriptsCache(QString savefile = "");

  void loadDefaults(const QString& dir, Script::ScriptType type);

  void save(const QString& file_name);
  void load(const QString& file_name);

  void add(const Script& script);
  void remove(const QString& name);

  bool has(const QString& name) const;
  std::optional<Script> get(const QString& name) const;
  QList<QString> getNames() const;

 private:
  QHash<QString, Script> scripts_;
};
