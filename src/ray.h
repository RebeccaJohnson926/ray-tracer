#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
    /// <summary>
    /// Construct a Ray object with the origin at (0,0,0) and a direction of (0,0,-1).
    /// The Ray's depth is initalized to zero, and epsilon is set to 1.0e-3.
    /// The Ray's start and end are initialized by calling reset().
    /// </summary>
    Ray();
    
    /// <summary>
    /// Construct a Ray object with the given origin and direction.    
    /// The Ray's depth is set to zero, and epsilon is set to 1.0e-3.
    /// The start and end of the Ray are initialized by calling reset().
    /// The Ray's direction will be normalized.
    /// </summary>
    /// <param name="origin">The origin of the Ray.</param>
    /// <param name="direction">The direction of the Ray.</param>
    Ray( const glm::vec3 & origin, const glm::vec3 & direction );

    /// <summary>
    /// Return the point on the Ray that is a distance d from the Ray's origin.
    /// </summary>
    /// <param name="t">The distance from the origin of the ray.</param>
    /// <returns>The point on the Ray at a distance t from the origin of the Ray.</returns>
    glm::vec3 at( float t ) const;

    /// <summary>
    /// Resets the start and end of this Ray.  The start is set to Ray.epsilon, and
    /// the end is set to the max value for a float (std::numeric_limits<float>::max()).
    /// </summary>
    void reset();

    /// <summary>
    /// The Ray's origin (a point).
    /// </summary>
    glm::vec3 o;

    /// <summary>
    /// This Ray's direction (a vector).  This should always be normailzed (unit
    /// vector).  The user of the Ray must assure this is the case.
    /// </summary>
    glm::vec3 d;

    /// <summary>
    /// The start of this Ray (distance from the Ray's origin).
    /// </summary>
    float start;

    /// <summary>
    /// The end of this Ray (distance from the Ray's origin).
    /// </summary>
    float end;

    /// <summary>
    /// The recursive depth of this Ray.  Primary rays that eminate from the
    /// Camera have a depth of 0.  Reflected/transmitted Rays have a depth that
    /// is one greater than the Ray that spawned them.
    /// </summary>
    int depth;

    /// <summary>
    /// A small value that is used to initialize the start of the Ray. This is used
    /// to help avoid self intersections when reflecting from a surface.
    /// </summary>
    float epsilon;
};
