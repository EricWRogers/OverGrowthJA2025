#pragma once
#include "HutBase.hpp"



class WoodHut : public HutBase {
private:
   
public:
    WoodHut() {
        max_health = 80;
        current_health = 0;
        create_resource_interval = 45;

    }
float amount_of_wood_to_earn = 2;
void AllocateResource();



    
};