//
//  GameScene.h
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//

#ifndef __TZFE__GameScene__
#define __TZFE__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    //在这里加入手势识别的事件检测
    //监听事件回调：触摸开始和触摸结束
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //滑向上下左右的方法
    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();
    //创建卡片
    void createCardSprite(cocos2d::Size size);
private:
    //点击元素
    int firstX,firstY,endX,endY;
};

#endif /* defined(__TZFE__GameScene__) */
