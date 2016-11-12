#pragma once

#include <glm/glm.hpp>

class Material
{
public:
  /// <summary>
  /// The base, diffuse color of the object. (Albedo means the diffuse reflectivity
  /// of an object, and is derived from the Latin meaning "whiteness".)
  /// </summary>
  glm::vec3 albedo;

  /// <summary>
  /// The glossy reflectivity of the object.  This describes how much radiance
  /// is reflected by glossy scattering.
  /// </summary>
  glm::vec3 glossReflect;

  /// <summary>
  /// This determines the shininess (or smoothness) of the surface.  Larger values create smaller
  /// specular highlights, and represent shinier surfaces.  Typical values range
  /// from 1 to 200.  A value of 0 is unrealistic and should be avoided.
  /// </summary>
  float shine;
    
  /// <summaray>
  /// This determines the reflectiveness of the surface.
  /// Typical values range from 0 to 1. 0 indecates a surface that is not reflective at all.
  ///</summary>
  float reflectance;

  /// <summaray>
  /// This determines the transoarency of the surface.
  /// Typical values range from 0 to 1. 0 indecates a surface that is not transparent at all.
  ///</summary>
  float transparency;
    
  /// <summaray>
  /// This determines the refractive index of the object.
  ///</summary>
  float indexRefr;
  
    
  /// <summary>
  /// Sets albedo to (1,1,1), glossReflect to (0,0,0), and shine to 1.0f.
  /// </summary>
  Material();

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
  glm::vec3 brdf( const glm::vec3 & wi, const glm::vec3 & wo, const glm::vec3 & n );
};
