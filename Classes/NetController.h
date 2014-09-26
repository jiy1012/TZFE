//
//  NetController.h
//  TZFE
//
//  Created by liuyi on 14-9-15.
//
//

#ifndef __TZFE__NetController__
#define __TZFE__NetController__

#include "CommonConfig.h"
#include <network/HttpRequest.h>
#include <network/HttpClient.h>
#include <json/document.h>  
using namespace network;

class NetController {
    private:
        NetController();
        ~NetController();
    public:
        static NetController* shared();
        void send(const char* postData);
        void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    protected:
        static NetController* m_NetContorller;

};


#endif /* defined(__TZFE__NetController__) */
