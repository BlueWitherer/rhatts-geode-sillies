#include <rhatt/util/colors.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

constexpr ccColor3B colors::internal::lerpColor(ccColor3B const& a, ccColor3B const& b, float t) noexcept {
    return {
        static_cast<GLubyte>(a.r + (b.r - a.r) * t),
        static_cast<GLubyte>(a.g + (b.g - a.g) * t),
        static_cast<GLubyte>(a.b + (b.b - a.b) * t),
    };
};

constexpr ccColor3B colors::fadeColor(float value) noexcept {
    if (value > 100.f) value = 100.f;
    if (value < 0.f) value = 0.f;

    if (value <= 50.0f) {
        auto t = value / 50.0f;
        return internal::lerpColor(red, yellow, t);
    } else {
        auto t = (value - 50.0f) / 50.0f;
        return internal::lerpColor(yellow, green, t);
    };
};