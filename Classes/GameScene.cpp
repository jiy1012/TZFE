//
//  GameScene.cpp
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//

#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    createGameScene(Director::getInstance()->getVisibleSize(), 10, 5, 5);
    return true;
}
void GameScene::createGameScene(cocos2d::Size size,int line,int row,int buttonNum)
{
	//求出单元格的宽度和高度
    int oneWidth = (size.width-50)/row;
	int oneHeight = (size.height-50)/line;
    int one = MIN(oneWidth, oneHeight);
    int tag = 1;
	//4*4的单元格
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<line; j++)
		{
            int rand = random()%buttonNum+1;
//			Sprite* card = createNumberSprite(rand, one, one, one*i+10, one*j+10,tag);
            tag++;
//			addChild(card);
		}
	}
}

Sprite* createNumberSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY,int tag)
{
    auto numberSprite = Sprite::create();
    numberSprite->setPosition(Point(CardSpriteX,CardSpriteY));
    
    //加入中间字体
    auto TTFumber = LabelTTF::create(ITOA(numbers),"",20);
    TTFumber->setPosition(Point(numberSprite->getContentSize().width/2,numberSprite->getContentSize().height/2));
    TTFumber->setTag(tag);
    numberSprite->addChild(TTFumber);
    return numberSprite;
}
