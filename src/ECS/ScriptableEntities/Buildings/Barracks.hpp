#pragma once
#include "HutBase.hpp"



class Barracks : public HutBase {
private:
   
public:
Barracks() {
        max_health = 80;
        current_health = 0;
        create_resource_interval = 45;
        
    }
void AllocateResource();

};