#include <string>
#include "Device.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jni.h"
#include "jni/JniHelper.h"
#endif  // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

using namespace std;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

string Device::getID()
{
    string _ret=_getStaticStrFromJava("com/fourfire/tzfe/DeviceUtil","getOSVersion");
    string ret = "";
    ret.append(_ret);
    CCLOG("Android-: %s",ret.c_str());
    return ret;
}
string Device::getOSVersion()
{
    string _ret=_getStrFromJava("com/fourfire/tzfe/DeviceUtil","getOSVersion");
    string ret = "";
    ret.append(_ret);
    CCLOG("Android-: %s",ret.c_str());
    return ret;
}


std::string Device::_getStaticStrFromJava(const char* jclz, const char* jfunc)
{
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, jclz, jfunc, "()Ljava/lang/String;")) {
        CCLOG("jni: no method");
        return "";
    }
    jstring retFromJava = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    std:string _ret = JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(retFromJava);
    return _ret;
}

//std::string Device::_getStrFromJava(const char* jclz, const char* jfunc)
//{
//    JniMethodInfo minfo;
//    if (!JniHelper::getStaticMethodInfo(minfo, jclz, "getInstance", "()Ljava/lang/Object;")) {
//        CCLOG("jni: no getInstance");
//        return "";
//    }
//    jobject jobj;
//    jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//    CCLOG("jni: %s getInstance ok",jclz);
//    
//    if (!JniHelper::getMethodInfo(minfo, jclz,jfunc, "()V;"))
//    {
//        CCLOG("jni: no %s",jfunc);
//        return "";
//    }
//    CCLOG("jni: %s %s ok",jclz,jfunc);
//    minfo.env->CallVoidMethod(jobj, minfo.methodID);
//    std:string _ret = JniHelper::jstring2string(retFromJava);
//    minfo.env->DeleteLocalRef(minfo.classID);
//    minfo.env->DeleteLocalRef(retFromJava);
//    return _ret;
//}
std::string Device::_getStrFromJava(const char* jclz, const char* jfunc)
{
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                "com/fourfire/tzfe/DeviceUtil", //类的路径
                                                "getInstance",  //方法名
                                                "()Ljava/lang/Object;");  //括号里的是参数，后面的是返回值。
    jobject jobj;
    if(isHave) {
        jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    CCLog("正确获取到 jobj");
    
    //
    isHave = JniHelper::getMethodInfo(minfo,
                                      "com/fourfire/tzfe/DeviceUtil", //类的路径
                                      "getOSVersion",  //方法名
                                      "()V");  //括号里的是参数，后面的是返回值。
    
    if(isHave) {
        minfo.env->CallVoidMethod(jobj, minfo.methodID);
    }
    CCLog("jni-java函数执行完毕");
}
#endif


