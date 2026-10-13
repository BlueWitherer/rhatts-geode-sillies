#pragma once

#include <Geode/utils/string.hpp>

namespace cw {
    namespace str {
        using namespace geode::utils::string;

        inline constexpr auto isOnOff(bool on) {
            return on ? "ON" : "OFF";
        };

        namespace plurals {
            std::string appendS(std::string_view word, uint64_t amount, bool uppercase = false);
            std::string versatile(std::string_view singular, std::string_view plural, uint64_t amount);
        };
    };
};