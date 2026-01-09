#include "config_reader.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "config.hpp"
#include "logger.hpp"

namespace fs = std::filesystem;

static fs::path getFixedConfigDir() {
#if defined(_WIN32)
    if (const char* appdata = std::getenv("APPDATA")) {
        return fs::path(appdata) / PROJECT_NAME;
    }
    return fs::current_path() / PROJECT_NAME;
#elif defined(__APPLE__)
    if (const char* home = std::getenv("HOME")) {
        return fs::path(home) / "Library" / "Application Support" / PROJECT_NAME;
    }
    return fs::current_path() / PROJECT_NAME;
#else
    if (const char* xdg = std::getenv("XDG_CONFIG_HOME")) {
        return fs::path(xdg) / PROJECT_NAME;
    }
    if (const char* home = std::getenv("HOME")) {
        return fs::path(home) / ".config" / PROJECT_NAME;
    }
    return fs::current_path() / PROJECT_NAME;
#endif
}

static std::string readFirstPathFromStream(std::istream& is) {
    std::string line;
    while (std::getline(is, line)) {
        auto start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
            continue;
        auto end = line.find_last_not_of(" \t\r\n");
        std::string v = line.substr(start, end - start + 1);
        if (v.empty())
            continue;
        auto eq = v.find('=');
        if (eq != std::string::npos) {
            v = v.substr(eq + 1);
            auto s2 = v.find_first_not_of(" \t\r\n");
            if (s2 == std::string::npos)
                continue;
            auto e2 = v.find_last_not_of(" \t\r\n");
            v = v.substr(s2, e2 - s2 + 1);
        }
        return v;
    }
    return {};
}

std::string ConfigReader::getDocumentRoot() {
    try {
        fs::path cfgDir = getFixedConfigDir();
        fs::create_directories(cfgDir);
        fs::path cfgFile = cfgDir / "document_root.conf";

        Logger::info("You can edit " + cfgFile.string());

        if (fs::exists(cfgFile)) {
            std::ifstream ifs(cfgFile);
            if (ifs) {
                auto v = readFirstPathFromStream(ifs);
                if (!v.empty()) {
                    fs::path p(v);
                    if (!p.is_absolute())
                        p = fs::current_path() / p;
                    return p.lexically_normal().string();
                }
            }
        }

        // 如果配置文件不存在或为空，生成默认配置并写入固定位置
        fs::path defaultRoot = fs::current_path() / "www";
        fs::path defaultRootAbs = defaultRoot;
        if (!defaultRootAbs.is_absolute())
            defaultRootAbs = fs::current_path() / defaultRootAbs;
        std::ofstream ofs(cfgFile, std::ios::trunc);
        if (ofs) {
            ofs << "document_root=" << defaultRootAbs.lexically_normal().string() << "\n";
            ofs.close();
        }
        return defaultRootAbs.lexically_normal().string();
    } catch (const std::exception& e) {
        // 任何异常都回退到 ./www
        try {
            fs::path fallback = fs::current_path() / "www";
            return fallback.lexically_normal().string();
        } catch (...) {
            return std::string("www");
        }
    }
}
