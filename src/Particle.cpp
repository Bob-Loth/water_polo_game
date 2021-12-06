//
// sueda - geometry edits Z. Wood
// 3/16
//

#include <iostream>
#include "Particle.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Texture.h"


float randFloat(float l, float h)
{
	float r = rand() / (float) RAND_MAX;
	return (1.0f - r) * l + r * h;
}

Particle::Particle(vec3 start) :
	charge(1.0f),
	m(1.0f),
	d(0.0f),
	x(start.x, start.y, start.z),
	v(0.0f, 0.0f, 0.0f),
	lifespan(2.0f),
	tEnd(0.0f),
	scale(10.0f),
	color(.245f * (((rand() % 8) + 2) / 5),
		.245f * (((rand() % 8) + 2) / 5),
		.666f * (((rand() % 8) + 2) / 5),
		1.0f)
{
}

Particle::~Particle()
{
}

void Particle::load(vec3 start)
{
	// Random initialization
	rebirth(0.0f, start);
}

/* all particles born at the origin */
void Particle::rebirth(float t, vec3 start)
{
	charge = randFloat(0.0f, 1.0f) < 0.5 ? -1.0f : 1.0f;	
	m = 1.0f;
  	d = randFloat(0.0f, 0.02f);
	x = vec3(start.x, start.y, start.z);
	v.x = randFloat(-1.0f, 1.0f);
	v.y = 1.0f;
	v.z = randFloat(-1.0f, 1.0f);
	lifespan = 2.0f; 
	tEnd = t + lifespan;
	scale = randFloat(1.0f, 1.0f);
   	color.r = randFloat(0.26f, 0.29f);
   	color.g = randFloat(0.14f, 0.34f);
   	color.b = randFloat(0.63f, 0.69f);
	color.a = randFloat(0.3f, 1.0f);
}

void Particle::update(float t, float h, const vec3 &g, const vec3 start)
{
	if(t > tEnd) {
		rebirth(t, start);
	}

	//very simple update
	x += h * v;
	v += h * g * 10.0f;
	
}