#pragma once

#include <QtCore/QJsonObject>
#include <QtCore/QString>
#include <optional>
#include <unordered_set>

using ScriptName = QString;
using ScriptCode = QString;

class Script {
 public:
  enum class ScriptType { kDefault, kTemplate, kAnimation, kImage, kTemporary };

  Script() = default;

  Script(ScriptName name, ScriptCode code,
         std::unordered_set<ScriptType> types);

  static QString scriptTypeToString(ScriptType type);
  static std::optional<ScriptType> stringToScriptType(QString type);
  static std::optional<Script> fromJsonObject(QJsonObject json_object);
  QJsonObject toJsonObject() const;

  bool shouldBeSaved() const;
  bool mayBeOverWritten() const;
  ScriptName name() const;
  ScriptCode code() const;
  const std::unordered_set<ScriptType>& types() const;

 private:
  ScriptName name_;
  ScriptCode code_;
  std::unordered_set<ScriptType> types_;
};
