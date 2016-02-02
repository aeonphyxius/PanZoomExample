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
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
/**
* Entity is a 2d image / sprite class that extends from cocos2d-x Sprite
*
* ClickSprite can be created with an image, or with a sub-rectangle of an image.
*
* To enhance its qualities will implement automatically the onTouchesEnded callback
* checking if the user's touch is between the ClickSprite limits.
*
* The default anchorPoint in ClickSprite is (0.0, 0.0).
*/
class Entity
{
public:

	Entity(){};
	virtual ~Entity(){};

	/**
	* Adds this entity elements to the main Node.
	*
	* @param mainNode Entities main node
	*/
	virtual void addToMainNode(cocos2d::Node *mainNode) = 0;
};

#endif // __ENTITY_H__