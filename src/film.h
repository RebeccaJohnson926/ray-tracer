#pragma once

#include <glm/glm.hpp>

class Film
{
public:
  /// <summary>
  /// Initializes a new Film object with the given dimensions.  Allocates
  /// space for the pixels, and sets all pixels to black (0,0,0).
  /// </summary>
  ///
  /// <param name="width">The width of the Film in pixels.</param>
  /// <param name="height">The height of the Film in pixels.</param>
  ///
  Film( unsigned int width, unsigned int height );

  /// <summary>
  /// Deallocates the memory used for the pixels.
  /// </summary>
  ~Film();

  /// <summary>
  /// Copy constructor.  Initializes this Film object as a deep copy of other.
  /// </summary>
  /// <param name="other">The Film object to copy</param>
  Film( const Film & other );

  /// <summary>
  /// Assignment operator, makes this Film a deep copy of other.  If the dimensions
  /// of other do not match the dimensions of this, then the pixel array is
  /// deleted and re-allocated to a size that matches that of other.  Then the
  /// pixel data is copied.
  /// </summary>
  /// <param name="other">The Film object to copy</param>
  /// <returns>A reference to this object.</returns>
  Film & operator=(const Film & other);

  /// <summary>
  /// Set the color for a pixel to (r, g, b).
  ///
  /// It is important to note that the (x,y) coordinate provided to this method
  /// is based on a coordinate system where the origin is located at the lower-left
  /// corner of the image.  Internally, the data is stored in row-major order
  /// starting with the top row of the image.
  /// </summary>
  /// <param name="x">The x coordinate of the pixel in pixel-coordinates.</param>
  /// <param name="y">The y coordinate of the pixel in pixel-coordinates.</param>
  /// <param name="r">The red component of the color.</param>
  /// <param name="g">The green component of the color.</param>
  /// <param name="b">The blue component of the color.</param>
  void expose( unsigned int x, unsigned int y,
    unsigned char r, unsigned char g, unsigned char b);
    
  /// <summary>
  /// Set the color for a pixel to (r, g, b).
  ///
  /// It is important to note that the (x,y) coordinate provided to this method
  /// is based on a coordinate system where the origin is located at the lower-left
  /// corner of the image.  Internally, the data is stored in row-major order
  /// starting with the top row of the image.
  /// </summary>
  /// <param name="x">The x coordinate of the pixel in pixel-coordinates.</param>
  /// <param name="y">The y coordinate of the pixel in pixel-coordinates.</param>
  /// <param name="color">expects the 3 components of color between 0 and 1.</param>
  void expose( unsigned int x, unsigned int y,
              glm::vec3 color);
    
  /// <summary>
  /// Set all pixels to the given color.
  /// </summary>
  /// <param name="r">The red component of the color.</param>
  /// <param name="g">The green component of the color.</param>
  /// <param name="b">The blue component of the color.</param>
  void clear( unsigned char r, unsigned char g, unsigned char b, unsigned char a );

  /// <returns>The width of this Film in pixels</returns>
  unsigned int getWidth() const;

  /// <returns>The height of this Film in pixels</returns>
  unsigned int getHeight() const;

  /// <returns>A pointer to the image data for this Film.  The data is stored in
  ///   row-major order, starting at the top of the image.  There are 3 bytes
  ///   per pixel, stored in RGB format. </returns>
  const unsigned char * getBytes() const;

private:
  /// <summary>
  /// The image data stored in a 1-dimensional array with 3 bytes per pixel.
  /// The data is organized in row-major order, starting
  /// with the top row of the image.  Each pixel is stored in RGB format.
  /// </summary>
  unsigned char* image;

  /// The width of the image in pixels.
  unsigned int width;

  /// The height of the image in pixels
  unsigned int height;
};
