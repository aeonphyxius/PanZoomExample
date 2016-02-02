#include "InfoEntity.h"

InfoEntity::InfoEntity ( std::string msgText )
{
	_isMsgDisplayed = false;
	
	// Info point
	_infoSprite = InfoSprite::create( );
	_infoSprite->setClickCallback(std::bind(&InfoEntity::infoCallback, this));
	
	// MSG display control
	_msgSprite  = MsgSprite::create ( );

	// MSG text
	_infoLabel = Label::createWithSystemFont(
		msgText, 
		"Helvetica", 
		18, 
		Size(_msgSprite->getContentSize().width, _msgSprite->getContentSize().height), 
		TextHAlignment::CENTER, 
		TextVAlignment::CENTER);

	_infoLabel->setAnchorPoint(Vec2::ZERO);
	_msgSprite->addChild(_infoLabel);

}


void InfoEntity::addToMainNode( Node * mainNode )
{
	if (mainNode)
	{
		mainNode->addChild(_infoSprite, 2);
		mainNode->addChild(_msgSprite, 1);
	}
	
}

void InfoEntity::setPosition(Vec2 position)
{
	_infoSprite->setPosition(position);
	_msgSprite->setPosition(position + Vec2(_infoSprite->getContentSize().width /2, _infoSprite->getContentSize().height));
}

void InfoEntity::infoCallback()
{
	if ( _isMsgDisplayed )
	{
		_msgSprite->onPopOut();		
	}
	else
	{
		_msgSprite->onPopIn();		
	}

	_isMsgDisplayed = !_isMsgDisplayed;
}