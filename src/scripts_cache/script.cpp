#include "script.hpp"

#include <QtCore/QJsonArray>

Script::Script(ScriptName name, ScriptCode code,
               std::unordered_set<ScriptType> types)
    : name_(name), code_(code), types_(types) {}

QString Script::scriptTypeToString(const Script::ScriptType type) {
  switch (type) {
    case Script::ScriptType::kAnimation: {
      return "animation";
    }
    case Script::ScriptType::kImage: {
      return "image";
    }
    case Script::ScriptType::kDefault: {
      return "default";
    }
    case Script::ScriptType::kTemporary: {
      return "temporary";
    }
    case Script::ScriptType::kTemplate: {
      return "template";
    }
    default: {
      Q_ASSERT(false);
      return "";
    }
  }
}

std::optional<Script::ScriptType> Script::stringToScriptType(
    const QString type) {
  if (type == "animation") {
    return Script::ScriptType::kAnimation;
  } else if (type == "image") {
    return Script::ScriptType::kImage;
  } else if (type == "default") {
    return Script::ScriptType::kDefault;
  } else if (type == "temporary") {
    return Script::ScriptType::kTemporary;
  } else if (type == "template") {
    return Script::ScriptType::kTemplate;
  }
  return std::nullopt;
}

std::optional<Script> Script::fromJsonObject(QJsonObject json_object) {
  auto encoded_code = json_object.value("script").toString().toUtf8();
  auto decoding_result = QByteArray::fromBase64Encoding(encoded_code);
  if (!decoding_result) {
    return std::nullopt;
  }
  ScriptCode code = decoding_result.decoded;

  std::unordered_set<ScriptType> types;
  QJsonArray type_array = json_object.value("type").toArray();
  for (auto iter = std::begin(type_array); iter != std::end(type_array);
       iter++) {
    auto type = stringToScriptType(iter->toString());
    if (type.has_value()) {
      types.insert(type.value());
    }
  }

  ScriptName name = json_object.value("name").toString();

  return Script(name, code, types);
}

QJsonObject Script::toJsonObject() const {
  QString encoded_code = code_.toUtf8().toBase64().constData();

  auto types_array = QJsonArray();
  for (auto type : types_) {
    types_array.append(scriptTypeToString(type));
  }

  QJsonObject json_object;
  json_object["name"] = name_;
  json_object["type"] = types_array;
  json_object["script"] = encoded_code;
  qWarning() << json_object;
  return json_object;
}

bool Script::shouldBeSaved() const {
  return !(types_.contains(ScriptType::kDefault) ||
           types_.contains(ScriptType::kTemporary) ||
           types_.contains(ScriptType::kTemplate));
}

ScriptName Script::name() const { return name_; }

ScriptCode Script::code() const { return code_; }

const std::unordered_set<Script::ScriptType>& Script::types() const {
  return types_;
}
