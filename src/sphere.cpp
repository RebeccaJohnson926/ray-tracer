/*
    Rebecca Johnson
    CSCE 412 Computer Graphics
    Wolff
    February 26, 2016
*/

#include "sphere.h"
using glm::vec3;

/* summary
    Constructs a sphere centered at the origin, with the given radius.

    <param name="r">The radius of the sphere</param>
*/
Sphere::Sphere( float r ) :
    center(0,0,0)   {
        radius = r;
}

/* summary
    Constructs a Sphere centered at c, with the given radius.

    <param name="c">The center of the sphere</param>
    <param name="r">The radius of the sphere</param>
*/
Sphere::Sphere( const glm::vec3 & c, float r ) {
    center = c;
    radius = r;
}

/*  summary
    Tests this sphere against the given Ray to determine whether the Ray
    intersects the sphere between the Ray's start and end points.  If so,
    the Ray's end point is updated to the intersection point nearest the
    origin of the ray, and the Intersection object is updated to contain
    all the information about the intersection including the normal vector
    to the surface at the intersection point, and a pointer to this sphere.
    Then it returns true.

    If there is no valid intersection between the Ray's start and end, this
    method returns false, and neither parameter is altered in any way.

    <param name="ray">The ray to test.  The Ray's end point is updated if
        there is a valid intersection.</param>
    <param name="inter">This object is updated with information about the
        intersection if there is a valid intersection.  Otherwise it is
        unchanged.</param>
    <returns>True if the Ray intersects this sphere within the start and
        end points of the Ray.</returns>
*/
bool Sphere::intersect( Ray & ray, Intersection & inter ){
    float t1 = 0;
    float t2 = 0;
    
    vec3 k = ray.o - center;
    float a = glm::dot(ray.d, ray.d);
    float b = glm::dot(( (float)2 * k), ray.d);
    float c = glm::dot(k,k) - glm::pow(radius,2);
    
    float num = (glm::pow(b, 2) - 4 * a * c);
    
    if( num < 0 )
    	return false;
    
    else {
    	t1 = (-b + glm::sqrt(num)) / (2 * a);
    	t2 = (-b - glm::sqrt(num)) / (2 * a);
        
        
    	if( (t1 < ray.end) && (t1 > ray.start) && ((t1 < t2) || (t2>ray.end || t2<ray.start))){ //check if t1 is between start and end
                ray.end = t1;
                inter.p = ray.o + (ray.d * t1);
                inter.n = glm::normalize(inter.p - center);
                inter.entity = this;
        }else if( (t2 < ray.end) && (t2 > ray.start) && ((t1 > t2) || (t1>ray.end || t1<ray.start))){ //check if t2 is between start and end
                ray.end = t2;
                inter.p = ray.o + (ray.d * t2);
                inter.n = glm::normalize(inter.p - center);
                inter.entity = this;
        }else{
            return false;
        }
    	return true;
    }
    return false;
}

//<returns> vec3, the center of the sphere (in object coordinates) </returns>
vec3 Sphere::getCenter() const{
    return center;
}

//<returns the radius of the sphere </returns>
float Sphere::getRadius() const{
    return radius;
}