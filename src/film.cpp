//
//  Rebecca Johnson
//  CSCE 412 Computer Graphics
//  Wolff
//  18 February 2016
//
//  file name: film.cpp
//

#include "film.h"
#include <iostream>
using namespace std;

/// <summary>
/// Initializes a new Film object with the given dimensions.  Allocates
/// space for the pixels, and sets all pixels to black (0,0,0).
/// </summary>
///
/// <param name="width">The width of the Film in pixels.</param>
/// <param name="height">The height of the Film in pixels.</param>
///
Film::Film( unsigned int w, unsigned int h ) :
    width(w), height(h)
{
    
    image = new unsigned char[ 4 * width * height ];
    clear(0,0,0,255);  //set all pixels to black
}

/// <summary>
/// Deallocates the memory used for the pixels.
/// </summary>
Film::~Film(){
    delete [] image; //delete
}

/// <summary>
/// Copy constructor.  Initializes this Film object as a deep copy of other.
/// </summary>
/// <param name="other">The Film object to copy</param>
Film::Film( const Film & other ) :
    width(other.width), height(other.height)
{
    image = new unsigned char[ 4 * width * height ];
    for ( unsigned int i = 0; i < 4 * width * height; i++) {
        image[i] = other.image[i];
    }
}

/// <summary>
/// Assignment operator, makes this Film a deep copy of other.  If the dimensions
/// of other do not match the dimensions of this, then the pixel array is
/// deleted and re-allocated to a size that matches that of other.  Then the
/// pixel data is copied.
/// </summary>
/// <param name="other">The Film object to copy</param>
/// <returns>A reference to this object.</returns>
Film & Film::operator=(const Film & other){
    if(this == &other) return *this;
    
    if(this->width != other.width || this->height != other.height){
        delete [] image;
        image=new unsigned char[ other.width * other.height * 4 ];
        height=other.height;
        width=other.width;
    }
    
    //copy constructor copies other to this
    for ( unsigned int i = 0; i < 4 * width * height; i++) {
        image[i] = other.image[i];
    }
    
    return *this;
}

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
void Film::expose( unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b){
    if( x < width && y < height ){
        unsigned int index = 4*((height-1-y)*width+x);
        image[index]=r;
        image[index+1]=g;
        image[index+2]=b;
    }
}

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
void Film::expose( unsigned int x, unsigned int y, glm::vec3 color){
    float max = FLT_MIN;
    if ( ( color.x < 0.0f || color.x > 1.0f) || (color.y < 0.0f || color.y > 1.0f) || ( color.z < 0.0f ||color.z > 1.0f ) ) {
        max = color.x;
        if (color.y>max) {
            if (color.y>color.z) {
                max = color.y;
            }else{
                max= color.z;
            }
        }
        color = (1/max) * color;
    }
 
    unsigned int r = (int)(255*color.x+0.5f);
    unsigned int g = (int)(255*color.y+0.5f);
    unsigned int b = (int)(255*color.z+0.5f);
    
    this->expose( x, y, r, g, b );
    
}

/// <summary>
/// Set all pixels to the given color.
/// </summary>
/// <param name="r">The red component of the color.</param>
/// <param name="g">The green component of the color.</param>
/// <param name="b">The blue component of the color.</param>
void Film::clear( unsigned char r, unsigned char g, unsigned char b, unsigned char a){
    for(unsigned int i=0; i< 4 * width * height; i=i+4){
        image[i] = r;
        image[i+1] = g;
        image[i+2] = b;
        image[i+3] = a;
    }
}

/// <returns>The width of this Film in pixels</returns>
unsigned int Film::getWidth() const{
    return width;
}

/// <returns>The height of this Film in pixels</returns>
unsigned int Film::getHeight() const{
    return height;
}

/// <returns>A pointer to the image data for this Film.  The data is stored in
///   row-major order, starting at the top of the image.  There are 3 bytes
///   per pixel, stored in RGB format. </returns>
const unsigned char * Film::getBytes() const{
    return image;
}

