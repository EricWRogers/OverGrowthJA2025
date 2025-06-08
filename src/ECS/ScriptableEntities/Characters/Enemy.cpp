#include "Enemy.hpp"
#include "../../Components/NPCBoid.hpp"
#include "../../Components/Billboard.hpp"
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/SpriteAnimationComponent.hpp>

void Enemy::OnCreate()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);

    Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    Canis::SphereCollider &sphere = entity.GetComponent<Canis::SphereCollider>();

    sphere.layer = (unsigned int)Canis::BIT::TWO;
    sphere.mask = (unsigned int)Canis::BIT::THREE;

    m_collisionSystem = GetScene().GetSystem<Canis::CollisionSystem>();
}

void Enemy::OnReady()
{
    entity.AddComponent<NPCBoid>();
    entity.AddComponent<Billboard>();
    Canis::Sprite2DComponent &sc = entity.AddComponent<Canis::Sprite2DComponent>();
    sc.textureHandle = Canis::AssetManager::GetTextureHandle("assets/textures/knight/front/knight_idle1.png");

    Canis::SpriteAnimationComponent &sac = entity.AddComponent<Canis::SpriteAnimationComponent>();
    sac.Play("assets/animations/knight_walk_front.anim");
    sac.flipX = false;

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    m_wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void Enemy::OnUpdate(float _dt)
{
    Canis::Sprite2DComponent& sc = entity.GetComponent<Canis::Sprite2DComponent>();
    Canis::Mesh& mesh = entity.GetComponent<Canis::Mesh>();
    mesh.albedoIdOverride = sc.textureHandle.id;
    mesh.overrideMaterialField = true;
    mesh.overrideMaterialFields.SetFloat("uvx", sc.uv.x);
    mesh.overrideMaterialFields.SetFloat("uvy", sc.uv.y);
    mesh.overrideMaterialFields.SetFloat("uvw", sc.uv.z);
    mesh.overrideMaterialFields.SetFloat("uvh", sc.uv.w);

    GoTo();
    Attack();
}

void Enemy::Attack()
{
    if (m_isEntsAlive)
    {
        // entt::entity is the id of Canis::Entity
        std::vector<entt::entity> targets = m_collisionSystem->GetHits(entity);
        for (entt::entity id : targets)
        {
            Canis::Entity ent(id, &GetScene());
            HealthComponent &attackersHealth = ent.GetComponent<HealthComponent>();
            Health::Damage(ent, damage);
            glm::vec3 dir = entity.GetGlobalPosition() - ent.GetGlobalPosition();

            if (dir.z > 0.0f)
            {
                SetAnimation("assets/animations/knight_attack_front.anim", false);
            }
            else
            {
                SetAnimation("assets/animations/knight_attack_back.anim", false);
            }
            Canis::Log("Current is " + std::to_string(attackersHealth.currentHealth));
        }
    }
    else
    {
        std::vector<entt::entity> targets = m_collisionSystem->GetHits(entity);
        for (entt::entity id : targets)
        {
            Canis::Entity townHall(id, &GetScene());
            HealthComponent &attackersHealth = townHall.GetComponent<HealthComponent>();
            Health::Damage(townHall, damage);
            glm::vec3 dir = entity.GetGlobalPosition() - townHall.GetGlobalPosition();

            if (dir.z > 0.0f)
            {
                SetAnimation("assets/animations/knight_attack_front.anim", false);
            }
            else
            {
                SetAnimation("assets/animations/knight_attack_back.anim", false);
            }
            Canis::Log("Current is " + std::to_string(attackersHealth.currentHealth));
        }
    }
}

void Enemy::GoTo()
{
    if (m_path.size() == 0)
    {
        m_index = 0;
        bool foundTarget = false;

        int idFrom = m_wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;

        std::vector<Canis::Entity> ents = entity.GetEntitiesWithTag("ENT");

        if (ents.size() == 0)
        {
            m_isEntsAlive = false;
        }
        else
        {
            m_isEntsAlive = true;
        }

        if (m_isEntsAlive)
        {
            float closestDistance = std::numeric_limits<float>::max();
            glm::vec3 npcPos = entity.GetGlobalPosition();

            for (Canis::Entity &ent : ents)
            {
                float dist = glm::distance(ent.GetGlobalPosition(), npcPos);
                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    idTo = m_wavePointsManager->aStar.GetClosestPoint(ent.GetGlobalPosition());
                    foundTarget = true;
                }
            }
        }
        else
        {
            std::vector<Canis::Entity> towns = entity.GetEntitiesWithTag("TOWN");
            float closestDistance = std::numeric_limits<float>::max();
            glm::vec3 npcPos = entity.GetGlobalPosition();

            for (Canis::Entity &town : towns)
            {
                float dist = glm::distance(town.GetGlobalPosition(), npcPos);
                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    idTo = m_wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());
                    foundTarget = true;
                }
            }
        }

        if (foundTarget)
        {
            m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);
        }

        if (m_path.empty())
        {
            return;
        }
    }

    entity.GetComponent<NPCBoid>().target = m_path[m_index];
    glm::vec3 currentPos = entity.GetGlobalPosition();
    glm::vec3 moveDir = m_path[m_index] - currentPos;

    if (abs(moveDir.z) > 0.1f)
    {
        if (moveDir.z > 0.0f)
        {
            SetAnimation("assets/animations/knight_walk_back.anim", false);
        }
        else
        {
            SetAnimation("assets/animations/knight_walk_front.anim", false);
        }
    }

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    {
        m_index++;
    }

    if (m_index >= m_path.size())
    {
        m_path.clear();
        return;
    }
}

void Enemy::SetAnimation(std::string _path, bool _flipX = false)
{
    auto &anim = entity.GetComponent<Canis::SpriteAnimationComponent>();
    if (animationName != _path)
    {
        anim.Play(_path);
        anim.flipX = _flipX;
        animationName = _path;
    }
}