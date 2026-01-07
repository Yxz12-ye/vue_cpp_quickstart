#include "testCtrl.hpp"

using namespace test::v1;

void testCtrl::retTestMsg(const drogon::HttpRequestPtr& req,
                          std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    Json::Value ret;
    ret["msg"] = "hello_world_from_backend!";

    LOG_DEBUG << "receive test!";

    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
