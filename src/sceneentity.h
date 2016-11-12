#pragma once

#include "material.h"
#include "intersection.h"
#include "ray.h"

/// <summary>
/// A SceneEntity is an abstract superclass representing an object in a scene.
/// </summary>
class SceneEntity
{
public:

    /// Empty destructor.
    virtual ~SceneEntity() {}

    /// <summary>
    /// The material for this SceneEntity 
    /// </summary>
    Material material;
    
    /// <summary>
    /// Matrix for converting from object coordinates to world coordinates.
    /// </summary>
    glm::mat4 objectToWorld;

    /// <summary>
    /// Matrix for converting from world coordinates to object coordinates.
    /// </summary>
    glm::mat4 worldToObject;

    /// <summary>
    /// Pure virtual (abstract) intersection method.
    /// Tests this SceneEntity against the given Ray to determine whether the Ray 
    /// intersects the SceneEntity between the Ray's start and end points.  If so,
    /// the Ray's end point is updated to the intersection point nearest the 
    /// origin of the ray, and the Intersection object is updated to contain
    /// all the information about the intersection including the normal vector
    /// to the surface at the intersection point, and a pointer to this SceneEntity.
    /// Then it returns true.
    ///
    /// If there is no valid intersection between the Ray's start and end, this
    /// method returns false, and neither parameter is altered in any way.
    /// </summary>
    ///
    /// <param name="ray">The ray to test.  The Ray's end point is updated if 
    ///   there is a valid intersection.</param>
    /// <param name="inter">This object is updated with information about the 
    ///   intersection if there is a valid intersection.  Otherwise it is 
    ///   unchanged.</param>
    /// <returns>True if the Ray intersects this within the start and 
    ///   end points of the Ray.</returns>
    virtual bool intersect( Ray & ray, Intersection & inter ) = 0;
};
