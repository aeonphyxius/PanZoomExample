#include "MsgSprite.h"


MsgSprite* MsgSprite::create(std::string fileName )
{
	auto msgSprite = new (std::nothrow) MsgSprite();

	if (msgSprite && msgSprite->initWithFile(fileName))
	{
		msgSprite->setPosition(Vec2::ZERO);
		msgSprite->setAnchorPoint( Vec2( 0.5f,0.0f ) );
		msgSprite->setScale(POP_UP_INIT_SCALE);
		msgSprite->autorelease();		

		return msgSprite;
	}

	CC_SAFE_DELETE(msgSprite);
	return NULL;

}

void MsgSprite::onPopIn()
{
	// according to parent layer (to avoid getting msgsprite manipulated scale) calculate final scale
	float parentScale = this->getParent()->getScale();	
	float popUpScale = parentScale < 1 ? parentScale * POP_UP_SCALE : POP_UP_SCALE / parentScale;

	// Apply ScaleIn action and EasyOutBack to simulate the "pop up" effect
	auto scaleIn = ScaleTo::create(POP_UP_TIME, popUpScale);
	auto easyOutBack = EaseBackOut::create(scaleIn);
	this->runAction(easyOutBack);
}

void MsgSprite::onPopOut()
{	
	// Create an effect to pop/out the container	
	auto scaleIn = ScaleTo::create( POP_UP_TIME, POP_UP_INIT_SCALE );
	auto easyOutBack = EaseBackInOut::create(scaleIn);
	this->runAction(easyOutBack);
}

void MsgSprite::onTouchesEndedAction()
{
	onPopOut();
}
