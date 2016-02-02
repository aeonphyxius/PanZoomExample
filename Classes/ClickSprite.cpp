#include "ClickSprite.h"

void ClickSprite::onEnter()
{
	Sprite::onEnter();

	_initPosition = this->getPosition();
	
	// Ad the onTouchesEnded event into this ClickSprite
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(ClickSprite::onTouchesEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ClickSprite::onExit()
{
	// Clean up events and exit
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->removeEventListenersForTarget(this, true);

	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	Sprite::onExit();
}


void ClickSprite::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event* event)
{	
	// Only when 1 touch event is being released ( otherwise is Pan / Zoom action)
	if (touches.size() == 1)
	{	
		if (checkTouchEvent(touches[0]->getLocation()))
		{
			onTouchesEndedAction();		
		}
	}
}

bool ClickSprite::checkTouchEvent(Vec2 touchPosition)
{
	// Get the touch & click points in the Pan & Zoom layer coordinates
	Vec2 normalizedPoint = this->getParent()->convertToNodeSpace(touchPosition);
	Rect spriteBB = Rect(_initPosition.x, _initPosition.y, this->getContentSize().width, this->getContentSize().height);

	// Check if the normalized point is within our sprite margins
	if (spriteBB.containsPoint(normalizedPoint))
	{
		return true;
	}

	return false;
}