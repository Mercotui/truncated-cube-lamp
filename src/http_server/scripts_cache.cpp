#include "scripts_cache.hpp"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(ScriptsCacheLog, "scriptscache", QtInfoMsg)

void ScriptsCache::loadDefaults(const QString& dir) {
  qCInfo(ScriptsCacheLog) << "Loading Defaults from" << dir;
  for (const auto& script_info : QDir(dir).entryInfoList()) {
    QFile script_file(script_info.filePath());
    script_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray script = script_file.readAll();

    auto name = script_info.fileName();
    name.chop(3);  // remove .js extension from script name
    qCDebug(ScriptsCacheLog) << "Loading Default:" << name;
    scripts_[name] = script;
  }
}

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

bool ScriptsCache::has(const QString& name) const {
  return scripts_.find(name) != scripts_.cend();
}

std::optional<QString> ScriptsCache::get(const QString& name) const {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    return iter.value();
  } else {
    qCInfo(ScriptsCacheLog) << "Tried to get unknown script" << name;
    return std::nullopt;
  }
}

QList<QString> ScriptsCache::getNames() const { return scripts_.keys(); }
