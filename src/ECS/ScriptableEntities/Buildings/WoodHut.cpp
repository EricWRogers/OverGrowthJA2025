#include "WoodHut.hpp"

void WoodHut::AllocateResource() //Thanks to the base class, we already have a timer for this.
{
   Canis::Log("Allocating Wood: " + std::to_string(amount_of_wood_to_earn) + " every " + std::to_string(create_resource_interval));
}