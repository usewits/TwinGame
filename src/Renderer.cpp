#include "Renderer.h"
#include "Light.h"
#include "RenderableObject.h"
#include <iostream>

#include "SDL/SDL.h"
#include "gl/glew.h"

Renderer::Renderer() : sdl_surface(0) {
}


Renderer::~Renderer(){
}

int Renderer::initialize(){
	windowWidth = 1024; windowHeight = 768; //TODO: Get this from settings file

	sdl_surface = SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
	if(sdl_surface == NULL) {
		return 0;
	}

	//Initialize GLEW (support for OpenGL 2.0 and higher)
	if(glewInit() != GLEW_OK || !GLEW_VERSION_2_0 ){
		std::cout << "ERROR: OpenGL 2.0 is not supported.\n";
		return 0;
	}

	//Initalize OpenGL settings
	glShadeModel(GL_SMOOTH);	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	glClearDepth(1.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	//glAlphaFunc(GL_ONE, GL_SRC_ALPHA);
	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	GenerateProjectionMatrix();

	//TODO: Initialize shaders

	return 1;
}

void Renderer::cleanup(){
	if( sdl_surface ) SDL_FreeSurface(sdl_surface);
	sdl_surface = 0;
}

void Renderer::GenerateProjectionMatrix(){
	//SET THE PROJECTION MATRIX
	//aspect, near and far, position vars
	float xmin, xmax, ymin, ymax, near, far, fov, aspect;

	//calculate aspect, set values for near far and pov
	aspect = (float)windowWidth / windowHeight;
	near = 1.0; far = 30.0; fov = 60.0;

	//calculate values for near plane
	xmin = -(near * (float)tan(fov * M_PI / 360.0));
	xmax = -xmin;
	ymin = xmin / aspect;
	ymax = xmax / aspect;

	//set the correct perspective matrix
	projectionMatrix.setPerspective(xmin, xmax, ymin, ymax, near, far);
}

void Renderer::AddObject(RenderableObject* obj){
	//TODO:
	//Decide what shader this object needs, to know in what list the object should be.
	defaultObjects.push_back(obj);
}

void Renderer::RemoveObject(RenderableObject* obj){
	if( RemoveFromList(obj, defaultObjects) ) return;
	//if( RemoveFromList(obj, shadowcastObjects) ) return;
}

bool Renderer::RemoveFromList(RenderableObject* obj, RenderList& renderlist){
	for( RenderIterator it = renderlist.begin(); it != renderlist.end(); ++it ){
		if( (*it) == obj ){
			renderlist.erase(it);
			return true;
		}
	}
	return false;
}

void Renderer::AddLight(Light* light){
	lights.push_back(light);
}

void Renderer::RemoveLight(Light* obj){
	for( LightIterator it = lights.begin(); it != lights.end(); ++it ){
		if( (*it) == obj ){
			lights.erase(it);
			break;
		}
	}
}


void Renderer::drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();
	return;
}