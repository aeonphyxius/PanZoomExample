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
#ifndef __INFO_ENTITIES_MANAGER_H__
#define __INFO_ENTITIES_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* InfoEntitiesManager is a class containing all Information Entities for a given Map
*
* Will create all items "hard-coded" in order to better understand how this example
* works. Also will manage the main Node that contains all Information Entities (container)
*/

class InfoEntitiesManager
{
public:

	/** returns a shared instance of the Information Entities manager */
	static InfoEntitiesManager *getInstance();

	virtual ~InfoEntitiesManager() {};

	/**
	* Builds this test information items using the map size as a reference
	* to locate all entities. Mostly used hardcoded values
	*
	* @param mapSize Map size to be used as a reference for locating the entitues
	*/
	void buildInfoItems(Size mapSize);

	/**
	* Main node getter function
	*
	* @return The main Information Entities Node container (will all the info points)
	*/
	Node * getItemsContainer();

private:
	/** Private constructor / singleton implementation */
	InfoEntitiesManager();

	Node * _itemsContainer;		/* Main node for all information Entities Manager (container) */

};

#endif // __INFO_ENTITIES_MANAGER_H__