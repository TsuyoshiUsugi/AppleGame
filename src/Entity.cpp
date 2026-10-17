#include "Entity.h"

Rectangle Entity::GetBounds() const
{
	return { pos.x, pos.y, width, height };
}