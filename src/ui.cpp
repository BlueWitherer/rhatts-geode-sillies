#include <rhatt/util/ui.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;
using namespace cw;

Button* ui::nodes::addHelpButton(CCNode* to, std::string content, bool useMarkdown, float btnScale, CCPoint const& offset) {
    auto infoBtn = Button::createWithSpriteFrameName(
        ui::sprites::info,
        [cont = std::move(content), useMarkdown](auto) {
            if (useMarkdown) return MDPopup::create(
                                        true,
                                        "Help",
                                        cont,
                                        "OK",
                                        nullptr,
                                        nullptr
            )
                ->show();

            createQuickPopup(
                "Help",
                cont,
                "OK",
                nullptr,
                nullptr
            );
        }
    );
    infoBtn->setID("info-btn");
    infoBtn->setScale(btnScale);
    infoBtn->setZOrder(CW_HIGHEST_Z);

    to->addChildAtPosition(infoBtn, Anchor::TopRight, ccp(-13.75f, -13.75f) + offset, false);
    return infoBtn;
}

FLAlertLayer* ui::popups::showDiscord() {
    return createQuickPopup(
        "Discord Community",
        "Join <cd>Cheeseworks</c>'s <cb>Discord server</c>?\n"
        "<cs>Get help, report bugs, and chat with other players!</c>",
        "Cancel",
        "OK",
        [](auto, bool ok) {
            if (ok) web::openLinkInBrowser("https://www.dsc.gg/cheeseworks");
        }
    );
}

void ui::popups::showSupport() {
    return openSupportPopup(Mod::get());
}