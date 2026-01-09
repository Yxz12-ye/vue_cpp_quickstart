#include "app.hpp"

#include <drogon/HttpAppFramework.h>
#include <iostream>

#include "../controllers/testCtrl.hpp"
#include "../utils/config_reader.hpp"
#include "../utils/logger.hpp"
#include "../utils/string_utils.hpp"
#include "config.hpp"

int App::run(int argc, char* argv[]) {
    Logger::init(PROJECT_NAME);
    std::vector<std::string> args(argv, argv + argc);
    Logger::setLevel(Logger::Level::DEBUG);

    Logger::info("Starting " + std::string(PROJECT_NAME));

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--version" || args[i] == "-v") {
            printVersion();
            return 0;
        }
        if (args[i] == "--help" || args[i] == "-h") {
            printHelp();
            return 0;
        }
    }

    std::cout << "\n=== " << PROJECT_NAME << " ===" << std::endl;
    std::cout << "Version: " << PROJECT_VERSION << std::endl;
    std::cout << "Build type: " << BUILD_TYPE << std::endl;
    std::cout << std::endl;

    Logger::debug("Application initialized successfully");
    Logger::info("Ready to process commands");

    // 从外部配置文件读取文档根目录（参见 src/utils/config_reader.*）
    drogon::app().setDocumentRoot(ConfigReader::getDocumentRoot());

    Logger::info("Working Directory: " + ConfigReader::getDocumentRoot());

    drogon::app().addListener("0.0.0.0", 80);

    drogon::app().run();

    return 0;
}

void App::printVersion() const {
    std::cout << PROJECT_NAME << " v" << PROJECT_VERSION << std::endl;
}

void App::printHelp() const {
    std::cout << "Usage: " << PROJECT_NAME << " [options]\n"
              << "\nOptions:\n"
              << "  -h, --help     Show this help message\n"
              << "  -v, --version  Show version information\n";
}