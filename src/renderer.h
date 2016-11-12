#pragma once

#include <string>
#include "scene.h"

class Camera;

/// <summary>
/// A Renderer object is responsible for the core rendering process.
/// The render() method implements the core rendering process.
/// </summary>
class Renderer
{
public:
  /// <summary>
  /// Initializes a Renderer with the given Scene and Camera.  This Renderer
  /// does not retain ownership of them, it is up to the caller to delete them
  /// after the render process is finished.
  /// </summary>
  ///
  /// <param name="scn">The Scene to render.</param>
  /// <param name="cam">The Camera used to view the Scene.</param>
  /// <param name="bgColor">The background color for rays that miss any geometry.</param>
  Renderer( Scene * scn, Camera *cam, std::string outFile, const glm::vec3 & bgColor = glm::vec3(0.5f), int maxD  = 7 );

  /// <summary>
  /// Renders the scene and writes the finished image to the file.
  ///
  /// This method will loop over each pixel and call Li to determine the
  /// color for that pixel.  Then, the resulting color will be written to
  /// the Camera's film by calling the expose method on the Film object.
  ///
  /// Once the render is complete, the Film is written to the output file.
  /// </summary>
  void render();

private:

  /// <summary>
  /// Returns the radiance arriving at the origin of the given ray.
  ///
  /// It computes this value by calling intersect on the Scene object, and if
  /// it returns true, this method returns the value of the albedo of the
  /// material of the object that was intersected.  Otherwise, this method
  /// returns the background color.
  /// </summary>
  /// <param name="r">The Ray.</param>
  /// <returns>The radiance along the given ray</returns>
  glm::vec3 Li( Ray & r );
    
  /// <summary>
  /// Returns whether or not the intersection point is visible from the
  /// given PointLight. It returns true if the point is NOT visible from the
  /// position of the PointLight (occluded).
  ///
  /// It does this by creating a Ray that has its origin at the intersection point,
  /// and points towards the PointLight. The start and end of the ray is set to
  /// Ray.epsilon and the location of the PointLight respectively. The latter
  /// is important because we do not want an intersection beyond the light
  /// source. Occlusion is tested by simply calling the intersect method on the Scene.
  /// </summary>
  ///
  /// <param name="inter">The Interssection object containing the point to test
  /// for occlusion.</param>
  /// <param name="light">The PointLight to test against.</param>
  /// <returns>True if the PointLight is occluded from the intersection point.</returns>
  bool occluded(Intersection & inter, PointLight * light);
    
  /// The background color
  glm::vec3 background;

  /// Pointer to the Scene to render
  Scene * scene;

  /// Pointer to the Camera
  Camera * camera;

  /// The output file name
  std::string outputFileName;
    
  /// An integer that represents the maximum recursion depth for this renderer
  /// No more new reflection rays are spawned after this depth
  int maxDepth;
    
    // A boolean that keeps track of whether the ray has entered the object, is
    // inside, at the intersection point or the ray is not inside the
    // object at the intersection
    bool inside;
    
    // A float representing the refraction index of the environment the
    // objects are placed in
    float index1;
    
};
