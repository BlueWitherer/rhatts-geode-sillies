#pragma once

#include <Geode/Geode.hpp>

namespace cw {
    namespace ui {
        struct LinkButton final {
            std::string id;
            std::string sprite;
            geode::Button::ButtonCallback callback;
        };

        namespace font {
            inline constexpr auto big = "bigFont.fnt";
            inline constexpr auto gold = "goldFont.fnt";
            inline constexpr auto chat = "chatFont.fnt";

            namespace geode {
                inline constexpr auto mono = "geode.loader/mdFontMono.fnt";
                inline constexpr auto regular = "geode.loader/mdFont.fnt";
                inline constexpr auto italic = "geode.loader/mdFontI.fnt";
                inline constexpr auto bold = "geode.loader/mdFontB.fnt";
                inline constexpr auto boldItalic = "geode.loader/mdFontBI.fnt";
            };
        };

        namespace sprites {
            namespace squares {
                inline constexpr auto white = "geode.loader/white-square.png";
                inline constexpr auto black = "geode.loader/black-square.png";
            };

            inline constexpr auto close = "geode.loader/close.png";
            inline constexpr auto info = "GJ_infoIcon_001.png";
        };

        namespace nodes {
            geode::Button* addHelpButton(cocos2d::CCNode* to, std::string content, bool useMarkdown = false, float btnScale = 0.75f, cocos2d::CCPoint const& offset = {});
        };

        namespace popups {
            FLAlertLayer* showDiscord();
            void showSupport();
        };
    };
};