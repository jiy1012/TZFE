//
//  CardSprite.h
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//

#ifndef __TZFE__CardSprite__
#define __TZFE__CardSprite__

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite
{
public:
    //初始化的数值，宽度，高度，卡片X轴，卡片Y轴
    static CardSprite* createCardSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    
    //获取数字
    int getNumber();
    //设置数字
    void setNumber(int num);
    
private:
    //显示在界面中的数字
    int number;
    void enemyInit(int numbers,int width,int height,float CardSpriteX,float CardSpriteY);
    
    //定义显示数字的控件
    cocos2d::LabelTTF* labelTTFCardNumber;
    
    //显示背景
    cocos2d::LayerColor* layerColorBG;
};

#endif /* defined(__TZFE__CardSprite__) */
