#pragma once

#include <drogon/HttpController.h>

namespace test {
namespace v1 {
class testCtrl : public drogon::HttpController<testCtrl> {
public:
    METHOD_LIST_BEGIN
    METHOD_ADD(testCtrl::retTestMsg, "/test", drogon::Get);
    METHOD_LIST_END

    void retTestMsg(const drogon::HttpRequestPtr& req,
                    std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
};  // namespace v1
};  // namespace test