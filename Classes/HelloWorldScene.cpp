#include "HelloWorldScene.h"
#include "ParallaxBackground.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	auto parallaxNode = ParallaxBackground::create();
    // add "HelloWorld" splash screen"
	auto sprite = Sprite::create("game_bg_01_001-hd.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	Color3B color = sprite->getDisplayedColor();
	color.r += 200;
	color.g += 191;
	color.b += 231;
	sprite->setColor(color);

	Vec2 bgSpeed(1, 0);
	
	parallaxNode->addChild(sprite, -1, bgSpeed, Vec2(0, 0));
	
	auto sprite_2 = Sprite::create("game_bg_01_001-hd.png");
	sprite_2->setAnchorPoint(Vec2(0, 0));
	Color3B color_2 = sprite_2->getDisplayedColor();
	color_2.r += 0;
	color_2.g += 162;
	color_2.b += 232;
	sprite_2->setColor(color_2);

	Vec2 bgSpeed_2(2, 0);
	parallaxNode->addChild(sprite_2, 0, bgSpeed_2, Vec2(0, -sprite_2->getContentSize().height * 4 / 5));

	auto go = MoveBy::create(10, Vec2(-sprite->getContentSize().width, 0));
	//auto goBack = go->reverse();
	auto seq = Sequence::create(go, nullptr);
	parallaxNode->runAction((RepeatForever::create(seq)));

    // add the sprite as a child to this layer
	this->addChild(parallaxNode);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
