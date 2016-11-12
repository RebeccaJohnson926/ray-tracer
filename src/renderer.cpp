//
//  Rebecca Johnson
//  CSCE 412 Computer Graphics
//  Wolff
//  5 May 2016
//
//  File name: renderer.cpp
//

#include "renderer.h"
#include "film.h"
#include "camera.h"
#include <QImage>


/// <summary>
/// Initializes a Renderer with the given Scene and Camera.  This Renderer
/// does not retain ownership of them, it is up to the caller to delete them
/// after the render process is finished.
/// </summary>
///
/// <param name="scn">The Scene to render.</param>
/// <param name="cam">The Camera used to view the Scene.</param>
/// <param name="bgColor">The background color for rays that miss any geometry.</param>
Renderer::Renderer( Scene * scn, Camera *cam, std::string outFile, const glm::vec3 & bgColor, int maxD ){
    background = bgColor;
    scene = scn;
    camera = cam;
    outputFileName = outFile;
    maxDepth = maxD;
    index1 = 1.0f;
    inside = false;
}
    
/// <summary>
/// Renders the scene and writes the finished image to the file.
///
/// This method will loop over each pixel and call Li to determine the
/// color for that pixel.  Then, the resulting color will be written to
/// the Camera's film by calling the expose method on the Film object.
///
/// Once the render is complete, the Film is written to the output file.
/// </summary>
void Renderer::render(){
    Film * film = camera->getFilm();
    Ray r;
    for (unsigned int x = 0; x < film->getWidth() ; x++ ) {
        for (unsigned int y = 0; y < film->getHeight(); y++) {
            Ray r = camera->getRay(x, y);
            film->expose( x, y, Li(r) );
        }
    }
    
    QString out = QString::fromStdString(outputFileName);
    QImage qimg(film->getBytes(), film->getWidth(), film->getHeight(), QImage::Format_RGBA8888);
    qimg.save(out);
    
}

/// <summary>
/// Returns the radiance arriving at the origin of the given ray.
///
/// It computes this value by calling intersect on the Scene object, and if
/// it returns true, this method returns the radiance contributed to the ray by
/// each light source (evaluates the rendering equation with each light source).
/// Otherwise, this method returns the background color.
/// </summary>
/// <param name="r">The Ray.</param>
/// <returns>The radiance along the given ray</returns>
glm::vec3 Renderer::Li( Ray & r ){
    glm::vec3 li = background;
    glm::vec3 reflectLi = glm::vec3(0,0,0);
    glm::vec3 tranLi = glm::vec3(0,0,0);
    Intersection inter;
    
    if ( scene->intersect( r, inter ) ){
        li = glm::vec3(0,0,0);
        
        for ( std::vector<PointLight*>::iterator i = scene->lights.begin(); i != scene->lights.end(); i++ ){
            
            //Check if light is occuded. If true, do not include any light from this lightsource
            if ( occluded(inter, *i) ){
                continue;
            } //if occluded
            
            float d = glm::pow( glm::length( (*i)->position - inter.p ), 2 );//distance from the surface point to the lightsource squared
            glm::vec3 L = (*i)->intensity * (1/d) ; //L(wi) intensity of incoming light
            glm::vec3 wi = glm::normalize( (*i)->position - inter.p ); //incoming direction
            glm::vec3 wo = glm::normalize( -1.0f * r.d ); //outgoing direction
            
            li = li + inter.entity->material.brdf( wi, wo, inter.n ) * L * glm::dot( wi, inter.n ) ;
        } //for lights
        
        
        float ref = inter.entity -> material.reflectance;
        float tran = inter.entity -> material.transparency;
        
        if ( ref > 0 && inside == false) {
            //calcutate reflections
            Ray r2 = Ray( inter.p, glm::normalize( glm::reflect (r.d, inter.n ) ) );
            r2.depth = r.depth + 1;
            
            if ( r2.depth < maxDepth ){
                reflectLi = Li(r2);
            }
            reflectLi = reflectLi*ref;
        }
        if ( tran > 0 ){
            //use snell's law to calculate refraction of light ( index1 * sin(a1) = index2 * sin(a2) )
            
            glm::vec3 norm = glm::normalize(inter.n); //normal at intersection point
            glm::vec3 incident = glm::normalize(r.d); //primary ray direction
            
            float index2 = inter.entity -> material.indexRefr; //refractive index of material
            float indexRatio = index1/index2;
            
            if (inside == true){
                indexRatio = index2/index1; //invert index ratio if inside object
                norm = -norm; //flip normal if inside object if inside object
                inside = false;
            }else{
                inside = true;
            }
            
            //find angle of incident
            float cosI = dot( norm, -incident); //a1
            float sinI = glm::pow( 1.0f - cosI*cosI, 0.5f); //1 - cos^2(x) = sin^2(x)
            
            //find angle of refraction
            float sinT = indexRatio * sinI; //sin(a2) = n1/n2 * sin(a1)
            float cosT = glm::pow( 1-sinT*sinT, 0.5f);  //a2
            
            if (cosT >= 0) {
                glm::vec3 refracted = indexRatio*incident + ( indexRatio*cosI - cosT)*norm;
                Ray transmitRay = Ray(inter.p, glm::normalize(refracted));  //transmitted ray
                
                transmitRay.depth = r.depth+1;  //increment ray depth
                
                if( transmitRay.depth < maxDepth ){
                    tranLi = Li(transmitRay);    //recursively call Li on the transmitted Ray
                }
            }
            tranLi = tranLi*tran ;
        } //if transparent
        li = li + reflectLi + tranLi;
    } //if scene intersect
    inside = false;
    return li;
} //Li

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
bool Renderer::occluded(Intersection & inter, PointLight * light){
    glm::vec3 d = light->position - inter.p ;
    Ray r(inter.p, d);
    r.end = glm::length(d);
    Intersection inter1;
    if ( scene->intersect(r, inter1) ) {
        return true;
    }
    return false;
}

