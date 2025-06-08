#pragma once
#include "HutBase.hpp"



class Hut : public HutBase {
private:
   
public:
Hut() {
        max_health = 80;
        current_health = 0;
        job_creation_interval = 45;
        
    }
float amount_of_units_to_create = 1;

void AllocateResource();



    
};