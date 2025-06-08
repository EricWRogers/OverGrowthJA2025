#pragma once
#include "HutBase.hpp"



class Farm : public HutBase {
private:
   
public:
Farm() {
        max_health = 100;
        current_health = 0;
        job_creation_interval = 60;
        
    }

float amount_of_pollen_to_earn = 2;

void AllocateResource();
//Thanks to the base class, we already have a timer for this.


    
};