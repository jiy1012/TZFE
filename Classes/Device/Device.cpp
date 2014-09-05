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


string Device::getOSVersion()
{
    string _ret=_getStaticStrFromJava("com/fourfire/tzfe/DeviceUtil","getOSVersion");
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

std::string Device::_getStrFromJava(const char* jclz, const char* jfunc)
{
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, jclz, "getInstance", "()Ljava/lang/Object;")) {
        CCLOG("jni: no getInstance");
        return "";
    }
    jobject jobj;
    jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    
    if (!JniHelper::getMethodInfo(minfo, jclz,jfunc, "()Ljava/lang/String;"))
    {
        CCLOG("jni: no %s",jfunc);
        return "";
    }

    jstring retFromJava = (jstring)minfo.env->CallObjectMethod(jobj, minfo.methodID);
    std:string _ret = JniHelper::jstring2string(retFromJava);
    minfo.env->DeleteLocalRef(minfo.classID);
    minfo.env->DeleteLocalRef(retFromJava);
    return _ret;
}

#endif


