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
#ifndef __MSG_SPRITE_H__
#define __MSG_SPRITE_H__

#include "cocos2d.h"
#include "ClickSprite.h"

#define MS_IMG_FILE "infoPanel.png"
#define POP_UP_TIME 0.5f
#define POP_UP_SCALE 1.0f
#define POP_UP_INIT_SCALE 0.01f

using namespace cocos2d;
using namespace std;

/**
* MsgSprite is a 2d image / sprite class that can recieve touch events
*
* MsgSprite can be created with the image file name, or will be created 
* with the deaultf image otherwise (IMG_FILE)
*
* This show a panel image that will pop in / out when showing information
* about some city point of interet
*
* The default anchorPoint in MsgSprite is (0.5, 0.0).
* The default scale in MsgSprite is POP_UP_INIT_SCALE.
*/
class MsgSprite : public ClickSprite
{
public:
	MsgSprite() {};
	virtual ~MsgSprite() {};

	/**
	* Creates an empty MsgSprite with a texture (either using the default one, or
	* the one given by file name.
	*
	* @param   filename A path to image file, e.g., "infoPanel.png", will use default otherwise
	* @return An autoreleased MsgSprite object.
	*/
	static MsgSprite* create(std::string fileName = MS_IMG_FILE);
	
	/**
	* When clicked / touched on this sprite, the msg container will Pop out (onPopOut)
	*/
	virtual void onTouchesEndedAction();

	/**
	* Pop In effect when showing the msg container (EaseBackOut)
	*/
	void onPopIn();

	/**
	* Disappearing effect ( EaseBackInOut ), making the msg container scale down and disappear	
	*/
	void onPopOut();

};

#endif // __MSG_SPRITE_H__