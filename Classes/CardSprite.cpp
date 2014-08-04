//
//  CardSprite.cpp
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//

#include "CardSprite.h"
USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY)
{
    CardSprite* enemy = new CardSprite();
    if(enemy && enemy->init())
    {
        enemy->autorelease();
        enemy->enemyInit(numbers, width, height, CardSpriteX, CardSpriteY);
        
        return enemy;
    }
    
    CC_SAFE_DELETE(enemy);
    return NULL;
}

bool CardSprite::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    
    return true;
}

void CardSprite::enemyInit(int numbers,int width,int height,float CardSpriteX,float CardSpriteY)
{
    //设置初始化值
    number = numbers;
    
    //加入游戏的背景颜色
    layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),width-15,height-15);
    layerColorBG->setPosition(Point(CardSpriteX,CardSpriteY));
    
    //判断如果大于0就显示，否则显示空
    if(number > 0)
    {
        //加入中间字体
        labelTTFCardNumber = LabelTTF::create(String::createWithFormat("%i",number)->getCString(),"HiraKakuProN-W6",100);
        labelTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width/2,layerColorBG->getContentSize().height/2));
        labelTTFCardNumber->setTag(8);
        layerColorBG->addChild(labelTTFCardNumber);
    }
    else
    {
        //加入中间字体
        labelTTFCardNumber = LabelTTF::create("","HiraKakuProN-W6",100);
        labelTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width/2,layerColorBG->getContentSize().height/2));
        labelTTFCardNumber->setTag(8);
        layerColorBG->addChild(labelTTFCardNumber);
    }
    
    this->addChild(layerColorBG);
}

//获取数字
int CardSprite::getNumber()
{
    return number;
}

//设置数字
void CardSprite::setNumber(int num)
{
    number = num;
    
    if(number > 0)
    {
        //获取数字重新更新数字
        labelTTFCardNumber->setString(String::createWithFormat("%i",number)->getCString());
    }
    else
    {
        labelTTFCardNumber->setString("");
    }
}
