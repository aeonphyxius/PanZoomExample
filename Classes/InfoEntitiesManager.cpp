#include "InfoEntitiesManager.h"
#include "InfoEntity.h"

// singleton stuff
static InfoEntitiesManager * _instance = nullptr;

InfoEntitiesManager* InfoEntitiesManager::getInstance()
{
	if (!_instance)
	{
		_instance = new (std::nothrow) InfoEntitiesManager();
	}

	return _instance;
}

InfoEntitiesManager::InfoEntitiesManager()
{
	_itemsContainer = Node::create();
	_itemsContainer->setPosition(Vec2::ZERO);
}

void InfoEntitiesManager::buildInfoItems(Size mapSize)
{
	// 
	// Madison Sq. Garden mark	
	//
	auto msgText = string("Madison Square Garden is a multi-purpose indoor arena in the New York City borough of Manhattan, New York");
	
	auto infoEntity = new InfoEntity(msgText);
	infoEntity->setPosition(
		Vec2( (1450 - mapSize.width / 2),
			  (mapSize.height / 2) - 1650));

	infoEntity->addToMainNode( _itemsContainer );


	// 
	// Statue of Liberty	
	//
	msgText = string("The Statue of Liberty (Liberty Enlightening the World; French: La Liberte eclairant le monde) is a colossal neoclassical sculpture on Liberty Island in New York Harbor in New York City, in the United States");

	infoEntity = new InfoEntity(msgText);
	infoEntity->setPosition(
		Vec2((273 - mapSize.width / 2),
		(mapSize.height / 2) - 4373));

	infoEntity->addToMainNode(_itemsContainer);

	// 
	// Central Park
	//
	msgText = string("Central Park is an urban park in middle-upper Manhattan, New York City. Central Park is the most visited urban park in the United States as well as one of the most filmed locations in the world.");

	infoEntity = new InfoEntity(msgText);
	infoEntity->setPosition(
		Vec2((2219 - mapSize.width / 2),
		(mapSize.height / 2) - 463));

	infoEntity->addToMainNode(_itemsContainer);
}

Node * InfoEntitiesManager::getItemsContainer()
{
	return _itemsContainer;
}

