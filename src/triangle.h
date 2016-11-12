/*
 Rebecca Johnson
 CSCE 412 Computer Graphics
 Wolff
 March 18, 2016
 */

#pragma once

#include "sceneentity.h"
#include <glm/glm.hpp>
using glm::vec3;

/// <summary>
/// A SceneEntity that represents a triangle.
/// </summary>

class Triangle : public SceneEntity
{
public:
    /*
     <summary>
     Constructs a Triangle with virtices at p1, p2, and p3.
     </summary>
     
     <param name = "p1"> The first vertex of the triangle.</param>
     <param name = "p2"> The second vertex of the triangle.</param>
     <param name = "p3"> The third vertex of the triangle.</param>
    */
    Triangle( vec3 p1, vec3 p2, vec3 p3 );
    
    /*
     <summary>
    Test this triangle against the given Ray to determine whether the Ray
     intersects the triangle between the Ray's start and end points. If so,
     the Ray's end point is updated to the intersetion point neareest the 
     origin of the ray, and the Intersection object is updated to contain
     all the information about the intersection including the normal vector
     to the surface at the point, and a pointer to the triangle.
     Then it returns true.
     
     If there is no valid intersection between the Ray's start and end, this
     method returns false, and neither parameter is altered in any way.
     </summary>
     
     <param name = "ray"> The ray to test. The Ray's end point is updated if 
        there is a valid intersection.</param>
     <param name = "inter"> The object is updated with information about the 
        intersection if there is a valid intersection. Otherwise it is 
        unchanged. </param>
     <returns> True if the Ray intersects this sphere within the start and 
        end points of the Ray.</returns>
    */
    virtual bool intersect( Ray & ray, Intersection & inter );
    
    //get the first vertex of the triangle
    vec3 getPoint1() const;
    
    //get the second vertex of the triangle
    vec3 getPoint2() const;
    
    //get the third vertex of the triangle
    vec3 getPoint3() const;
    
private:
    /*
     <summary>
     The location of the first virtex of the triangle.
     </summary>
    */
    vec3 point1;
    
    /*
     <summary>
     The location of the second virtex of the triangle.
     </summary>
     */
    vec3 point2;
    
    /*
     <summary>
     The location of the third virtex of the triangle.
     </summary>
     */
    vec3 point3;
};