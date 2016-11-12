//
//  Rebecca Johnson
//  CSCE 412 Computer Graphics
//  Wolff
//  5 May 2016
//
//  file name: scene.cpp
//  Resources: http://stackoverflow.com/questions/23318875/iterating-through-a-vector-of-pointers
//

#include "scene.h"
#include <iostream>

/// <summary>
/// Deallocates all SceneEntity objects, and clears the vector.
/// </summary>
Scene::~Scene(){
    if ( !objects.empty() ) {
        objects.clear();
        for (std::vector<SceneEntity*>::iterator i=objects.begin(); i != objects.end(); i++) {
            delete *i;
        }

    }if ( !lights.empty() ){
        lights.clear();
        for (std::vector<PointLight*>::iterator i=lights.begin(); i != lights.end(); i++) {
            delete *i;
        }
    }
}
    
/// <summary>
/// Add the given SceneEntity to this Scene.
/// </summary>
/// <param name="e">A pointer to the SceneEntity to add to this Scene.</param>
void Scene::add(SceneEntity * e){
    objects.push_back( e );
}

/// <summary>
/// Add the given PointLight to this Scene.
/// </summary>
/// <param name="l">A pointer to the PointLight to add to this Scene.</param>
void Scene::add(PointLight * l){
    lights.push_back( l );
}

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
bool Scene::intersect( Ray & ray, Intersection & inter ){
    bool hit = false;
    for (std::vector<SceneEntity*>::iterator i=objects.begin(); i != objects.end(); i++) {
        if( (*i)->intersect(ray, inter) )
            hit = true;
    }
    return hit;
}

