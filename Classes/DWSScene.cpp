//
//  DWSScene.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#include "DWSScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
DWSScene* DWSScene::s_DWSScene = NULL;

DWSScene* DWSScene::shared()
{
    if (NULL == s_DWSScene) {
        s_DWSScene = new DWSScene();
    }
    return s_DWSScene;
}


Sprite* DWSScene::DWSLogoDisplay()
{
    Size winSize = Director::getInstance()->getWinSize();
    auto DWSSprite = Sprite::create();
    DWSSprite->setContentSize(Size(winSize.width/2,winSize.height/2));
    DWSSprite->setPosition(Vec2(winSize.width/2,winSize.height/2));
    
    auto pSprite = Sprite::create("DWS.LOGO.png");
    pSprite->setPosition(Vec2(DWSSprite->getContentSize().width/2, DWSSprite->getContentSize().height/2) );
    auto pLabel = LabelTTF::create("DWS，为爱而生", "", 25);
    pLabel->cocos2d::Node::setPosition(Vec2(DWSSprite->getContentSize().width/2, DWSSprite->getContentSize().height/2-pSprite->getContentSize().height));
    
    FadeOut* pFadeOutS = FadeOut::create(1.0f);
    FadeOut* pFadeOutL = FadeOut::create(1.0f);
    FiniteTimeAction* pSeqS = Sequence::create(pFadeOutS,NULL);
    FiniteTimeAction* pSeqL = Sequence::create(pFadeOutL,NULL);
    
    pSprite->runAction(pSeqS);
    pLabel->runAction(pSeqL);
    
    DWSSprite->addChild(pSprite);
    DWSSprite->addChild(pLabel);
    
    return DWSSprite;
}



