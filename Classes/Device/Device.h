//
//  GOEUtilies.h
//  ccgoe
//
//  Created by Limin on 12-11-8.
//
//

#ifndef _Device_H_
#define _Device_H_
#include "CommonConfig.h"

using namespace std;

namespace Device{
#pragma mark -
#pragma mark Platform dependent
    
    std::string getDeviceModel();
    std::string getLanguage();
    std::string getLocaleString();
    std::string getDeviceUid();
    std::string getOSVersion();
    std::string getModel();
    std::string getManufacturer();
    std::string getBrand();
    std::string getProduct();
    std::string getBoard();
    std::string getPhoneNumber();
    std::string getReferrer();
    
    std::string getNetworkStatus();
    bool isNetworkAvaible();
    bool isBackgroundToForeground();
    
    std::string getVersionName();

    int getStrLen(string str);
    
#pragma mark * clipboard

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Dictionary* getDeviceInfo();
    std::string getOpenUDID();
    bool saveOpenUDIDToKeyChain(const std::string &openudid);
    std::string getOpenUDIDFromKeyChain();
//    bool saveUsernameAndPasswordToKeyChain(const std::string &username, const std::string &password);
//    std::string getUsernameFromKeyChain();
//    std::string getPasswordFromKeyChain();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string _getStaticStrFromJava(const char* jclz, const char* jfunc);
    std::string _getStrFromJava(const char* jclz, const char* jfunc);
#endif
};



#endif // _Device_H_
