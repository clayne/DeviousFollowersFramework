#pragma once

#include <articuno/articuno.h>
#include <articuno/types/auto.h>
#include <SKSE/SKSE.h>

namespace DFF {
    class Debug {
    public:
        [[nodiscard]] inline spdlog::level::level_enum GetLogLevel() const noexcept {
            return _logLevel;
        }

        [[nodiscard]] inline spdlog::level::level_enum GetFlushLevel() const noexcept {
            return _flushLevel;
        }

    private:
        articuno_serialize(ar) {
            auto logLevel = spdlog::level::to_string_view(_logLevel);
            auto flushLevel = spdlog::level::to_string_view(_flushLevel);
            ar <=> articuno::kv(logLevel, "logLevel");
            ar <=> articuno::kv(flushLevel, "flushLevel");
        }

        articuno_deserialize(ar) {
            *this = Debug();
            std::string logLevel;
            std::string flushLevel;
            if (ar <=> articuno::kv(logLevel, "logLevel")) {
                _logLevel = spdlog::level::from_str(logLevel);
            }
            if (ar <=> articuno::kv(flushLevel, "flushLevel")) {
                _flushLevel = spdlog::level::from_str(flushLevel);
            }
        }

        spdlog::level::level_enum _logLevel{spdlog::level::level_enum::info};
        spdlog::level::level_enum _flushLevel{spdlog::level::level_enum::trace};

        friend class articuno::access;
    };

    class Config {
    public:
        [[nodiscard]] inline const Debug& GetDebug() const noexcept {
            return _debug;
        }

        [[nodiscard]] inline const std::string GetForcedDealName() const noexcept { return forcedDealName; }

        [[nodiscard]] static const Config& GetSingleton() noexcept;

    private:
        articuno_serde(ar) {
            ar <=> articuno::kv(_debug, "debug");
            ar <=> articuno::kv(forcedDealName, "forcedDeal");
            std::transform(forcedDealName.begin(), forcedDealName.end(), forcedDealName.begin(), ::tolower);

        }

        std::string forcedDealName;

        Debug _debug;
        friend class articuno::access;
    };
}
