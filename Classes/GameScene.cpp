//
//  GameScene.cpp
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//

#include "GameScene.h"
USING_NS_CC;

GameScene::GameScene(){
    line = 0;
    row = 0;
    buttonNum = 0;
    oldNumber = 0;
    clickNum = 0;
    stepNum = 0;
    allNumber = Dictionary::create();
    allChange = Dictionary::create();
}
GameScene::~GameScene(){
    line = 0;
    row = 0;
    buttonNum = 0;
    oldNumber = 0;
    clickNum = 0;
    stepNum = 0;
    CC_SAFE_RELEASE(allNumber);
    CC_SAFE_RELEASE(allChange);
}

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
    line = 10;
    row = 10;
    buttonNum = 7;
    createGameScene(line, row, buttonNum);
    return true;
}

void GameScene::createGameScene(int line,int row,int buttonNum)
{
	//求出单元格的宽度和高度
    int oneWidth = (VISIBLE_WIDTH-50)/row;
	int oneHeight = (VISIBLE_HEIGHT-50)/line;
    int one = MIN(oneWidth, oneHeight);
    int tag = 1;
    int allWidth = one*(line+1);
    int allHeight = one*(row+1);
	//4*4的单元格
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<line; j++)
		{
            int rand = random()%buttonNum+1;
			Sprite* numberSprite = createNumberSprite(rand, one, one, one*(j+1), VISIBLE_HEIGHT-one*(i+1),tag);
            allNumber->setObject(String::createWithFormat("%d",rand), tag);
            allChange->setObject(String::createWithFormat("%d",0), tag);
            tag++;
			addChild(numberSprite);
		}
	}
//    checkAround(15,2);
    int onebtn = VISIBLE_WIDTH/(buttonNum+1);
    Vector<MenuItem*> buttonItems;
    int x = 0;
    int y = 0;
    for (int b=1; b<=buttonNum; b++) {
        x = (onebtn+2)*(b-1)+onebtn/2;
        y = (VISIBLE_HEIGHT - allHeight)/2-onebtn/2;
        int btnWidth = MIN(onebtn, 40);
        int btnHeight = MIN(onebtn, 40);
        
        MenuItemImage* buttonItem = createNumberButton(b, btnWidth,btnHeight,x,y,b+1000);
        buttonItems.pushBack(buttonItem);
    }
    Menu* buttonMenu = Menu::createWithArray(buttonItems);
    buttonMenu->setPosition(Vec2::ZERO);
    addChild(buttonMenu);
}

MenuItemImage* GameScene::createNumberButton(int buttonNumber ,int width,int height,float positionX,float positionY,int tag )
{
    MenuItemImage* buttonImg = MenuItemImage::create(String::createWithFormat("button_%d.png",buttonNumber)->getCString(), String::createWithFormat("button_%d.png",buttonNumber)->getCString(), CC_CALLBACK_1(GameScene::clickNumberButton, this));
    buttonImg->setTag(tag);
    buttonImg->setPosition(Point(positionX,positionY));
    float btnScaleX = (float)width/40.0;
    float btnScaleY = (float)height/40.0;
    float scaleBtn = MIN(btnScaleX, btnScaleY);
    buttonImg->setScale(scaleBtn);
    return buttonImg;
}

void GameScene::clickNumberButton(Object* pSender)
{
    auto buttonImg = (MenuItemImage*) pSender;
    int clickTag = buttonImg->getTag();
    clickNum = clickTag - 1000;
    CCLOG("clickNumber:%d",clickNum);
    oldNumber = allNumber->valueForKey(1)->intValue();
    if (oldNumber == clickNum) {
        CCLOG("oldNumber == clickNum");
        return;
    }
    if (allChange->valueForKey(1)->intValue() == 0) {
        allChange->setObject(String::createWithFormat("%d",1), 1);
        addTagToChange(clickNum, oldNumber);
    }
    bool haveAdd = addTagToChange(clickNum, clickNum);
    if(haveAdd == false){
        CCLOG("haveAdd == false");
        return ;
    }
    DictElement* changeElement;
    CCDICT_FOREACH(allChange, changeElement)
    {
        if(allChange->valueForKey(changeElement->getIntKey())->intValue() == 1)
        {
            allNumber->setObject(String::createWithFormat("%d",clickNum), changeElement->getIntKey());
        }
    }
    
    DictElement* numberElement;
    CCDICT_FOREACH(allNumber, numberElement)
    {
        LabelTTF* TTFNumber = (LabelTTF*) getChildByTag(numberElement->getIntKey());
        TTFNumber->setString(allNumber->valueForKey(numberElement->getIntKey())->getCString());
    }
    return;
}

Sprite* GameScene::createNumberSprite(int numbers,int width,int height,float spriteX,float spriteY,int tag)
{
    auto numberSprite = Sprite::create();
    numberSprite->setPosition(Point(spriteX,spriteY));
    CCLOG("Sprite x:%f y:%f w:%d h:%d n:%d",spriteX,spriteY,width,height,numbers);
    //加入中间字体
    auto TTFNumber = LabelTTF::create(ITOA(numbers),"",20);
    TTFNumber->setPosition(Point(numberSprite->getContentSize().width/2,numberSprite->getContentSize().height/2));
    TTFNumber->setTag(tag);
    numberSprite->addChild(TTFNumber);
    return numberSprite;
}

bool GameScene::addTagToChange(int clickNumber,int compareNumber)
{
    bool haveadd = false;
    for (int i = 1; i <= allNumber->count(); i++) {
        bool addnew = false;
        addnew = checkAround(i, compareNumber);
        if (addnew == true && allChange->valueForKey(i)->intValue() == 0) {
            haveadd = true;
            allChange->setObject(String::createWithFormat("%d",1), i);
            allNumber->setObject(String::createWithFormat("%d",clickNumber), i);
            CCLOG("add %d to allChange with compare:%d click:%d",i,compareNumber,clickNumber);
        }
    }
    return haveadd;
}

bool GameScene::checkAround(int tag, int compareNumber)
{
    bool needup = true;
    bool needdown = true;
    bool needleft = true;
    bool needright = true;
    bool needadd = false;
    if (tag%row == 1) {needleft = false;};
    if (tag%row == 0){needright = false;}
    if (tag<row){needup = false;}
    if (tag>row*(line-1)){needdown = false;}
    
    if (needup){
        int changetag = tag-row;
        int changeup = allChange->valueForKey(changetag)->intValue();
        int numberup = allNumber->valueForKey(changetag)->intValue();
        CCLOG("needup tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeup,numberup);
        if( changeup == 0 && numberup == compareNumber ){
            needadd = true;
        }
    }
    if (needleft){
        int changetag = tag-1;
        int changeup = allChange->valueForKey(changetag)->intValue();
        int numberup = allNumber->valueForKey(changetag)->intValue();
        CCLOG("needleft tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeup,numberup);
        if( changeup == 0 && numberup == compareNumber ){
            needadd = true;
        }
    }
    if (needright){
        int changetag = tag+1;
        int changeup = allChange->valueForKey(changetag)->intValue();
        int numberup = allNumber->valueForKey(changetag)->intValue();
        CCLOG("needright tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeup,numberup);
        if( changeup == 0 && numberup == compareNumber ){
            needadd = true;
        }
    }
    if (needdown){
        int changetag = tag+row;
        int changeup = allChange->valueForKey(changetag)->intValue();
        int numberup = allNumber->valueForKey(changetag)->intValue();
        CCLOG("needdown tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeup,numberup);
        if( changeup == 0 && numberup == compareNumber ){
            needadd = true;
        }
    }
    return needadd;
}
