#include "HelloWorldScene.h"

#include "DWSScene.h"

#include "GameScene.h"

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
    pStratButton->setPosition(Vec2(WIN_WIDTH/4, WIN_HEIGHT/4));
    pStratButton->setScale(scale);
    auto pExitButton = MenuItemImage::create("exitButton.png", "exitButtonSelected.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    pExitButton->setPosition(Vec2(WIN_WIDTH/2, WIN_HEIGHT/4));
    pExitButton->setScale(scale);
    auto pMenu = Menu::create(pStratButton,pExitButton,NULL);
    pMenu->setPosition( Vec2(0, 0) );
    this->addChild(pMenu, 1);
}


void HelloWorld::startGame(cocos2d::Ref* pSender)
{
    CCLOG("start game");
    Scene* gameScene = GameScene::createScene();
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
