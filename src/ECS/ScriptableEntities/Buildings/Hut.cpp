#include "Hut.hpp"

void Hut::AllocateResource() //Thanks to the base class, we already have a timer for this.
{
   Canis::Log("Allocating Pop: " + std::to_string(amount_of_units_to_create) + " every " + std::to_string(create_resource_interval));
}