#include "scripts_cache.hpp"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QLoggingCategory>

namespace {
constexpr auto kDefaultSaveFile = "./animations.json";
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

    auto name = script_info.fileName();
    name.chop(3);  // remove .js extension from script name
    qCDebug(ScriptsCacheLog) << "Loading Default:" << name;
    scripts_[name] = script;
  }
}

void ScriptsCache::save(const QString& file_name) {
  qCDebug(ScriptsCacheLog) << "Save scritps to" << file_name;

  QJsonArray scripts_array;
  for (auto iter = std::begin(scripts_); iter != std::end(scripts_); iter++) {
    // TODO(menno): don't save default scripts
    QJsonObject script_object;
    script_object["name"] = iter.key();
    // TODO(menno): save script type
    script_object["type"] = "animation";
    script_object["script"] = iter.value().toUtf8().toBase64().constData();
    scripts_array.append({script_object});
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
        auto script_object = object_ref.toObject();
        QString decoded_script = script_object.value("script")
                                     .toString()
                                     .toUtf8()
                                     .toBase64()
                                     .constData();
        QString name = script_object.value("name").toString();
        scripts_[name] = decoded_script;
      }
    }
  }
}

void ScriptsCache::add(const QString& name, const QString& script) {
  if (auto iter = scripts_.find(name); iter != scripts_.end()) {
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
