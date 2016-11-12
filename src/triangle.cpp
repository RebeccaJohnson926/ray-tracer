//
//  triangle.cpp
//  
//
//  Created by Rebecca Johnson on 3/18/16.
//
//

#include "triangle.h"

/*
 <summary>
 Constructs a Triangle with virtices at p1, p2, and p3.
 </summary>
 
 <param name = "p1"> The first vertex of the triangle.</param>
 <param name = "p2"> The second vertex of the triangle.</param>
 <param name = "p3"> The third vertex of the triangle.</param>
 */
Triangle::Triangle( vec3 p1, vec3 p2, vec3 p3 ){
    point1 = p1;
    point2 = p2;
    point3 = p3;
}

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
bool Triangle::intersect( Ray & ray, Intersection & inter ){
    vec3 d = ray.d;
    vec3 s = ray.o - point1;
    vec3 e1 = point2 - point1;
    vec3 e2 = point3 - point1;
    vec3 s1 = glm::cross( d, e2 );
    vec3 s2 = glm::cross( s, e1 );
    
    float b1 = glm::dot( s1, s ) / glm::dot( s1, e1) ;
    if ( b1 < 0 || b1 > 1) {
        return false; //miss
    }
    
    float b2 = glm::dot( s2, d ) / glm::dot( s1, e1) ;
    if ( b2 < 0 || b2 > 1) {
        return false; //miss
    }
    
    if (b1+b2 > 1) {
        return false;
    }
    
    float t = glm::dot( s2, e2 ) / glm::dot( s1, e1) ;
    if (t < ray.end && t > ray.start) {
        ray.end = t;
        inter.p = ray.o + (ray.d * t);
        inter.n = glm::normalize(glm::cross( (point2 - point1), (point3 - point1) ));
        inter.entity = this;
        return true;
    }
    return false;
}

//get the first vertex of the triangle
vec3 Triangle::getPoint1() const{
    return point1;
}

//get the second vertex of the triangle
vec3 Triangle::getPoint2() const{
    return point2;
}

//get the third vertex of the triangle
vec3 Triangle::getPoint3() const{
    return point3;
}