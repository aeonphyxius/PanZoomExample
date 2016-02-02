#include "MainScene.h"
#include "PZLayer.h"
#include "InfoEntitiesManager.h"


USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();    
	auto layer = MainScene::create();
    scene->addChild(layer);
    
    return scene;
}


bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// Close menu 
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
		
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// NYC map
	auto map = Sprite::create("new_york_map.jpg");
	map->setOpacity(150);
	map->setAnchorPoint(Vec2::ZERO);
	map->setPosition(map->getContentSize() * -0.5);

	// Pan  / Zoom layer
	auto pzLayer = PZLayer::create();	
	pzLayer->setScale(1.0f);
	pzLayer->addChild(map, -1);
	pzLayer->setPosition(Vec2::ZERO);
	pzLayer->SetPanBoundsRect(Rect(
		map->getContentSize().width * -0.5,
		map->getContentSize().height * -0.5,
		map->getContentSize().width * 1.0,
		map->getContentSize().height * 1.0));


	// Information points ( Madison Sq Garde, Statue of Libert and Central Park)
	InfoEntitiesManager::getInstance()->buildInfoItems(map->getContentSize());
	pzLayer->addChild(InfoEntitiesManager::getInstance()->getItemsContainer());


	// Add the pan / zoom layer to this scene
	this->addChild(pzLayer);

	return true;
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}