/****************************************************************************
Copyright (c) 2016 Alejandro Santiago Varela

http://www.aeonphyxius.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef _PZ_LAYER_H_
#define _PZ_LAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

#define ACC_FACTOR 38
#define ACC_FACTOR_MARGIN 0.004
#define MIN_SCALE 1.0f
#define MAX_SCALE 5.0f
#define MAX_DT 0.02f
#define PAN_SPEED 60
#define PAN_MAX_SPEED 0.99
#define ACC_NORM_FACTOR 0.025
/**
* PZLayer is a LayerColor extension class that implements Pan & Zoom actions
*
* MsgSprite can be created with the image file name, or will be created
* with the deaultf image otherwise (IMG_FILE)
*
* There is some pre-defined values for PAN & ZOOM actions :
*	- Min scale: 1 (MIN_SCALE)
*	- Max scale: 5 (MAX_SCALE)
*	- Acceleration factor: 38 (ACC_FACTOR)
*	- Acceleration factor margin: 0.04 (ACC_FACTOR_MARGIN)
*	- Maximun delta time allowed (to have a smooth pan): 0.02 (MAX_DT)
*	- Maximun delta time allowed (to have a smooth pan): 0.02 (MAX_DT)
*   - Pan displacement speed 60 ( PAN_SPEED )
*	- Maximun Pan displacement speed 0.99f ( PAN_SPEED )
*
* The default anchorPoint in PZLayer is (0.0, 0.0).
* 
*/
class PZLayer : public LayerColor
{
public:
	PZLayer();
	virtual ~PZLayer() {};

	/**
	* Creates an empty PZLayer
	*
	* @return An autoreleased PZLayer object.
	*/
	static PZLayer* create();
	
	/**
	* Initializes the PZLayer and default PAN & zoom values
	*/
	virtual bool init();

	/**
	* OnEnter initializes all touch events for this Layer 
	*	- onTouchesBegan
	*	- onTouchesEnded
	*	- onTouchesMoved
	*/
	virtual void onEnter();
	
	/**
	* Remove all listeners before exiting this PZLayer 
	*/
	virtual void onExit();
	
	/**
	* When updating this layer, if no touches are stored previously, decelarate the pan effect
	* if needed or accelerate if one touch is enabled
	* 
	*/
	virtual void update( float dt );


	/**
	* onTouchesBegan callback event
	*
	* When a touch/es are detected, store them to proccess them
	* an reset drag & pan data
	*
	* @param  touches list of touch/es that have raised this event
	* @param  event event info
	*/
	virtual void onTouchesBegan( const std::vector<Touch*>& touches, Event* event );
	
	/**
	* onTouchesEnded callback event
	*	
	* Clean up Touch events information
	*
	* @param  touches list of touch/es that have raised this event
	* @param  event event info
	*/
	virtual void onTouchesEnded( const std::vector<Touch*>& touches, Event* event );
	
	/**
	* onTouchesMoved callback event (when one or more toches have moved)
	*
	* When there is only a single touch(Pan / move ) -> onTouchesMovedSingle
	* When 2 or more touches (zoom IN / OUT) -> onTouchesMovedMultipe
	*
	* @param  touches list of touch/es that have raised this event
	* @param  event event info
	*/
	virtual void onTouchesMoved( const std::vector<Touch*>& touches, Event* event );
	

	/**	
	* Once a single touch is detected and is moving, drag & pan this layer
	*
	* @param   touch Event data that is dragging the layer (Pan)
	*/
	void onTouchesMovedSingle( Touch *touch );

	/**
	* When the user is moving 2 or more touchs points. It will only use the first 2 to create
	* the ZOOM / UN OUT effect
	*	
	*/
	void onTouchesMovedMultipe();

	/**
	* Sets the bounding box (Rect) of this layer, and sets the new minScale
	*
	* @param   newBoundsRect to be assign and from which will get the new minScale
	*/
	void SetPanBoundsRect( Rect newBoundsRect );
		
	/**
	* Deccelerates when the user is panning and the touches have been released
	*
	* The phormula to deccelerate is:	
	*	newPposition = (currentPosition * adder * 2.5 * accelerationFactor)
	*	where:		
	*		// _accelerationFactor = (_accelerationFactor + normalizedAcceleration) * normilizedSpeed;
	*		// adder = _deltaSum (delta touch displacement) + layerSize
	*		// Normalized acceleration = currentAccelerationFactor * ACC_FACTOR * NormilizedSpeed 
	*		// Normalized speed = DeltaTime * PAN_SPEED (with a top speed of PAN_MAX_SPEED)
	*
	* @param   filename A path to image file, e.g., "infoPanel.png", will use default otherwise	
	*/	
	void onDecelerate(float dt);
	
	/**
	* Accelerates when the user is dragging and releasing ( PAN )
	*
	* The phormula to accelerate is:	
	*	_accelerationFactor *= dt * ACC_FACTOR;
	* @param	dt detla time
	*/
	void onAccelerate(float dt);


	// Setters and getters
	void setMaxScale( float maxScale );
	float getMaxScale();
	void setMinScale(float minScale);
	float getMinScale();	
	virtual void setPosition(Point position);
	virtual void setScale(float newScale);

private:

	float			_maxScale;				/* Max scale allowed when zoom out */
	float			_minScale;				/* Min scale allowed when zoom in */
	Point			_deltaSum;				/* Accumulated delta displacement when panning */
	Point			_prevDeltaPoint;		/* When draggin and moving the layer, previous touch point */
	double         _accelerationFactor;		/* Acceleration factor to be applied when drag & Pan */
	Vector<Touch*> _touches;				/* List of touches to be procesed*/
	timeval        _timeStamp;				/* timestamp to be used to calculate drag & pan */
	Rect           _panBoundsRect;			/* Bounding box / rect of this PZLayer */

};
#endif /*_PZ_LAYER_H_*/