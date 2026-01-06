#pragma once

#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>

// 基于 spdlog 的日志封装类
// 提供统一的日志接口，支持格式化输出和日志级别控制
class Logger {
public:
    // 日志级别枚举，与 spdlog 级别对应
    enum class Level {
        DEBUG,    // 调试信息
        INFO,     // 一般信息
        WARNING,  // 警告信息
        ERROR     // 错误信息
    };

    // 初始化日志系统（程序启动时调用一次）
    static void init(const std::string& loggerName = "app");

    // 设置日志级别
    static void setLevel(Level level);

    // 基础日志方法
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

    // 支持格式化的模板方法
    template <typename... Args>
    static void debug(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        if (logger_)
            logger_->debug(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void info(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        if (logger_)
            logger_->info(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void warning(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        if (logger_)
            logger_->warn(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void error(spdlog::format_string_t<Args...> fmt, Args&&... args) {
        if (logger_)
            logger_->error(fmt, std::forward<Args>(args)...);
    }

    // 获取底层 spdlog logger（高级用法）
    static std::shared_ptr<spdlog::logger> getLogger() { return logger_; }

private:
    static std::shared_ptr<spdlog::logger> logger_;

    // 将自定义级别转换为 spdlog 级别
    static spdlog::level::level_enum toSpdlogLevel(Level level);
};