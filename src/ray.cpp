/*
    Rebecca Johnson
    CSCE 412 Computer Graphics
    Wolff
    February 26, 2016
*/

#include "ray.h"
#include <stdio.h>
using glm::vec3;


/* summary
    Construct a Ray object with the origin at (0,0,0) and a direction of (0,0,-1)
    The Ray's depth is initalized to zero, and epsilon is set to 1.0e-3.
    The Ray's start and end are initialized by calling reset().
*/
Ray::Ray(){
    o = vec3(0,0,0);
    d = vec3(0,0,-1);
    depth = 0;
    epsilon = 0.001;
    reset();
}

/* summary
    Construct a Ray object with the given origin and direction. 
    The Ray's depth is set to zero, and epsilon is set to 1.0e-3.
    The start and end of the Ray are initialized by calling reset().
    The Ray's direction will be normalized.

    <param name="origin">The origin of the Ray.</param>
    <param name="direction">The direction of the Ray.</param>
*/
Ray::Ray( const glm::vec3 & origin, const glm::vec3 & direction ){
    o = origin;
    d = direction;
    depth = 0;
    epsilon = 0.001;
    reset();
    
	d = glm::normalize(d);
}

/* summary
    Return the point on the Ray that is a distance d from the Ray's origin.

    <param name="t">The distance from the origin of the ray.</param>
    <returns>The point on the Ray at a distance t from the origin of the Ray.</returns>
 */
glm::vec3 Ray::at(float t) const{
    vec3 point = o + d * t;
    return point;
}

/* summary
    Resets the start and end of this Ray.  The start is set to Ray.epsilon, and 
    the end is set to the max value for a float (std::numeric_limits<float>::max()).
*/
void Ray::reset(){
    start = epsilon;
    end = std::numeric_limits<float>::max();
}