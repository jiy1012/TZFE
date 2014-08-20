//
//  DWSScene.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#ifndef __ClassCocos2d_x__DWSScene__
#define __ClassCocos2d_x__DWSScene__

#include "CommonConfig.h"

class DWSScene : public Layer
{
public:

    static DWSScene* shared();
    
    static Sprite* DWSLogoDisplay();
    
    Sprite* DWSTitleHeroDisplay();
    
    Scene* DWSHeroShow();
    
private:
    static DWSScene* s_DWSScene;
};


#endif /* defined(__ClassCocos2d_x__DWSScene__) */
