//
//  GameScene.cpp
//  TZFE
//
//  Created by 刘燚 on 14-8-2.
//
//tag分类:
//数字卡片:number*100
//数字按钮:button*1000
//结果10000
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
    CC_SAFE_RETAIN(allNumber);
    CC_SAFE_RETAIN(allChange);
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
    line = 8;
    row = 8;
    buttonNum = 7;
    createGameScene(line, row, buttonNum);
    return true;
}

void GameScene::createGameScene(int line,int row,int buttonNum)
{
	//求出单元格的宽度和高度
    int oneWidth = (VISIBLE_WIDTH)/(row+2);
	int oneHeight = (VISIBLE_HEIGHT/2)/line;
    int one = MIN(oneWidth, oneHeight);
//    CCLOG("one: %d w:%d h:%d",one,oneWidth,oneHeight);
    int tag = 1;
    int allWidth = one*(line+1);
    int allHeight = one*(row+1);
	//line 行 row 列 的单元格 横行竖列
	for(int i=0; i<line; i++)
	{
		for(int j=0; j<row; j++)
		{
            int r = (arc4random() % buttonNum) + 1;
//            int r = arc4random()%buttonNum+1;
//            CCLOG("r:%d",r);
			Sprite* numberSprite = createNumberSprite(r, one, one, one*((float)j+0.5), VISIBLE_HEIGHT-one*(i+1),tag);
            allNumber->setObject(String::createWithFormat("%d",r), tag);
            allChange->setObject(String::createWithFormat("%d",0), tag);
            numberSprite->setTag(tag*100);
            tag++;
			addChild(numberSprite);
		}
	}
//    checkAround(15,2);
    int onebtn = VISIBLE_WIDTH/(buttonNum+1);
    Vector<MenuItem*> buttonItems;
    int x = 0;
    int y = 0;
    int btnWidth = onebtn;
    int btnHeight = onebtn;
    if (onebtn < 40) {
        btnWidth = MIN(onebtn, 40);
        btnHeight = MIN(onebtn, 40);
    }
    for (int b=1; b<=buttonNum; b++) {
        x = (onebtn+2)*(b-1)+onebtn/2;
        y = (VISIBLE_HEIGHT - allHeight)-onebtn/2;
//        CCLOG("w:%d h:%d",btnWidth,btnHeight);
        MenuItemImage* buttonItem = createNumberButton(b, btnWidth,btnHeight,x,y,b*1000);
        buttonItems.pushBack(buttonItem);
    }
    
    MenuItemImage* backImg = MenuItemImage::create("backButton.png", "backButton.png", CC_CALLBACK_1(GameScene::clickBackButton, this));
    backImg->setPosition(Point(WIN_WIDTH/2,(VISIBLE_HEIGHT - allHeight)-6*btnHeight/2));
                         
    buttonItems.pushBack(backImg);
    Menu* buttonMenu = Menu::createWithArray(buttonItems);
    buttonMenu->setPosition(Vec2::ZERO);
    addChild(buttonMenu);
    
//    auto stepString = String::createWithFormat("一共用了 %d 步",0)->getCString();
//    auto TTFStep = LabelTTF::create(stepString,"",30);
//    TTFStep->setTag(10001);
//    TTFStep->setPosition(Point(TTFStep->getContentSize().width/2,TTFStep->getContentSize().height/2));
//    addChild(TTFStep);
    auto TTFResult = LabelTTF::create("","",30);
    TTFResult->setTag(10000);
    TTFResult->setPosition(Point(WIN_WIDTH/2,(VISIBLE_HEIGHT - allHeight)-3*btnHeight/2));
    addChild(TTFResult);
    

}


void GameScene::clickBackButton(CCObject* pSender)
{
    CCLog("click backClick");
    Director::getInstance()->popScene();
    
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
    clickNum = clickTag/1000;
    CCLOG("clickNumber:%d",clickNum);
    oldNumber = allNumber->valueForKey(1)->intValue();
    if (oldNumber == clickNum) {
        CCLOG("oldNumber == clickNum");
        return;
    }
    if (allChange->valueForKey(1)->intValue() == 0) {
        allChange->setObject(String::createWithFormat("%d",1), 1);
        CCLOG("oldnumber:%d",oldNumber);
        addTagToChange(oldNumber, oldNumber);
    }
    bool haveAdd = addTagToChange(clickNum, clickNum);
    if(haveAdd == false){
        CCLOG("haveAdd == false");
        return ;
    }
    stepNum++;
    DictElement* changeElement;
//    std::string allChangeString = "";
    int i = 0;
    CCDICT_FOREACH(allChange, changeElement)
    {
//        int key = changeElement->getIntKey();
//        allChangeString.append(ITOA(key));
//        allChangeString.append(":");
//        allChangeString.append(allChange->valueForKey(changeElement->getIntKey())->getCString());
//        allChangeString.append(" ");
        if(allChange->valueForKey(changeElement->getIntKey())->intValue() == 1)
        {
            i++;
            allNumber->setObject(String::createWithFormat("%d",clickNum), changeElement->getIntKey());
        }
    }
//    CCLOG("allChangeString:%s",allChangeString.c_str());
    DictElement* numberElement;
    CCDICT_FOREACH(allNumber, numberElement)
    {
        auto numSprit = getChildByTag(numberElement->getIntKey()*100);
        auto numLabel = (LabelTTF*) numSprit->getChildByTag(numberElement->getIntKey());
        numLabel->setString(allNumber->valueForKey(numberElement->getIntKey())->getCString());
    }
    if (i >= line*row) {
        std::string resString = String::createWithFormat("恭喜完成!一共用了%d步! ",stepNum)->getCString();
        CCLOG("%s",resString.c_str());
        auto TTFRes = (LabelTTF*) getChildByTag(10000);
        TTFRes->setString(resString);
        return;
    }
    std::string resString = String::createWithFormat("一共用了 %d 步",stepNum)->getCString();
    CCLOG("%s",resString.c_str());
    auto TTFStep = (LabelTTF*) getChildByTag(10000);
    TTFStep->setString(resString);
    return;
}

Sprite* GameScene::createNumberSprite(int numbers,int width,int height,float spriteX,float spriteY,int tag)
{
    auto numberSprite = Sprite::create();
    numberSprite->setPosition(Point(spriteX,spriteY));
//    numberSprite->setContentSize(Size(width,height));
//    CCLOG("Sprite x:%f y:%f w:%d h:%d n:%d",spriteX,spriteY,width,height,numbers);
    //加入中间字体
//    auto TTFNumber = LabelTTF::create(ITOA(numbers),"",25);
    auto TTFNumber = LabelTTF::create();
    TTFNumber->setFontSize(height);
    TTFNumber->setString(ITOA(numbers));
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
        int changeStatus = allChange->valueForKey(changetag)->intValue();
        int tagNumber = allNumber->valueForKey(tag)->intValue();
//        CCLOG("needup tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeStatus,tagNumber);
        if( changeStatus == 1 && tagNumber == compareNumber ){
            needadd = true;
        }
    }
    if (needleft){
        int changetag = tag-1;
        int changeStatus = allChange->valueForKey(changetag)->intValue();
        int tagNumber = allNumber->valueForKey(tag)->intValue();
//        CCLOG("needleft tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeStatus,tagNumber);
        if( changeStatus == 1 && tagNumber == compareNumber ){
            needadd = true;
        }
    }
    if (needright){
        int changetag = tag+1;
        int changeStatus = allChange->valueForKey(changetag)->intValue();
        int tagNumber = allNumber->valueForKey(tag)->intValue();
//        CCLOG("needright tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeStatus,tagNumber);
        if( changeStatus == 1 && tagNumber == compareNumber ){
            needadd = true;
        }
    }
    if (needdown){
        int changetag = tag+row;
        int changeStatus = allChange->valueForKey(changetag)->intValue();
        int tagNumber = allNumber->valueForKey(tag)->intValue();
//        CCLOG("needdown tag:%d changetag:%d inchange:%d innumber:%d",tag,changetag,changeStatus,tagNumber);
        if( changeStatus == 1 && tagNumber == compareNumber ){
            needadd = true;
        }
    }
    return needadd;
}
