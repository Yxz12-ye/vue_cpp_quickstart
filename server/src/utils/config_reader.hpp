#pragma once

#include <string>

namespace ConfigReader {
// 返回文档根目录（绝对路径）
// 优先从固定的跨平台配置文件读取（例如 Windows: %APPDATA%/<PROJECT>/document_root.conf，
// Linux: $XDG_CONFIG_HOME/<PROJECT>/document_root.conf 或
// ~/.config/<PROJECT>/document_root.conf）。
// 若配置文件不存在，会在该固定位置生成配置文件并写入默认值（./www 的绝对路径），然后返回该值。
std::string getDocumentRoot();

}  // namespace ConfigReader
