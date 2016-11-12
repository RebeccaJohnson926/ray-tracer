#pragma once

#include "film.h"
#include "ray.h"

class Camera
{
public:
  /// <summary>
  /// Constructs a new Camera object with the given film and field of view.
  /// The Camera is given a default position and orientation.
  /// The default position is (0,0,0), looking in the negative z direction,
  /// with the y-axis defining "up" for the Camera.
  /// </summary>
  /// <param name="filmWidth">The width of the film in pixels.</param>
  /// <param name="filmHeight">The height of the film in pixels.</param>
  /// <param name="fovy">The vertical field-of-view angle in radians.</param>
  Camera( unsigned int filmWidth, unsigned int filmHeight, float fovy );

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
  void orient( const glm::vec3 & loc, const glm::vec3 & at, const glm::vec3 & up );

  /// <returns>A pointer to this Camera's Film.</returns>
  Film * getFilm();

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
  Ray getRay( int x, int y ) const;

  /// <returns>The position of this camera.</returns>
  glm::vec3 getLocation();

private:
  /// The Film for this Camera
  Film film;

  /// The vertical field of view angle for this Camera (in radians)
  float fovy;

  /// The position of the Camera
  glm::vec3 location;

  /// The 3 vectors that define this Camera's coordinate system u, v, and n.
  glm::vec3 u, v, n;
};
