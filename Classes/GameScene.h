//
//  GameScene.h
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//

#ifndef __TZFE__GameScene__
#define __TZFE__GameScene__

#include "CommonConfig.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
//
    CREATE_FUNC(GameScene);

//    //创建卡片
    void createGameScene(cocos2d::Size size,int line,int row,int buttonNum);
    
    Sprite* createNumberSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY,int tag);
private:
    //点击元素
//    int firstX,firstY,endX,endY;
    int line,row,buttonNum;
};

#endif /* defined(__TZFE__GameScene__) */
