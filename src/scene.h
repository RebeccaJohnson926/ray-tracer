#pragma once

#include <vector>
#include "sceneentity.h"
#include "pointlight.h"

class PointLight;

/// <summary>
/// A Scene object contains a list of pointers to SceneEntity objects.  It
/// retains ownership of the SceneEntity objects and will delete them when this
/// object is deleted.
/// </summary>
class Scene
{
public:
    
  /// <summary>
  /// Deallocates all SceneEntity and PointLight objects, and clears the vector.
  /// </summary>
  ~Scene();

  /// <summary>
  /// Add the given SceneEntity to this Scene.
  /// </summary>
  /// <param name="e">A pointer to the SceneEntity to add to this Scene.</param>
  void add(SceneEntity * e);
    
  ///<summary>
  ///Add the given PointLight to this Scene
  ///</summary>
  ///<param name="l">A pointer to the PointLight to add to this Scene.</param>
  void add(PointLight * l);

  /// <summary>
  /// Test the ray for intersection against all objects in this Scene.  Returns
  /// true if there was at least one intersection.  The Intersection object is
  /// updated with information about the closest intersection.
  /// </summary>
  /// <param name="ray">The ray to test for intersection.</param>
  /// <param name="inter">The Intersection object will contain information about the
  /// intersection nearest to the ray's origin if there was at least one
  /// successful intersection.</param>
  /// <returns>true if there was at least one intersection.</returns>
  bool intersect( Ray & ray, Intersection & inter );

  /// The list of pointers to SceneEntity objects
  std::vector<SceneEntity *> objects;
    
  ///The list of pointers to PointLight objects
  std::vector<PointLight *> lights;
};
