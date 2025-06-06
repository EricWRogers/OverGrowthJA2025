#pragma once



struct HealthComponent
{
    float currentHealth = 0.0f;
    float maxHealth = 10.0f;
};

namespace Health
{
    void ResetHealth(Canis::Entity _target)
    {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth = healthComponent.maxHealth;
    }

    void AddHealth(Canis::Entity _target, float _amount)
    {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth += _amount;

        if(healthComponent.currentHealth > healthComponent.maxHealth)
        {
            healthComponent.currentHealth = healthComponent.maxHealth;
        }
    }

    void Damage(Canis::Entity _target, float _amount) {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth -= _amount;

        if (healthComponent.currentHealth < 0.0f)
        {
            _target.Destroy();
        }
    }

    void Annihilation(Canis::Entity _target)
    {
        HealthComponent& healthComponent = _target.GetComponent<HealthComponent>();
        healthComponent.currentHealth = 0;

        _target.Destroy();
    }
};