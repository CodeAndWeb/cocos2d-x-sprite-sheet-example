#include "HelloWorldScene.h"


USING_NS_CC;


Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cityscene.plist");

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    
    // background
    auto background = Sprite::createWithSpriteFrameName("background.png");
    background->setPosition(origin.x + visibleSize.x / 2,origin.y + visibleSize.y/2);
    this->addChild(background);

    // sprite
    auto frames = getAnimation("capguy/walk/%04d.png", 8);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    background->addChild(sprite);
    sprite->setPosition(100,620);

    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/8);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    auto movement = MoveTo::create(10, Vec2(2148,620));
    auto resetPosition = MoveTo::create(0, Vec2(-150,620));
    auto sequence = Sequence::create(movement, resetPosition, NULL);
    sprite->runAction(RepeatForever::create(sequence));
    
    return true;
}


Vector<SpriteFrame*> HelloWorld::getAnimation(const char *format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}
