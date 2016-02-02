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
#ifndef __CLICK_SPRITE_H__
#define __CLICK_SPRITE_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* ClickSprite is a 2d image / sprite class that extends from cocos2d-x Sprite
*
* ClickSprite can be created with an image, or with a sub-rectangle of an image.
*
* To enhance its qualities will implement automatically the onTouchesEnded callback
* checking if the user's touch is between the ClickSprite limits. 
*
* The default anchorPoint in ClickSprite is (0.0, 0.0).
*/
class ClickSprite : public Sprite
{
public:
	ClickSprite(){};
	virtual ~ClickSprite(){};

	/**
	* Callback function referred when the users ends a touch event.
	*
	*
	* @param   touches list of all touches that have generated this callback
	* @param   event event data
	*/
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event* event);

	/**
	* All needed intializations when entering on this ClickSprite.
	*
	* Will add the listener to this class in order to detect when a touch is beingg released 
	* on top of it.	
	*/
	virtual void onEnter();
	
	/**
	* Clean up when exiting (before destroying)
	*
	* Will clean up the listener enabled for this ClickSprite and remove all selectors
	* for this class.	
	*/
	virtual void onExit();
	
	/**
	* Implements the action when the user touches on this sprite.
	*/
	virtual void onTouchesEndedAction() = 0;

protected:
	/**
	* Checks if the last touch event is on top of this ClickSprite
	*
	* Will use its parent to normalize the touch position and get the current boundingbox
	* and with it if contains the touch normalized point
	*
	* @param   touchPosition the latest touch event position
	* @return  will return true if the touch point is within the sprite limits, false otherwise.
	*/
	bool checkTouchEvent(Vec2 touchPosition);


	Vec2 _initPosition;		// Initial sprite position (to be used when scrolling)

};

#endif // __CLICK_SPRITE_H__