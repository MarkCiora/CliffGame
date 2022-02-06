#include "PhysicsObject.h"

#include "helper.h"
#include "Tex.h"
#include "Matrix2D.h"
#include "VisualObject.h"
#include "VisualLine.h"

#include <cmath>
#include <iomanip>

using std::endl;
using std::cout;

//int PhysicsObject::world_ratio = 50;

unordered_map<int, PhysicsObject*> PhysicsObject::list;
int PhysicsObject::next_pos = 0;
void PhysicsObject::PhysicsUpdateAll(const float& dt) {
	for (auto& it : list) it.second->PhysicsUpdate(dt);
}

void PhysicsObject::PhysicsUpdate(const float& dt) {
	if(false){
		force = Vec2();
	}else{
		//accumulate forces
		if(gravity_on) force = force + gravity * mass;
		force = force - vel * AIR_RES;
		//torque = torque + 30.f;

		//save old values
		auto pacc = acc;
		auto pvel = vel;
		auto pang_acc = ang_acc;
		auto pang_vel = ang_vel;

		//update new values
		acc = force / mass;
		vel = vel + ((acc + pacc) * dt * 0.5f);
		pos = pos + ((vel + pvel) * dt * 0.5f);
		ang_acc = torque / moment;
		ang_vel = ang_vel + ((ang_acc + pang_acc) * dt * 0.5f);
		angle = angle + ((ang_vel + pang_vel) * dt * 0.5f);
		//std::cout << helper::world_ratio << std::endl;
		//reset force
		force = Vec2();
		//std::cout << force << std::endl;
		//torque = 0;
	}
	std::cout << acc << " " << vel << " " << pos << " " << dt << std::endl;
}

void PhysicsObject::CollisionUpdateAll(const float& dt){
	if(list.size() <= 1) return;
	Matrix2D rot90 = Matrix2D::TransformFromAngle(PI * 0.5f);
	for (auto it1 = list.begin(); it1 != list.end(); it1++){
		auto it2 = it1;
		it2++;
		for (; it2 != list.end(); it2++){
			PhysicsObject &PO1 = *(it1->second);
			PhysicsObject &PO2 = *(it2->second);
			// check for collisions between PO1 and PO2
			//Cut tests
			//1. check if they are even close enough:
			auto difference_vec = PO1.pos - PO2.pos;
			//if (difference_vec.mag() > PO1.max_radius + PO2.max_radius) return;

			//Now detect actual collisions
			auto rot_mat1 = Matrix2D::TransformFromAngle(PO1.angle * PI / 180);
			auto rot_mat2 = Matrix2D::TransformFromAngle(PO2.angle * PI / 180);
			auto rot_mat1_inv = Matrix2D::TransformFromAngle(-PO1.angle * PI / 180);
			auto rot_mat2_inv = Matrix2D::TransformFromAngle(-PO2.angle * PI / 180);

			Vec2 corner1[4];
			corner1[0] = rot_mat1 * ((Vec2(PO1.width, PO1.height) * 0.5f));
			corner1[1] = rot_mat1 * ((Vec2(PO1.width, -PO1.height) * 0.5f));
			corner1[2] = corner1[0] * -1.f;
			corner1[3] = corner1[1] * -1.f;
			for (int i = 0; i < 4; i++) corner1[i] = corner1[i] + PO1.pos;
			Vec2 corner2[4];
			corner2[0] = rot_mat2 * ((Vec2(PO2.width, PO2.height) * 0.5f));
			corner2[1] = rot_mat2 * ((Vec2(PO2.width, -PO2.height) * 0.5f));
			corner2[2] = corner2[0] * -1.f;
			corner2[3] = corner2[1] * -1.f;
			for (int i = 0; i < 4; i++) corner2[i] = corner2[i] + PO2.pos;


			//Each edge is cross compared and checked for overlap, then the
			//points of overlap are used to determine the forces that should
			//be applied. Start at positive x and y for each, work around by
			//increasing by +90 degrees each time. Two points are used in each
			//loop increment, the current and the next, to form the edge.
			Vec2 corner1_current = corner1[0], corner1_next = corner1[1];
			Vec2 corner2_current = corner2[0], corner2_next = corner2[1];

			//also check if each point is inside the other object first
			bool inside1[4], inside2[4];
			for(int i = 0; i < 4; i++){
				corner1_current = corner1[i];
				corner2_current = corner2[i];
				auto t1 = rot_mat2_inv * (corner1_current - PO2.pos);
				auto t2 = rot_mat1_inv * (corner2_current - PO1.pos);
				inside1[i] = (t1.x < PO2.width * 0.5f) && (t1.x > -PO2.width * 0.5f) &&
					(t1.y < PO2.height * 0.5f) && (t1.y > -PO2.height * 0.5f);
				inside2[i] = (t2.x < PO1.width * 0.5f) && (t2.x > -PO1.width * 0.5f) &&
					(t2.y < PO1.height * 0.5f) && (t2.y > -PO1.height * 0.5f);
			}
			//std::cout << PO1.pos << PO2.pos << std::endl;

			corner1_current = corner1[0], corner1_next = corner1[1];
			corner2_current = corner2[0], corner2_next = corner2[1];

			cout << std::setprecision(2);
			
			std::vector<Vec2> points;
			int cur_point = 0;
			for (int i = 0; i < 4; i++){//PO1
				corner1_next = corner1[(i+1)%4];
				for (int j = 0; j < 4; j++){//PO2
					corner2_next = corner2[(j+1)%4];

					//logic... (y-y1)*dx=(x-x1)*dy 
					auto d1 = corner1_next - corner1_current + Vec2(1e-20f,1e-20f);
					auto d2 = corner2_next - corner2_current + Vec2(1e-20f,1e-20f);
					auto m1 = (d1.y) / (d1.x + 1e-20f);
					auto b1 = corner1_current.y - corner1_current.x * m1;
					auto m2 = (d2.y) / (d2.x + 1e-20f);
					auto b2 = corner2_current.y - corner2_current.x * m2;

					float x=0.f,y=0.f;
					if((d1.y * d2.x == d2.y * d1.x)){
						continue; //failed if slope is the same
					}
					if(d1.y == 0 || d2.y == 0){
						if(d1.y == d2.y) continue;//same slope of 0
						if(d1.y == 0){//infinite slope on line 1
							x = corner1_current.x;
							if (d2.x != 0) y = m2 * x + b2;
							else y = PO2.pos.y;
						}else if(d2.y == 0){//infinite slope on line 2
							x = corner2_current.x;
							if (d1.x != 0) y = m1 * x + b1;
							else y = PO1.pos.y;
						}
					}
					else if(d1.x == 0 || d2.x == 0){
						if(d1.x == d2.x) continue;//same slope of 0
						if(d1.x == 0){//infinite slope on line 1
							y = corner1_current.y;
							if (d2.y != 0) x = (y - b2) / m2;
							else x = PO2.pos.x;
						}else if(d2.y == 0){//infinite slope on line 2
							y = corner2_current.y;
							if (d1.y != 0) x = (y - b1) / m1;
							else x = PO1.pos.x;
						}
					}
					else{
						x = (b2 - b1) / (m1 - m2);//solve for x
						y = m1 * x + b1;//wow!
					}

					//check if x is between corner1_next an corner1_current
					//check if x is between corner2_next an corner2_current
					//both must be true, then assign this as an intersect point
					bool match1, match2;
					if(corner1_current.x > corner1_next.x){
						match1 = (x < corner1_current.x) && (x > corner1_next.x);
					}else{
						match1 = (x > corner1_current.x) && (x < corner1_next.x);
					}
					if(corner1_current.y > corner1_next.y){
						match1 = match1 || ((y < corner1_current.y) && (y > corner1_next.y));
					}else{
						match1 = match1 || ((y > corner1_current.y) && (y < corner1_next.y));
					}

					if(corner2_current.x > corner2_next.x){
						match2 = (x < corner2_current.x) && (x > corner2_next.x);
					}else{
						match2 = (x > corner2_current.x) && (x < corner2_next.x);
					}
					if(corner2_current.y > corner2_next.y){
						match2 = match2 || ((y < corner2_current.y) && (y > corner2_next.y));
					}else{
						match2 = match2 || ((y > corner2_current.y) && (y < corner2_next.y));
					}

					if(match1 && match2){
						points.push_back(Vec2(x,y));
						cur_point++;
					}
					//cout << j << Vec2(x,y);
					corner2_current = corner2_next;
				}
				//cout << endl;
				corner1_current = corner1_next;
			}
			//cout << PO1.pos << PO2.pos << endl << endl;
			cout << cur_point << endl;
			for (auto &it : points) VisualObject::AddDotRed(it);
			if((cur_point > 0) && (cur_point % 2 == 0)){
				std::cout << "intersection" << std::endl;
				for (auto it = 0; it < points.size(); it+=2){
					auto p1 = points[it], p2 = points[it + 1];
					VisualLine::AddLine(points[it], points[it+1]);

					//new technique
					//if they are moving towards each other, trigger elastic collision
					auto vel_diff = PO2.vel - PO1.vel, pos_diff = PO2.pos - PO1.pos;
					if (Vec2::dot(vel_diff, pos_diff) > 0){
						auto mass_sum = PO1.mass + PO2.mass, mass_diff = PO2.mass - PO1.mass;
						auto temp = PO1.vel;
						PO1.vel = temp * (-mass_diff / mass_sum) + 
								PO2.vel * (2 * PO2.mass / mass_sum);
						PO2.vel = temp * (2 * PO1.mass / mass_sum) +
								PO2.vel * (mass_diff / mass_sum);
					}
					else continue;//otherwise do nothing
					
				}
			}
			else if(inside1[0] || inside1[1] || inside1[2] || inside1[3] ||
				inside2[0] || inside2[1] || inside2[2] || inside2[3]){
				std::cout << "just inside" << cur_point << std::endl;
			}
			//std::cout << inside2[0] << inside2[1] << inside2[2] << inside2[3] << std::endl;
		}
	}
}

PhysicsObject::PhysicsObject(POType type = default_, Vec2 p = Vec2()) {
	//put it in the list
	list_index = next_pos;
	list[list_index] = this;
	next_pos++;
	
	//initialize physics properties
	pos = p;
	vel = acc = force = Vec2();
	mass = 1.f;

	//initiliaze angular physics properties
	angle = ang_vel = ang_acc = torque = 0.f;
	moment = 1.f;

	simulate_collisions = true;
	if(type == POType::default_static){
		texture = Tex::rock1.t;
		//is it static?
		is_static = type == default_static;
		gravity_on = false;

		//width and height
		width = 10.f;
		height = 3.f;
	}else{
		texture = Tex::green16x16.t;
		//is it static?
		is_static = type == default_static;

		//width and height
		width = 1.f;
		height = 1.f;
	}
	
	//initialize collision properties
	collision_energy_ratio = 0.5f;
	max_radius = (std::sqrt(width * width + height * height)) * 0.5f;

	//texture stuff
	src.x = 0; src.y = 0;
	src.w = 16; src.h = 16;
}

PhysicsObject::~PhysicsObject() {
	list.erase(list_index);
}

void PhysicsObject::RenderAll() {
	int asdf = 0;
	for (auto& it : list) it.second->Render();
}
void PhysicsObject::Render() {
	dest.w = width * helper::world_ratio;
	dest.h = height * helper::world_ratio;
	dest.x = pos.x * helper::world_ratio - (dest.w >> 1);
	dest.y = pos.y * helper::world_ratio - (dest.h >> 1);
	//SDL_RenderCopy(helper::MAIN_RENDERER, texture, &src, &dest);
	SDL_RenderCopyEx(helper::MAIN_RENDERER, texture, &src, &dest, angle,
		nullptr, SDL_FLIP_NONE);
}