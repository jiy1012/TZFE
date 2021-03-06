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
    GameScene();
    ~GameScene();
    
    static cocos2d::Scene* createScene();
    static Scene* createScene(int l,int r,int b);//带参数创建layer
    
    virtual bool init();

    CREATE_FUNC(GameScene);
    
    bool init(int l,int r,int b);
    
    //创建场景
    void createGameScene(int line,int row,int buttonNum);
    //创建数字
    Sprite* createNumberSprite(int numbers,int width,int height,float spriteX,float spriteY,int tag);
    //创建数字按钮
    MenuItemImage* createNumberButton(int buttonNumber ,int width,int height,float positionX,float positionY,int tag );
    
    void clickBackButton(Ref* pSender);
protected:
    bool checkAround(int tag, int compareNumber);
    bool addTagToChange(int clickNumber,int compareNumber);
    void clickNumberButton(Ref* pSender);
private:
    //  行数  列数 按钮数量   上次数字   点击的数字 总步数
    int g_line,g_row,g_buttonNum,g_oldNumber,g_clickNum,g_stepNum;
    //总的tag=>数字列表
    Dictionary* allNumber;
    //改过的tag列表
    Dictionary* allChange;
//    Map<int,int> allNumber;
//    Map<int,int> allChange;
//    Map<int,std::string> allNumber;
//    Vector<int> allNumber;
//    Vector<int> allChange;
};

#endif /* defined(__TZFE__GameScene__) */
