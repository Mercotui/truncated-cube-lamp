#include "scripts_cache.hpp"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(ScriptsCacheLog, "scriptscache", QtInfoMsg)

void ScriptsCache::save(const QString& file) {
  qCDebug(ScriptsCacheLog) << "fake save to" << file;
}

void ScriptsCache::load(const QString& file) {
  qCDebug(ScriptsCacheLog) << "fake load from" << file;
}

void ScriptsCache::add(const QString& name, const QString& script) {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    qCDebug(ScriptsCacheLog) << "Overwriting script" << name;
  } else {
    qCDebug(ScriptsCacheLog) << "Adding script" << name;
  }

  scripts_[name] = script;
}

void ScriptsCache::remove(const QString& name) {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    qCDebug(ScriptsCacheLog) << "Deleting script" << name;
    scripts_.erase(iter);
  } else {
    qCInfo(ScriptsCacheLog) << "Asked to delete unknown script" << name;
  }
}

std::optional<QString> ScriptsCache::get(const QString& name) {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    return iter.value();
  } else {
    qCInfo(ScriptsCacheLog) << "Tried to get unknown script" << name;
    return std::nullopt;
  }
}
