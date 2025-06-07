#include "Farm.hpp"

void Farm::AllocateResource() //Thanks to the base class, we already have a timer for this.
{
    Canis::Log("Allocating Pollen: " + std::to_string(amount_of_pollen_to_earn) + " every " + std::to_string(create_resource_interval));
}