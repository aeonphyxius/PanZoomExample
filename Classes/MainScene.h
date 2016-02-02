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

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

/**
* MainScene builds the main Scene / layer of this example
*
* Builds the main layer, close menu, Pan / zoom Layer and all information points
*
*/
class MainScene : public cocos2d::Layer
{
public:
	/**
	* Creates an empty MainScene
	*
	* @return An autoreleased MainScene object.
	*/
    static cocos2d::Scene* createScene();

	/**
	* Initializes the main example scene, adding all needed elements
	*
	* @return True if the initialization have succeeded.
	*/
    virtual bool init();
    
	/**
	* Callback function to be assined in close button menu
	*
	* @param   pSender A reference to the object sending this callback
	*/
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
	CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
