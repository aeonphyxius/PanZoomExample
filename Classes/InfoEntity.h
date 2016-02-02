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
#ifndef __INFO_ENTITY_H__
#define __INFO_ENTITY_H__

#include "cocos2d.h"
#include "InfoSprite.h"
#include "MsgSprite.h"
#include "Entity.h"

using namespace cocos2d;

/**
* InfoEntity an entity that will show some information point in a map
*
* Will create all needed sprites and text component to display the information point and the 
* message sprite & text components
*
* The default components of this Entity are:
*	- InfoSprite: Will be located at the given position and default anchor point at (0,0)
*	- MsgSprite: Will be created and located (when setLocation) into the following position:
*				 (position + Vec2(_infoSprite->getContentSize().width /2, _infoSprite->getContentSize().height));
*	- Label: Will be created and added msgsprite, with text aligment:TextHAlignment::CENTER, TextVAlignment::CENTER);
*			 and default anchor point at (0,0)
* 
*/
class InfoEntity : Entity
{
public:

	/**
	* Creates all InfoEntity components, including the text to be displayed
	* inside the msgsprite
	* 
	* @param   msgText Text to be displayed for this map's info point
	*/
	InfoEntity( std::string msgText );
	
	virtual ~InfoEntity() {};
	
	/**
	* Callback that will be assigned to the InfoSprite component and called 
	* when the user touches the sprite	
	*/
	void infoCallback();
	
	/**
	* Assigns a new position for the whole point + msg container + text component.
	*
	* @param   position new position to be assined to this entity
	*/
	void setPosition( Vec2 position );	
	
	/**
	* Adds this entity elements to the main Node.
	*
	* @param mainNode Entities main node
	*/
	virtual void addToMainNode( Node *mainNode );

private:

	bool		_isMsgDisplayed;		/* flag to know if the message is displayed already or not */
	MsgSprite	*_msgSprite;			/* message sprite container */
	InfoSprite	*_infoSprite;			/* Map information point sprite */
	Label		*_infoLabel;			/* Label that will display the information (inside the msg sprite) */
};

#endif // __INFO_ENTITY_H__