#pragma once

#define CW_OWNER 6408873

#define CW_GEODE_ID "geode.loader"

#define CW_HIGHEST_Z cocos2d::CCScene::get()->getHighestChildZ() + 1

#ifdef CW_ENABLE_WEB
    #ifndef CW_WEB_BASEURL
        #define CW_WEB_BASEURL "http://localhost:6769/"
    #endif

    #define CW_ARGON_UNWRAP(var)                                                                        \
        auto tokenRes = co_await argon::startAuth();                                                    \
        if (tokenRes.isErr()) co_return WebRes(std::nullptr_t(), std::move(tokenRes).unwrapErr(), 402); \
        var = std::move(tokenRes).unwrap()
#endif