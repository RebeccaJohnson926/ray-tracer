/*
 Rebecca Johnson
 CSCE 412 Computer Graphics
 Wolff
 February 26, 2016
 */

#pragma once

#include "sceneentity.h"
#include <glm/glm.hpp>

/// <summary>
/// A SceneEntity that represents a sphere.
/// </summary>
class Sphere : public SceneEntity
{
public:
    /// <summary>
    /// Constructs a sphere centered at the origin, with the given radius.
    /// </summary>
    ///
    /// <param name="r">The radius of the sphere</param>
    Sphere( float r );

    /// <summary>
    /// Constructs a Sphere centered at c, with the given radius.
    /// </summary>
    ///
    /// <param name="c">The center of the sphere</param>
    /// <param name="r">The radius of the sphere</param>
    Sphere( const glm::vec3 & c, float r );

    /// <summary>
    /// Tests this sphere against the given Ray to determine whether the Ray
    /// intersects the sphere between the Ray's start and end points.  If so,
    /// the Ray's end point is updated to the intersection point nearest the
    /// origin of the ray, and the Intersection object is updated to contain
    /// all the information about the intersection including the normal vector
    /// to the surface at the intersection point, and a pointer to this sphere.
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
    /// <returns>True if the Ray intersects this sphere within the start and
    ///   end points of the Ray.</returns>
    virtual bool intersect( Ray & ray, Intersection & inter );
    
    //get the center of the sphere (in object coordinates)
    glm::vec3 getCenter() const;
    
    
    //ge the radius of the sphere (in object coordinates)
    float getRadius() const;

private:

    /// <summary>
    /// The location (in object coordinates) of the center of the sphere.
    /// </summary>
    glm::vec3 center;

    /// <summary>
    /// The radius (in object coordinates) of the sphere.
    /// </summary>
    float radius;
};
