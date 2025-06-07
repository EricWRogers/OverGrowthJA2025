#include "NPC.hpp"

void NPC::OnCreate()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);

    m_isAlive = true;

    Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    //Check Job
    if(characterClass == "Civilian")
    {
        //NPC switches from doing nothing 
        ChangeCharacterClass("Worker");
        //Go To Job
    }

    Canis::Log("NPC is a " + characterClass);
}
    
void NPC::OnReady()
{
    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    wavePointsManager = &manager.GetScript<WavePointsManager>();
}
    
void NPC::OnUpdate(float _dt)
{
    if(GetInputManager().JustPressedKey(SDLK_h))
    {
        GoToJob();
    }

    MoveNPC(_dt);
}

void NPC::ChangeCharacterClass(std::string _characterClass)
{
    characterClass = _characterClass;
}

void NPC::GoToJob()
{
    {
        Canis::Log("Get To Work");

        glm::vec3 start = entity.GetComponent<Canis::Transform>().position;
        glm::vec3 end = glm::vec3(10.0f, 0.0f, 10.0f);

        int idFrom = wavePointsManager->aStar.GetClosestPoint(glm::vec3(0.0f));
        int idTo = wavePointsManager->aStar.GetClosestPoint(glm::vec3(10.0f,0.0f,10.0f));
        
        m_path = wavePointsManager->aStar.GetPath(idFrom, idTo);
        m_currentPathIndex = 0;
        
        Canis::Log(std::to_string(m_path.size()));
    }
    {
        Canis::Log("Get To Work");
        int idFrom = wavePointsManager->aStar.GetClosestPoint(glm::vec3(10.f, 0.0f, 0.0f));
        int idTo = wavePointsManager->aStar.GetClosestPoint(glm::vec3(10.0f,0.0f,10.0f));
        Canis::Log(std::to_string(wavePointsManager->aStar.GetPath(idFrom, idTo).size()));
    }
}

void NPC::MoveNPC(float time)
{
    if (!m_path.empty() && m_currentPathIndex < m_path.size())
    {
        Canis::Transform transform = entity.GetComponent<Canis::Transform>();
        glm::vec3 currentPos = transform.position;
        glm::vec3 targetPos = m_path[m_currentPathIndex];

        // Move toward next path point
        glm::vec3 direction = glm::normalize(targetPos - currentPos);
        float distance = glm::distance(currentPos, targetPos);
        float step = m_moveSpeed * time;

        if (distance <= step)
        {
            transform.position = targetPos;
            m_currentPathIndex++;
        }
        else
        {
            transform.position += direction * step;
        }
    }
}