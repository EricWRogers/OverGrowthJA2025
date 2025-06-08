#include "Temp3DSprite.hpp"
#include "Canis/Math.hpp"
#include <Canis/ECS/Components/Mesh.hpp>

  void Temp3DSprite::OnReady() {
    entity.SetPosition(glm::vec3(-100.0f, -1.0f, 0.0f));
    entity.SetRotation(glm::vec3(90.0f,90.0f,0.0f) * Canis::DEG2RAD);
    Canis::Mesh &mesh = entity.GetComponent<Canis::Mesh>();
    mesh.overrideMaterialField = true;
    mesh.overrideMaterialFields.SetFloat("uvx", 0.0f);
    mesh.overrideMaterialFields.SetFloat("uvy", 0.0f);
    mesh.overrideMaterialFields.SetFloat("uvw", 10.0f);
    mesh.overrideMaterialFields.SetFloat("uvh", 10.0f);
  }
