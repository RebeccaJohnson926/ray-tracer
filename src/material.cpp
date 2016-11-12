//
//  Rebecca Johnson
//  CSCE 412 Computer Graphics
//  Wolff
//  5 May 2016
//
//  file name: material.cpp
//

#include "material.h"

/// <summary>
/// Sets albedo to (1,1,1), glossReflect to (0,0,0), and shine to 1.0f.
/// </summary>
Material::Material() {
    albedo = glm::vec3(1.0f,1.0f,1.0f);
    glossReflect = glm::vec3(0.0f,0.0f,0.0f);
    shine = 1.0f;
    reflectance = 0.0f;
    transparency = 0.0f;
    indexRefr = 1.0f;
    
}

/// <summary>
/// The bi-directional reflectance distribution function.  This method returns
/// the fraction of the radiance that is reflected from a surface, given the
/// incoming and outgoing directions and the surface normal.  All directions
/// point away from the surface.
///
/// The equation/model used here will be described in class.
///
/// For this iteration of the project, we need to be careful to return (0,0,0)
/// when the light source direction comes from the direction "below" the surface
/// of the intersected object.  For now, return (0,0,0) when the angle between
/// n and wi is greater than 90 degrees.  We will remove this restriction in
/// the next iteration.
/// </summary>
///
/// <param name="wi">The direction of incoming radiance. (Must be normalized)</param>
/// <param name="wo">The direction of outgoing radiance. (Must be normalized)</param>
/// <param name="n">The normal to the surface.  (Must be normalized)</param>
/// <returns>The reflectance (fraction of reflected light) as a RGB value.</returns>
glm::vec3 Material::brdf( const glm::vec3 & wi, const glm::vec3 & wo, const glm::vec3 & n ){
   //return (0,0,0) if the angle between n and wi is greater than 90 degrees
    if ( glm::dot( n, wi ) < 0 ){
        return glm::vec3(0,0,0);
    }
    //calculate the brdf
    glm::vec3 r = glm::reflect( -1.0f*wi, n ) ; //pure reflection vector
    float c = glm::dot(wo, r);
    glm::vec3 glossyBRDF(0.0f);
    if( c >= 0 ){
        glossyBRDF = glossReflect * glm::pow( c, shine );
    }
    
    return albedo + glossyBRDF ;
}