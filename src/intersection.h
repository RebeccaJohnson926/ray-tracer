#pragma once

#include <glm/glm.hpp>
class SceneEntity;

/// <summary>
/// An Intersection object stores information about a ray-object intersection.
/// It stores the intersection point, the normal to the surface at the intersection,
/// and a pointer to the object that was hit.
/// </summary>
class Intersection
{
public:
    /// <summary>
    /// Inializes this Intersection to p = (0,0,0), n = (0,0,0) and entity = NULL
    /// </summary>
    Intersection() : p(0), n(0), entity(nullptr) { }

    /// <summary>
    /// The intersection point in world coordinates.
    /// </summary>
    glm::vec3 p;

    /// <summary>
    /// The surface normal at the intersection point in world coordinates.
    /// </summary>
    glm::vec3 n;

    /// <summary>
    /// A pointer to the object that was hit.
    /// </summary>
    SceneEntity *entity;
};
