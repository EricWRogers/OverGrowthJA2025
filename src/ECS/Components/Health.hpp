#pragma once

#include <Canis/Entity.hpp>

struct HealthComponent
{
    float currentHealth = 0.0f;
    float maxHealth = 10.0f;
};

namespace Health
{
    inline void ResetHealth(Canis::Entity _target)
    {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth = healthComponent.maxHealth;
    }

    inline void AddHealth(Canis::Entity _target, float _amount)
    {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth += _amount;

        if(healthComponent.currentHealth > healthComponent.maxHealth)
        {
            healthComponent.currentHealth = healthComponent.maxHealth;
        }
    }

    inline void Damage(Canis::Entity _target, float _amount) {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth -= _amount;

        if (healthComponent.currentHealth < 0.0f)
        {
            _target.Destroy();
        }
    }

    inline void Annihilation(Canis::Entity _target)
    {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth = 0.0f;

        _target.Destroy();
    }
};