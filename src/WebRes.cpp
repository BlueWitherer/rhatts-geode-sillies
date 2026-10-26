#ifdef CW_ENABLE_WEB
#include <rhatt/util/WebRes.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

Result<WebRes> json::Serialize<WebRes>::fromJson(json::Value const& value) {
    GEODE_UNWRAP_INTO(std::string error, value["error"].asString());

    uint16_t code = 200;
    GEODE_UNWRAP_INTO_IF_OK(code, value["code"].asUInt());

    return Ok(WebRes(value["payload"], std::move(error), code));
};

json::Value json::Serialize<WebRes>::toJson(WebRes const& value) {
    json::Value obj;

    obj["payload"] = value.getPayloadValue();
    obj["error"] = value.getError();
    obj["code"] = value.getCode();

    return obj;
};

WebRes::WebRes(json::Value payload, std::string error, uint16_t code) : m_payload(std::move(payload)), m_error(std::move(error)), m_code(code) {};

WebRes request::parse(web::WebResponse const& res) {
    auto const fallback = [&res](std::string err) {
        log::error("Failed to process web response: {}", err);
        return WebRes(std::nullptr_t(), std::move(err), res.code());
    };

    auto jsonRes = res.json();
    if (jsonRes.isErr()) return fallback(std::move(jsonRes).unwrapErr());

    auto json = std::move(jsonRes).unwrap();
    if (!json.contains("code") || !json["code"].isNumber()) json["code"] = res.code();

    auto resp = std::move(json).as<WebRes>();
    if (resp.isErr()) return fallback(std::move(resp).unwrapErr());

    return std::move(resp).unwrap();
};

web::WebRequest request::base() {
    auto loader = Loader::get();

    return web::WebRequest()
        .userAgent(fmt::format("ModComments/{} ({}, Geode {}, GD {})",
            Mod::get()->getVersion().toVString(false),
            platform::getString(),
            loader->getVersion(),
            loader->getGameVersion()))
        .timeout(std::chrono::seconds(15));
};

web::WebRequest request::setBytes(geode::utils::web::WebRequest other, geode::ByteVector data) {
    return other.body(std::move(data));
}

json::Value& WebRes::getPayloadValue() & noexcept {
    return m_payload;
};

json::Value&& WebRes::getPayloadValue() && noexcept {
    return std::move(m_payload);
};

json::Value const& WebRes::getPayloadValue() const& noexcept {
    return m_payload;
};

ZStringView WebRes::getError() const noexcept {
    return m_error;
};

uint16_t WebRes::getCode() const noexcept {
    return m_code;
};

bool WebRes::isOk() const noexcept {
    return !m_payload.isNull() && m_error.empty();
};

bool WebRes::isErr() const noexcept {
    return m_payload.isNull() || m_code >= 400 || !m_error.empty();
};
#endif