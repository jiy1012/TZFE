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
    
    void rateApp();
    
    std::string getChannelId();
    std::string getPayCmd();
    std::string getMarketUrl();
    std::string getFansUrl();
    
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
    std::string getID();
    std::string getReferrer();
    
    std::string getNetworkStatus();
    bool isNetworkAvaible();
    bool isBackgroundToForeground();
    
    std::string getVersionName();
    int getVersionCode();
    bool supportOfferwall();
    void exitGame();
    void createShortcut();
    void openURL(const std::string &sURL);
    void sendMail(const std::string &address,const std::string &title,const std::string &content);
    
    void showGameCenter();
    
    float getScaledTouchSlop();
    void mobileAppTrackPurchase(const std::string &cash_cnt, const std::string &text);
    void mobileAppTrackAction(const std::string &text);
    void kochavaTrackPurchase(const std::string &cash_cnt, const std::string &text);
    void kochavaTrackAction(const std::string &text);
    
    void onUMEvent(const std::string &event_type, const std::string &event_detail);
    void onAFEvent(const std::string &event_type, const std::string &event_detail);
    void onTapjoyOffersWall(const string &gameuid);
    void onUploadPhoto(int gameuid, int srcCode, int idx);
    int getStrLen(string str);
    
#pragma mark * clipboard
    std::string clipboardGetText();
    void clipboardSetText(const std::string &text);
    
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
