#include <rhatt/util/strings.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

std::string str::plurals::appendS(std::string_view word, uint64_t amount, bool uppercase) {
    return (amount != 1) ? fmt::format("{}{}", word, uppercase ? "S" : "s") : std::string{word};
};

std::string str::plurals::versatile(std::string_view singular, std::string_view plural, uint64_t amount) {
    return std::string{(amount != 1) ? plural : singular};
};