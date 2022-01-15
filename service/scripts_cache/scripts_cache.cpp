#include "scripts_cache.hpp"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QLoggingCategory>

namespace {
constexpr auto kDefaultSaveFile = "./animations.json";
const std::unordered_set<Script::ScriptType> kNullScriptTypes;
}  // namespace

Q_LOGGING_CATEGORY(ScriptsCacheLog, "scriptscache", QtInfoMsg)

ScriptsCache::ScriptsCache(QString savefile) {
  if (savefile != "") {
    load(savefile);
  } else {
    load(kDefaultSaveFile);
  }
}

void ScriptsCache::loadDefaults(const QString& dir) {
  qCInfo(ScriptsCacheLog) << "Loading Defaults from" << dir;
  for (const auto& script_info : QDir(dir).entryInfoList()) {
    QFile script_file(script_info.filePath());
    script_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray script = script_file.readAll();

    auto file_name = script_info.fileName();
    // extract script name, types, and remove .js extension from script name
    auto file_name_sections = file_name.split(".");
    if (file_name_sections.length() >= 2) {
      file_name_sections.pop_back();
      auto name = file_name_sections.takeFirst();
      qCDebug(ScriptsCacheLog) << "Loading Default:" << name;

      // the rest of the file name should be script types
      std::unordered_set<Script::ScriptType> types;
      for (auto type_name : file_name_sections) {
        auto type = Script::stringToScriptType(type_name);
        if (type.has_value()) {
          types.insert(type.value());
        } else {
          qCWarning(ScriptsCacheLog) << "File name" << file_name
                                     << "contains unknown type:" << type_name;
        }
      }

      scripts_[name] = {name, script, types};
    } else {
      qCWarning(ScriptsCacheLog)
          << "File name does not contain name+extension:" << file_name;
    }
  }
}

void ScriptsCache::save(const QString& file_name) {
  qCDebug(ScriptsCacheLog) << "Save scritps to" << file_name;

  QJsonArray scripts_array;
  for (auto iter = std::begin(scripts_); iter != std::end(scripts_); iter++) {
    const auto script = iter.value();
    if (script.shouldBeSaved()) {
      scripts_array.append(script.toJsonObject());
    }
  }

  QFile save_file(file_name);
  if (save_file.open(QIODevice::WriteOnly)) {
    save_file.write(QJsonDocument(scripts_array).toJson());
  } else {
    qCWarning(ScriptsCacheLog) << "Could not open file to save" << file_name;
  }
}

void ScriptsCache::load(const QString& file_name) {
  qCDebug(ScriptsCacheLog) << "Load scripts from" << file_name;

  QFile save_file(file_name);
  if (!save_file.open(QIODevice::ReadOnly)) {
    qCWarning(ScriptsCacheLog) << "Could not open file to load" << file_name;
    return;
  } else {
    QJsonParseError status;
    auto scripts_array =
        QJsonDocument::fromJson(save_file.readAll(), &status).array();
    if (status.error != QJsonParseError::NoError) {
      qCWarning(ScriptsCacheLog)
          << "Malformed savefile:" << status.errorString();
      return;
    } else {
      for (const auto& object_ref : scripts_array) {
        auto script = Script::fromJsonObject(object_ref.toObject());
        if (script) {
          scripts_[script.value().name()] = script.value();
        }
      }
    }
  }
}

void ScriptsCache::add(const Script& script) {
  const auto name = script.name();
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    if (!iter->mayBeOverWritten()) {
      qCWarning(ScriptsCacheLog) << "Can't overwrite script" << name;
    }
    qCDebug(ScriptsCacheLog) << "Overwriting script" << name;
  } else {
    qCDebug(ScriptsCacheLog) << "Adding script" << name;
  }

  scripts_[name] = script;

  save(kDefaultSaveFile);
}

void ScriptsCache::remove(const QString& name) {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    qCDebug(ScriptsCacheLog) << "Deleting script" << name;
    scripts_.erase(iter);
  } else {
    qCInfo(ScriptsCacheLog) << "Asked to delete unknown script" << name;
  }

  save(kDefaultSaveFile);
}

bool ScriptsCache::has(const QString& name) const {
  return scripts_.find(name) != scripts_.cend();
}

std::optional<Script> ScriptsCache::get(const QString& name) const {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    return iter.value();
  } else {
    qCInfo(ScriptsCacheLog) << "Tried to get unknown script" << name;
    return std::nullopt;
  }
}

const std::unordered_set<Script::ScriptType>& ScriptsCache::getTypesForScript(
    const QString& name) const {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
    return iter.value().types();
  } else {
    qCInfo(ScriptsCacheLog) << "Tried to get types of unknown script" << name;
    return kNullScriptTypes;
  }
}

QList<QString> ScriptsCache::getNames() const { return scripts_.keys(); }
