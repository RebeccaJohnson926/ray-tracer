#pragma once

#include <glm/glm.hpp>

class PointLight
{
public:
  /// The position of this PointLight (a point)
  glm::vec3 position;

  /// The intensity of this PointLight (a RGB  value)
  glm::vec3 intensity;

  /// <summary>
  /// Create a PointLight at (0,0,0) with intensity (100,100,100)
  /// </summary>
  PointLight() : position(0), intensity(100) { }
};
