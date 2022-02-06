#pragma once

#include "Vec2.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <unordered_map>

using std::unordered_map;

enum POType {
	default_, default_static
};

class PhysicsObject
{
public:
	constexpr static float PI = 3.141592654f;
	constexpr static float AIR_RES = 1.f;
	static unordered_map<int,PhysicsObject*> list;
	static int next_pos;
	static void PhysicsUpdateAll (const float&);
	static void CollisionUpdateAll(const float&);
	const Vec2 gravity = Vec2(0.f,9.8f);
	int list_index;
	
	//physics properties
	Vec2 pos, vel, acc, force;
	float mass;

	//angular physics properties
	float angle, ang_vel, ang_acc, torque, moment;

	//collision properties
	float collision_energy_ratio, max_radius;

	bool is_static;
	bool simulate_collisions;
	bool gravity_on = true;

	float width, height;
	int pixel_width, pixel_height;

	SDL_Rect src, dest;
	SDL_Texture* texture;

	PhysicsObject(POType, Vec2);
	~PhysicsObject();

	void PhysicsUpdate(const float&);

	static void RenderAll();
	void Render();

private:

};

