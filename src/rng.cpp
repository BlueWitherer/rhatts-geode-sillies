#include <rhatt/util/rng.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

bool rng::flip() {
    return internal::generate<bool>();
}

uint8_t rng::fast() {
    return get<uint8_t>(100, 0);
}

bool rng::chance(uint8_t percent) {
    if (percent > 100) percent = 100;
    return get(100) <= percent;
}

float rng::pc(size_t precision) {
    auto factor = std::powf(10.f, precision);
    return std::round(get(1.f) * factor) / factor;
}

constexpr float rng::chanceToDelayPct(uint8_t chance) noexcept {
    if (chance > 100) chance = 100;

    return 1.f - (static_cast<float>(chance) / 100.f);
}