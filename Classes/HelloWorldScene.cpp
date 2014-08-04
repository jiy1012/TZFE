#include "HelloWorldScene.h"
#include "DWSScene.h"
#include "GameScene.h"

USING_NS_CC;

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
    
    auto DWSSprite = DWSScene::shared()->DWSLogoDisplay();
    
    FadeOut* pFadeout = FadeOut::create(1.0f);
    auto pSequence = Sequence::create(
                                      pFadeout,
                                      CallFuncN::create(CC_CALLBACK_0(HelloWorld::logoDisplayCallback,this)),
                                      NULL);
    DWSSprite->runAction(pSequence);
    this->addChild(DWSSprite, 0);
    
    /*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           _CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */
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
    auto pLabel = LabelTTF::create("神马品质 坚如磐石", "", 50);
    
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
    
    CCLOG("");
    auto title = LabelTTF::create("2048", "", 200);
    title->setPosition(Vec2(WIN_WIDTH/2,WIN_HEIGHT/2));
    this->addChild(title);
    
    auto pStratButton = MenuItemImage::create("startButton.png", "startButtonSelected.png",
                                              CC_CALLBACK_1(HelloWorld::startGame,this));
    pStratButton->setPosition(Vec2(WIN_WIDTH/4, WIN_HEIGHT/6));
    
    auto pExitButton = MenuItemImage::create("exitButton.png", "exitButtonSelected.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    pExitButton->setPosition(Vec2(WIN_WIDTH/2, WIN_HEIGHT/6));
    
    auto pMenu = Menu::create(pStratButton,pExitButton,NULL);
    pMenu->setPosition( Vec2(0, 0) );
    this->addChild(pMenu, 1);
}


void HelloWorld::startGame(cocos2d::Ref* pSender)
{
    CCLOG("start game");
    auto gameScene = GameScene::createScene();
    Director::getInstance()->pushScene(gameScene);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (_TARGET_PLATFORM == _PLATFORM_WP8) || (_TARGET_PLATFORM == _PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (_TARGET_PLATFORM == _PLATFORM_IOS)
    exit(0);
#endif
}
