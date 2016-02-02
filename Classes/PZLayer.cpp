#include "PZLayer.h"

PZLayer::PZLayer()
{	
	//_productFactor = 55.0f;
	_maxScale = MAX_SCALE; 
	_minScale = MIN_SCALE;	
}

PZLayer* PZLayer::create()
{
	auto pzLayer = new PZLayer;
	if (pzLayer && pzLayer->init())
	{
		pzLayer->autorelease();
		return pzLayer;
	}

	CC_SAFE_DELETE(pzLayer);
	return NULL;
}


bool PZLayer::init()
{
	if (LayerColor::initWithColor( Color4B(0, 0, 255, 0)) == false)
		return false;

	this->setAnchorPoint( Vec2::ZERO );

	_touches = Vector<Touch*>();
	
	_accelerationFactor = 0.0f;
	
	return true;
}


void PZLayer::onEnter()
{
	Layer::onEnter();
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	
	// Add touch listeners
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(PZLayer::onTouchesBegan, this);
	listener->onTouchesEnded = CC_CALLBACK_2(PZLayer::onTouchesEnded, this);
	listener->onTouchesMoved = CC_CALLBACK_2(PZLayer::onTouchesMoved, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void PZLayer::onExit()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->removeEventListenersForTarget(this, true);

	Director::getInstance()->getScheduler()->unscheduleAllForTarget( this );

	_touches.clear();	

	Layer::onExit();
}

void PZLayer::update( float dt )
{		
	// Skip smoothe panning when dt is high value
	if (dt > MAX_DT)
		return;

	LayerColor::update( dt );

	if( _touches.size() == 1 )
	{
		onAccelerate(dt);
	}

	else if( _touches.size() == 0 )
	{
		onDecelerate(dt);
	}
}

void PZLayer::onAccelerate(float dt)
{
	_accelerationFactor *= dt * ACC_FACTOR;
}

void PZLayer::onDecelerate(float dt)
{
	_accelerationFactor = fabs(_accelerationFactor);
	if (_accelerationFactor < FLT_EPSILON)
		return;

	if (_accelerationFactor < ACC_FACTOR_MARGIN)
	{
		_accelerationFactor = 0;
	}
	else
	{
		// Normalized speed = DeltaTime * PAN_SPEED (with a top speed of PAN_MAX_SPEED)
		double normilizedSpeed = (dt * PAN_SPEED);
		normilizedSpeed = normilizedSpeed > PAN_MAX_SPEED ? PAN_MAX_SPEED : normilizedSpeed;
		
		// Normalized acceleration = currentAccelerationFactor * ACC_FACTOR * NormilizedSpeed 
		double normalizedAcceleration = _accelerationFactor * ACC_NORM_FACTOR * normilizedSpeed * -1;

		// update the acceleration factor with the new normalized acceleraton and speed
		_accelerationFactor = (_accelerationFactor + normalizedAcceleration) * normilizedSpeed;

		// Get the adding distance using the current size of this layer (usually the background image)
		Point adder = _deltaSum;
		adder.x *= this->getContentSize().width;
		adder.y *= this->getContentSize().height;
		
		this->setPosition(this->getPosition() + adder * 2.5 * _accelerationFactor);		
	}
}

void PZLayer::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event* event)
{
	// store all touches in order to be processed
	for (std::vector<int>::size_type i = 0; i < touches.size(); i++)
	{
		_touches.pushBack(touches[i]);
	}

	// Reset the drag & pan data
	_deltaSum = Vec2::ZERO;
	_accelerationFactor = 0;
	gettimeofday(&_timeStamp, nullptr); // Timestamp to calculate the drag & pan
}


void PZLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event* event)
{	
	if (_touches.size() == 1) // 1 touch = we are dragging & Pan  
	{
		onTouchesMovedSingle(_touches.at(0));
	}
	else if (_touches.size() >= 2) // 2 or more touches: we want to zoom
	{
		onTouchesMovedMultipe();
	}
}

void PZLayer::onTouchesMovedSingle( Touch *touch )
{	 
	Point curTouchPosition = Director::getInstance()->convertToGL(touch->getLocationInView());
	Point prevTouchPosition = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
	
	Point deltaPosition = curTouchPosition - prevTouchPosition;

	this->setPosition(this->getPosition() + deltaPosition);

	float prevAngle = CC_RADIANS_TO_DEGREES( _prevDeltaPoint.getAngle() );
	float angle = CC_RADIANS_TO_DEGREES(deltaPosition.getAngle());
	
	if (fabs(prevAngle - angle) <= 30)
	{
		_deltaSum = Vec2::ZERO;
	}

	_prevDeltaPoint = deltaPosition;

	_deltaSum.x += deltaPosition.x / this->getContentSize().width;
	_deltaSum.y += deltaPosition.y / this->getContentSize().height;

	_accelerationFactor += _deltaSum.getLength();
}

void PZLayer::onTouchesMovedMultipe()
{
	// Get the two first touches (ig
	Touch *touch1 = (Touch*)_touches.at(0);
	Touch *touch2 = (Touch*)_touches.at(1);

	// Get current and previous touches positions
	Point curPosTouch1 = Director::getInstance()->convertToGL(touch1->getLocationInView());
	Point curPosTouch2 = Director::getInstance()->convertToGL(touch2->getLocationInView());
	Point prevPosTouch1 = Director::getInstance()->convertToGL(touch1->getPreviousLocationInView());
	Point prevPosTouch2 = Director::getInstance()->convertToGL(touch2->getPreviousLocationInView());

	// Calculate current and previous positions of PZlayer relative the anchor point
	Point curPosLayer = curPosTouch1.getMidpoint(curPosTouch2);
	Point prevPosLayer = prevPosTouch1.getMidpoint(prevPosTouch2);

	// Calculate new scale
	float prevScale = this->getScale();
	float curScale = this->getScale() * curPosTouch1.getDistance(curPosTouch2) / prevPosTouch1.getDistance(prevPosTouch2);

	this->setScale(curScale);

	// Update the position only if the scale was applied (beetwen the limits)
	if (this->getScale() != prevScale)
	{
		Point realCurPosLayer = this->convertToNodeSpaceAR(curPosLayer);
		float deltaX = (realCurPosLayer.x) * (this->getScale() - prevScale);
		float deltaY = (realCurPosLayer.y) * (this->getScale() - prevScale);

		this->setPosition(Vec2(this->getPosition().x - deltaX, this->getPosition().y - deltaY));
	}

	// If current and previous position of the multitouch's center aren't equal -> change position of the layer
	if (!prevPosLayer.equals(curPosLayer))
	{
		this->setPosition(Vec2(	this->getPosition().x + curPosLayer.x - prevPosLayer.x,
								this->getPosition().y + curPosLayer.y - prevPosLayer.y));
	}
}

void PZLayer::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event* event)
{
	//if( _isHolding ) return;

	// Delete all stored touches
	for (std::vector<int>::size_type i = 0; i < touches.size(); i++)
	{
		_touches.eraseObject(touches[i]);
	}
}


void PZLayer::setPosition( Point position )
{
	Node::setPosition( position );

	if( _panBoundsRect.equals( Rect::ZERO ) == false )
	{
		Rect boundBox;
		boundBox.origin = this->getPosition() / this->getScale();
		boundBox.size = this->getContentSize() / this->getScale();

		// OpenGL coordinate system
		float left = boundBox.getMinX();
		float right = boundBox.getMaxX();
		float top = boundBox.getMaxY();
		float bottom = boundBox.getMinY();

		float min_x = _panBoundsRect.getMinX() + boundBox.size.width;
		float max_x = _panBoundsRect.getMaxX() + boundBox.size.width;
		float min_y = _panBoundsRect.getMinY() + boundBox.size.height;
		float max_y = _panBoundsRect.getMaxY() + boundBox.size.height;

		float scale = this->getScale();
		float arLeft = min_x * scale;
		float arRight = max_x * scale - this->getContentSize().width;
		float arTop = max_y * scale - this->getContentSize().height;
		float arBottom = min_y * scale;
		
		if( left < min_x )
		{
			Node::setPosition( arLeft, this->getPosition().y );
		}

		if( right > max_x )
		{
			Node::setPosition( arRight, this->getPosition().y );
		}

		if( top > max_y )
		{
			Node::setPosition( this->getPosition().x, arTop );
		}

		if( bottom < min_y )
		{
			Node::setPosition( this->getPosition().x, arBottom );
		}
	}
}


void PZLayer::setScale( float newScale )
{

	LayerColor::setScale(MIN(MAX(newScale, _minScale), _maxScale));
	this->setPosition( this->getPosition() );
}


void PZLayer::SetPanBoundsRect(Rect newBoundsRect)
{
	_panBoundsRect = newBoundsRect;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	float wFactor = _panBoundsRect.size.width / visibleSize.width;
	float hFactor = _panBoundsRect.size.height / visibleSize.height;
	
	float minScale;

	if (wFactor > hFactor)
	{
		minScale = wFactor;
	}		
	else
	{
		minScale = hFactor;
	}
		
	setMinScale( minScale );
}

void PZLayer::setMaxScale( float maxScale )
{
	_maxScale = maxScale;
}


float PZLayer::getMaxScale()
{
	return _maxScale;
}


void PZLayer::setMinScale( float minScale )
{
	_minScale = minScale;
}


float PZLayer::getMinScale()
{
	return _minScale;
}
