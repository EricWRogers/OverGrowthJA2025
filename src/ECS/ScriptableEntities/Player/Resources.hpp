#pragma once
#include <string>
#include <vector>


#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>

using namespace Canis;

class Resources : public Canis::ScriptableEntity {
    public:
        unsigned int food = 5;
        unsigned int wood = 5;
        unsigned int popused = 0;
        unsigned int popcap = 0;
        bool CheckCost(unsigned int f, unsigned int w, unsigned int p) {
            return (food >= f && wood >= w && popused + p <= popcap );
        }
        void Spend(unsigned int f, unsigned int w, unsigned int p) {
            food -= f;
            wood -= w;
            popused += p;
        }

};