#include "logger.hpp"

// 静态成员初始化
std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

void Logger::init(const std::string& loggerName) {
    // 创建控制台输出的 sink（带颜色支持）
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // 设置输出格式：[时间戳] [日志级别] 消息
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    // 创建 logger 实例
    logger_ = std::make_shared<spdlog::logger>(loggerName, console_sink);

    // 设置默认日志级别为 INFO
    logger_->set_level(spdlog::level::info);

    // 注册为全局 logger（可选，方便通过 spdlog::get() 获取）
    spdlog::register_logger(logger_);
}

void Logger::setLevel(Level level) {
    if (logger_) {
        logger_->set_level(toSpdlogLevel(level));
    }
}

void Logger::debug(const std::string& message) {
    if (logger_)
        logger_->debug(message);
}

void Logger::info(const std::string& message) {
    if (logger_)
        logger_->info(message);
}

void Logger::warning(const std::string& message) {
    if (logger_)
        logger_->warn(message);
}

void Logger::error(const std::string& message) {
    if (logger_)
        logger_->error(message);
}

spdlog::level::level_enum Logger::toSpdlogLevel(Level level) {
    switch (level) {
    case Level::DEBUG:
        return spdlog::level::debug;
    case Level::INFO:
        return spdlog::level::info;
    case Level::WARNING:
        return spdlog::level::warn;
    case Level::ERROR_:
        return spdlog::level::err;
    default:
        return spdlog::level::info;
    }
}

/**
 * 日志系统封装实现文件
 * 基于 spdlog 库，提供统一的日志接口
 * 使用方法：
 * 1. 在程序启动时调用 Logger::init() 初始化日志系统
 * 2. 使用 Logger::debug/info/warning/error 方法记录日志
 * 3. 可选地调用 Logger::setLevel() 设置日志级别
 * ```c++
 * // 程序启动时初始化一次
 * Logger::init("myapp");
 *
 * // 基础用法
 * Logger::info("Server started");
 * Logger::error("Connection failed");
 *
 * // 格式化用法（推荐）
 * Logger::debug("User ID: {}, Name: {}", userId, userName);
 *
 * // 调整日志级别
 * Logger::setLevel(Logger::Level::DEBUG);
 * ```
 */