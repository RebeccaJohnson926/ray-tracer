//
//  Rebecca Johnson
//  CSCE 412 Computer Graphics
//  Wolff
//  5 May 2016
//
//  File name: main.cpp
//  Resources: http://stackoverflow.com/questions/1814189/how-to-change-string-into-qstring
//

#include "renderer.h"
#include "sphere.h"
#include "camera.h"
#include "triangle.h"
#include "scene.h"
#include "pointlight.h"
#include <iostream>
using namespace std;


int main(){
    Scene * scn = new Scene;

    Sphere * s = new Sphere(glm::vec3(1, -1.8f, -2), 1);
    s->material.glossReflect = glm::vec3(1);
    s->material.shine = 200.0f;
    s->material.albedo = glm::vec3(0,0.4f,1);
    s->material.reflectance = 0.2f;
    s->material.transparency = 0.8f;
    s->material.indexRefr = 1.004f;
    scn->add(s);

    s = new Sphere(glm::vec3(-2, -1.5, -1.5f), 1.5);
    s->material.albedo = glm::vec3(0.9f, 0, 0.9f);
    scn->add(s);
    
    //s = new Sphere(glm::vec3(5,-2,-4), .5f);
    //s->material.glossReflect = glm::vec3(1);
    //s->material.shine = 250.0f;
    //s->material.albedo = glm::vec3(1,1,1);
    //s->material.reflectance = 1.0f;
    //scn->add(s);
    
    s = new Sphere(glm::vec3(-1,-1,-4), 2);
    s->material.shine = 250.0f;
    s->material.albedo = glm::vec3(1,1,1);
    s->material.reflectance = 1.0f;
    scn->add(s);

    Triangle * t = new Triangle(glm::vec3(-5,-3,-10), glm::vec3(-5,-3,0), glm::vec3(15,-3,0));
    t->material.albedo = glm::vec3(0,0.9f,0.9f);
    scn->add(t);

    t = new Triangle( glm::vec3(-5,-3,-10), glm::vec3(15,-3,0), glm::vec3(15,-3,-10) );
    t->material.albedo = glm::vec3(0,0.9f,0.9f);
    scn->add(t);
    
    t = new Triangle( glm::vec3(-5,10,-10),  glm::vec3(-5,10,0), glm::vec3(-5,-3,0) );
    t->material.albedo = glm::vec3(0.8f, 0.8f, 0.8f);
    scn->add(t);
    
    t = new Triangle( glm::vec3(-5,-3,-10), glm::vec3(-5,10,-10), glm::vec3(-5,-3,0) );
    t->material.albedo = glm::vec3(0.8f, 0.8f, 0.8f);
    scn->add(t);
    
    t = new Triangle( glm::vec3(15,10,-10),  glm::vec3(15,10,0), glm::vec3(15,-3,0) );
    t->material.albedo = glm::vec3(0.8f, 0.8f, 0.8f);
    scn->add(t);
    
    glm::vec3 p1 = glm::vec3(5, 1, -4);
    glm::vec3 p2 = glm::vec3(4,-3,-5);
    glm::vec3 p3 = glm::vec3(4,-3,-3);
    glm::vec3 p4 = glm::vec3(6,-3,-3);
    glm::vec3 p5 = glm::vec3(6,-3,-5);
    
    t = new Triangle(p1, p2, p3 );
    t->material.albedo = glm::vec3(0.8f, 0.5f, 0.2f);
    t->material.transparency = 0.6f;
    t->material.indexRefr = 1.04f;
    scn->add(t);
    
    t = new Triangle(p1, p5, p2 );
    t->material.albedo = glm::vec3(0.8f, 0.5f, 0.2f);
    t->material.transparency = 0.6f;
    t->material.indexRefr = 1.04f;
    scn->add(t);
    
    t = new Triangle(p1, p4, p5 );
    t->material.albedo = glm::vec3(0.8f, 0.5f, 0.2f);
    t->material.transparency = 0.6f;
    t->material.indexRefr = 1.04f;
    scn->add(t);
    
    t = new Triangle(p1, p3, p4 );
    t->material.albedo = glm::vec3(0.8f, 0.5f, 0.2f);
    t->material.transparency = 0.6f;
    t->material.indexRefr = 1.04f;
    scn->add(t);
    
    t = new Triangle( glm::vec3(15,-3,-10), glm::vec3(15,10,-10), glm::vec3(15,-3,0) );
    t->material.albedo = glm::vec3(0.8f, 0.8f, 0.8f);
    scn->add(t);
    
    t = new Triangle( glm::vec3(-5,-3,-10), glm::vec3(15,-3,-10), glm::vec3(15,10,-10) );
    t->material.albedo = glm::vec3(0.8f, 0.8f, 0.8f);
    scn->add(t);
    
    t = new Triangle( glm::vec3(15,10,-10), glm::vec3(-5,10,-10), glm::vec3(-5,-3,-10) );
    t->material.albedo = glm::vec3(0.8f, 0.8f, 0.8f);
    scn->add(t);
    
    PointLight * light = new PointLight;
    light->position = glm::vec3(20,15,20);
    light->intensity = glm::vec3(500);
    scn->add(light);
    
    light = new PointLight;
    light->position = glm::vec3(-20,15,20);
    light->intensity = glm::vec3(500);
    scn->add(light);
  
    Camera * cam = new Camera(800, 600,glm::radians(60.0f));
    cam->orient(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    Renderer render(scn, cam, "out.png");
    render.render();
    
    delete s;
    delete t;
    delete scn;
    delete cam;
    delete light;
};