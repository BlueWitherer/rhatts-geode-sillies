#pragma once

#include <matjson.hpp>

#include <asp/fs.hpp>

#include <Geode/cocos/cocoa/CCGeometry.h>

namespace cw {
    namespace sfx {
        inline void play(geode::ZStringView file) {
            (void)FMODAudioEngine::sharedEngine()->playEffectAsync(file);
        }
    };

    namespace anchor {
        inline constexpr cocos2d::CCPoint center = { 0.5f, 0.5f };
    };

    namespace json = matjson;
    namespace fs = asp::fs;
};