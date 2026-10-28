#pragma once

#include <Geode/utils/random.hpp>

namespace cw {
    namespace rng {
        namespace internal {
            using namespace geode::utils::random;

            template <typename T>
            concept Num = std::is_arithmetic_v<std::remove_cvref_t<T>> && !std::same_as<std::remove_cvref_t<T>, bool>;
        };

        template <typename T = int>
            requires internal::Num<T>
        inline T get(T max, T min = static_cast<T>(0)) {
            if constexpr (std::is_integral_v<T>) return internal::generate<T>(min, max + static_cast<T>(1));
            return internal::generate<T>(min, max);
        }

        bool flip();

        uint8_t fast();
        bool chance(uint8_t percent);
        float pc(size_t precision = 2);

        constexpr float chanceToDelayPct(uint8_t chance = 50) noexcept;
    };
};