#pragma once
#include <string>
#include <vector>


#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>

using namespace Canis;

class Resources : public Canis::ScriptableEntity {
    public:
        unsigned int food = 0;
        unsigned int wood = 0;
        unsigned int popused = 0;
        unsigned int popcap = 0;
        bool CheckCost(unsigned int f, unsigned int w, unsigned int p) {
            return (food >= f && wood >= w && popused + p <= popcap );
        }


};