#include "InfoSprite.h"


InfoSprite* InfoSprite::create(std::string fileName)
{
	auto infoSprite = new (std::nothrow) InfoSprite();

	if (infoSprite && infoSprite->initWithFile(fileName))
	{
		infoSprite->setPosition(Vec2::ZERO);
		infoSprite->setAnchorPoint(Vec2::ZERO);
		infoSprite->autorelease();		

		return infoSprite;
	}

	CC_SAFE_DELETE(infoSprite);
	return NULL;

}

void InfoSprite::setClickCallback(std::function<void()> callback)
{
	_callback = callback;
}

void InfoSprite::onTouchesEndedAction()
{
	_callback();	
}