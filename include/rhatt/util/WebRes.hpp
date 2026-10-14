#pragma once

#include "../Macros.h"

#ifdef CW_ENABLE_WEB
#include "../aliases.hpp"

#include <Geode/Geode.hpp>
#endif

namespace cw {
    namespace web = geode::utils::web;

#ifdef CW_ENABLE_WEB
    namespace url {
        static constexpr auto apiBase = CW_WEB_BASEURL;

        inline std::string apiEndpoint(std::string_view path) {
            return fmt::format("{}/api{}", apiBase, path);
        };
    };

    inline std::string operator""_api(const char* str, size_t len) {
        return url::apiEndpoint(std::string_view{str, len});
    };

    struct WebRes final {
    private:
        json::Value m_payload;
        std::string m_error;

        uint16_t m_code = 200;

    public:
        WebRes(json::Value payload = std::nullptr_t(), std::string error = "", uint16_t code = 200);

        template <typename T>
        geode::Result<T> getPayload() const {
            return m_payload.as<T>();
        };

        json::Value& getPayloadValue() & noexcept;
        json::Value&& getPayloadValue() && noexcept;
        json::Value const& getPayloadValue() const& noexcept;

        geode::ZStringView getError() const noexcept;
        uint16_t getCode() const noexcept;

        bool isOk() const noexcept;
        bool isErr() const noexcept;
    };

    namespace request {
        WebRes parse(web::WebResponse const& res);

        web::WebRequest base();

        web::WebRequest withAuth(std::string token);
        arc::Future<web::WebRequest> withAuthCo(std::string token);
    };
#endif
};

#ifdef CW_ENABLE_WEB
template <>
struct cw::json::Serialize<cw::WebRes> final {
    static geode::Result<cw::WebRes> fromJson(cw::json::Value const& value);
    static cw::json::Value toJson(cw::WebRes const& value);
};
#endif