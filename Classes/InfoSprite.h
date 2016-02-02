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
#ifndef __INFO_SPRITE_H__
#define __INFO_SPRITE_H__

#include "cocos2d.h"
#include "ClickSprite.h"

#define IS_IMG_FILE "pointMark.png"

using namespace cocos2d;

/**
* InfoSprite is a 2d image / sprite class that can recieve touch events
*
* InfoSprite can be created with the image file name, or will be created
* with the deaultf image otherwise (IMG_FILE)
*
* This sprite would be located near a building that you would like to show
* some information using a msgsprite
*
* The default anchorPoint in MsgSprite is (0.5, 0.0).
* The default scale in MsgSprite is POP_UP_INIT_SCALE.
*/
class InfoSprite : public ClickSprite
{
public:
	InfoSprite() {};
	virtual ~InfoSprite() {};
	
	/**
	* Creates an empty MsgSprite with a texture (either using the default one, or
	* the one given by file name.
	*
	* @param   filename A path to image file, e.g., "pointMark.png", will use default otherwise
	* @return An autoreleased InfoSprite object.
	*/
	static InfoSprite* create(std::string fileName = IS_IMG_FILE);

	/**
	* When clicked / touched on this sprite, the callaback function will be called
	*/
	virtual void onTouchesEndedAction();

	/**
	* Assigns a function callback.
	*
	* @param   callback A function callback to be used when touch is ended
	*/
	void setClickCallback(std::function<void(void)> callback);

private:

	std::function<void(void)> _callback;	// Function that should be called when a touch event on this object
};

#endif // __INFO_SPRITE_H__