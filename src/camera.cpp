//
//  Rebecca Johnson
//  CSCE 412 Computer Graphics
//  Wolff
//  5 May 2016
//
//  File name: camera.cpp
//

#include "camera.h"
#include <glm/glm.hpp>

/// <summary>
/// Constructs a new Camera object with the given film and field of view.
/// The Camera is given a default position and orientation.
/// The default position is (0,0,0), looking in the negative z direction,
/// with the y-axis defining "up" for the Camera.
/// </summary>
/// <param name="filmWidth">The width of the film in pixels.</param>
/// <param name="filmHeight">The height of the film in pixels.</param>
/// <param name="fovy">The vertical field-of-view angle in radians.</param>
Camera::Camera( unsigned int filmWidth, unsigned int filmHeight, float fovy ) :
    film(filmWidth, filmHeight), fovy(fovy), location(0,0,0) {
        n = glm::vec3( 0, 0, 1 );
        u = glm::normalize( glm::cross( glm::vec3( 0, 1, 0 ), n ) );
        v = glm::normalize( glm::cross( n, u ) );
}
    
/// <summary>
/// Orient this Camera based on the given information.  This will update the
/// position and axes of this camera such that it is positioned at loc,
/// oriented to look towards the point at, and rotated so that up is the
/// approximate upward direction for someone looking through the Camera.
/// </summary>
/// <param name="loc">The location of the Camera in world coordinates.</param>
/// <param name="at">The point toward which the Camera is pointed (in world coordinates).</param>
/// <param name="up">A vector that gives the approximate upward direction for
///  the Camera in world coordinates.</param>
void Camera::orient( const glm::vec3 & loc, const glm::vec3 & at, const glm::vec3 & up ) {
    location = loc;
    n = glm::normalize( loc - at );
    u = glm::normalize( glm::cross( up, n ) );
    v = glm::normalize( glm::cross( n,u ) );
}
    
/// <returns>A pointer to this Camera's Film.</returns>
Film * Camera::getFilm(){
    return & film;
}
    
/// <summary>
/// Returns a Ray object with its origin at the camera's position and a
/// direction that points through the center of the pixel at (x, y) on the
/// image plane.  The Ray's direction is computed as if the image plane is
/// located a distance of 1.0 from the position of the camera on the Camera's
/// negative n-axis (i.e. at -1.0 on the n-axis).  The image plane is oriented
/// perpendicular to the Camera's n axis.
///
/// The Ray is defined with its start at Ray.epsilon,
/// and its end at the maximum value for a float (default values).
///
/// x and y are pixel-based coordinates.  For example, the pixel at the lower
/// left corner of the image plane is located at pixel-coordinate (0,0).
/// The corrsponding Ray should go through the center of that pixel, but is
/// defined in world coordinates. The pixel at the upper-right of the image plane
/// is given as (w-1, h-1) in pixel coordinats where w is the width of the
/// Film and h is the height of the Film.
/// </summary>
/// <param name="x">The x coordinate on the image plane (pixel-based).</param>
/// <param name="y">The y coordinate on the image plane (pixel-based).</param>
/// <returns>A Ray object with origin at this Camera's position and direction
///   through the center of the pixel on the image plane at (x, y). </returns>
Ray Camera::getRay( int x, int y ) const{
    float w = film.getWidth();
    float h = film.getHeight();
    
    //find height and width of the film plane
    float b = 2 * glm::tan( fovy/2 );
    float a = b * ( w / h );
    
    //width and height of single pixel
    float sX = a/w; //pixel width
    float sY = b/h; //pixel height

    //find origin and direction of ray that goes through center of pixel r=O+dt
    glm::vec3 orgn = location-n;
    glm::vec3 p = (location-n) + ( ((1/2) + x)*sX - (a/2)) * u + ( ((1/2) +y) * sY - (b/2) ) * v;
    glm::vec3 d = (p-location)/(glm::length(p-location));
    Ray r( orgn, d );
    
    return r;
}
    
/// <returns>The position of this camera.</returns>
glm::vec3 Camera::getLocation(){
    return location;
}

