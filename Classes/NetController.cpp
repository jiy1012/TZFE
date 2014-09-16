//
//  NetController.cpp
//  TZFE
//
//  Created by liuyi on 14-9-15.
//
//

#include "NetController.h"
USING_NS_CC;
using namespace cocos2d::network;
NetController* NetController::m_NetContorller = NULL;

NetController* NetController::shared()
{
    if (m_NetContorller == NULL)
    {
        m_NetContorller = new NetController();

    }
    return m_NetContorller;
}

NetController::NetController()
{
    
}

NetController::~NetController()
{
    
}
void NetController::send(const char* postData)
{
    //创建一个post请求
    HttpRequest* request_post = new HttpRequest();
//    request_post->setUrl("http://10.1.7.250/SinaApp/1/checkversion.php");
    request_post->setUrl("http://5461.sinaapp.com/Amfphp/index.php");
    request_post->setRequestType(HttpRequest::Type::POST);
//    std::vector<std::string> headers;
//    headers.push_back("Content-Type: application/json; charset=utf-8");
//    request_post->setHeaders(headers);
    request_post->setResponseCallback(CC_CALLBACK_2(NetController::onHttpRequestCompleted, this));
    //post数据
//    postData = "game=class";
    CCLOG("post %s",postData);
    request_post->setRequestData(postData, strlen(postData));
    request_post->setTag("POST test2");
    HttpClient::getInstance()->send(request_post);
    request_post->release();
}



void NetController::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed",response->getHttpRequest()->getTag());
    }
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s",statusCode,response->getHttpRequest()->getTag());
    log("response code: %ld",statusCode);
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s",response->getErrorBuffer());
        return;
    }
    std::vector<char>* buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    for (unsigned int i = 0 ; i < buffer->size();i++) {
        printf("%c",(*buffer)[i]);
    }
    //将std::vector(char)* 转换成 std::string的两种方法
    std::string backStr = std::string(&(*buffer->begin()), buffer->size());
    std::string anotherStr;
    anotherStr.insert(anotherStr.begin(), buffer->begin(), buffer->end());
    printf("%s\n", backStr.c_str());
    printf("%s\n", anotherStr.c_str());
    printf("\n");
    if (strcmp(response->getHttpRequest()->getTag(), "json") == 0)
    {
        rapidjson::Document doc;
        doc.Parse<0>(backStr.c_str());
        const rapidjson::Value& v = doc["status"];
        printf("status is : %s",v.GetString());
        const rapidjson::Value& dir = doc["results"];
        if (dir.IsArray()) {
            unsigned int i = 0;
            const rapidjson::Value& city = dir[i]["currentCity"];
            log("city is %s", city.GetString());
            //多层测试
            const rapidjson::Value& title = doc["results"][(unsigned int)0]["index"][(unsigned int)2]["title"];
            log("the title is %s", title.GetString());
        }
    }
}
