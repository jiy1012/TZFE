#include "HelloWorldScene.h"

#include "DWSScene.h"

#include "GameScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jni.h"
#include "jni/JniHelper.h"

#endif
void HelloWorld::startGame(cocos2d::Ref* pSender)
{
    CCLOG("test jni");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    std::string ret;
    if (JniHelper::getStaticMethodInfo(t, "com/fourfire/TZFE/SIMCardInfo", "getNativePhoneNumber", "(Ljava/lang/String;)Ljava/lang/String;")) {
        CCLOG("test JniHelper::getStaticMethodInfo ");
//        jstring jret = (jstring)t.env->CallObjectMethod(t.classID, t.methodID);
//        ret = JniHelper::jstring2string(jret);
//        CCLOG("%s",ret);
    }
#endif
    CCLOG("test jni end ");
    //    Scene* gameScene = GameScene::createScene();
    //    Director::getInstance()->pushScene(gameScene);
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Sprite* DWSSprite = DWSScene::DWSLogoDisplay();
    
    FadeOut* pFadeout = FadeOut::create(1.0f);
    auto pSequence = Sequence::create(
                                      pFadeout,
                                      CallFuncN::create(CC_CALLBACK_0(HelloWorld::logoDisplayCallback,this)),
                                      NULL);
    DWSSprite->runAction(pSequence);
    this->addChild(DWSSprite, 0);
    return true;
}
void HelloWorld::logoDisplayCallback()
{
    CCLOG("%s","logoDisplayCallback pNode");
    auto pMydraw = Sprite::create("mydraw.jpg");
    pMydraw->setPosition(Vec2(WIN_WIDTH/2, WIN_HEIGHT/2));
    
    float expire = 0.5f;

    
    FadeIn* pFadein = FadeIn::create(expire);
    DelayTime* pDelay = DelayTime::create(expire);
    FadeOut* pFadeout = FadeOut::create(expire);
    
    auto pSequence = Sequence::create(
                                      pFadein,
                                      pDelay,
                                      pFadeout,
                                      CallFuncN::create( CC_CALLBACK_0(HelloWorld::sloganDisplayCallback,this)),
                                   NULL);
    pMydraw->runAction(pSequence);
    this->addChild(pMydraw);
}

void HelloWorld::sloganDisplayCallback()
{
    CCLOG("%s","sloganDisplayCallback");
    auto pLabel = LabelTTF::create("神马品质\n坚如磐石", "", 50);
    
    pLabel->setPosition(Vec2(WIN_WIDTH/2, WIN_HEIGHT/2));
    
    float expire = 0.5f;

    
    FadeIn* pFadein = FadeIn::create(expire);
    FadeOut* pFadeout = FadeOut::create(expire);
    auto pSequence = Sequence::create(
                                      pFadein,
                                      pFadeout,
                                      CallFunc::create(CC_CALLBACK_0(HelloWorld::titleDisplayCallback,this)),
                                      NULL);
    pLabel->runAction(pSequence);
    this->addChild(pLabel);
}

void HelloWorld::titleDisplayCallback()
{
    float scale = MIN(WIN_WIDTH/1024,WIN_HEIGHT/768);
    
    auto title = LabelTTF::create("NUMBER", "", 200);
    title->setPosition(Vec2(WIN_WIDTH/2,WIN_HEIGHT*2/3));
    title->setScale(scale);
    this->addChild(title);
    
    auto pStratButton = MenuItemImage::create("startButton.png", "startButtonSelected.png",
                                              CC_CALLBACK_1(HelloWorld::startGame,this));
    pStratButton->setPosition(Vec2(WIN_WIDTH/4, WIN_HEIGHT/8));
    pStratButton->setScale(scale);
    auto pStrat6 = MenuItemImage::create("6_6_4.png", "6_6_4.png",
                                         CC_CALLBACK_1(HelloWorld::startGameWithParams,this,6,6,4));
    pStrat6->setPosition(Vec2(WIN_WIDTH/4, WIN_HEIGHT/4));
    pStrat6->setScale(scale);

    auto pStrat8 = MenuItemImage::create("8_8_6.png", "8_8_6.png",
                                         CC_CALLBACK_1(HelloWorld::startGameWithParams,this,8,8,6));
    pStrat8->setPosition(Vec2(WIN_WIDTH/2, WIN_HEIGHT/4));
    pStrat8->setScale(scale);
    
    auto pStrat10 = MenuItemImage::create("10_10_7.png", "10_10_7.png",
                                         CC_CALLBACK_1(HelloWorld::startGameWithParams,this,10,10,7));
    pStrat10->setPosition(Vec2(WIN_WIDTH*3/4, WIN_HEIGHT/4));
    pStrat10->setScale(scale);
    
    auto pExitButton = MenuItemImage::create("exitButton.png", "exitButtonSelected.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    pExitButton->setPosition(Vec2(WIN_WIDTH/2, WIN_HEIGHT/8));
    pExitButton->setScale(scale);
    
    auto pMenu = Menu::create(pStrat6,pStrat8,pStrat10,pExitButton,pStratButton,NULL);
    pMenu->setPosition( Vec2(0, 0) );
    this->addChild(pMenu, 1);
}



void HelloWorld::startGameWithParams(cocos2d::Ref* pSender,int l,int r,int b)
{
    CCLOG("start game line:%d row:%d button:%d", l ,r ,b);
    Scene* gameScene = GameScene::createScene(l,r,b);
    Director::getInstance()->pushScene(gameScene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
//#if (_TARGET_PLATFORM == _PLATFORM_WP8) || (_TARGET_PLATFORM == _PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
    
    Director::getInstance()->end();
    
#if (_TARGET_PLATFORM == _PLATFORM_IOS)
    exit(0);
#endif
}
