#pragma once
#include "HutBase.hpp"



class Barracks : public HutBase {
private:
   
public:
Barracks() {
        max_health = 80;
        current_health = 0;
        job_creation_interval = 45;
        
    }
void AllocateResource();

};