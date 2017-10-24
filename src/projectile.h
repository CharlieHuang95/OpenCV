#pragma once
#include <iostream>
#include <stdio.h>
#include <list>
#include <cmath>
#include "main.h"

using namespace cv;
using namespace std;

class Projectile {
public:
	Point_F location;
	float slope;
	float speed;
	float size;
	bool backward;
	void Set_Initial(Point_F, Point_F, float, float);
	void update_location(void);
	bool check_collision(float, float);
};

class ProjectileController {
public:
	vector<Projectile> projectiles;
	void add_projectile(Point_F, Point_F, float, float);
	void update_projectiles(void);
	void render_projectiles(Mat);
	bool check_collisions(float, float);
};

void ProjectileController::add_projectile(Point_F start_point, Point_F target_point, float myspeed, float mysize) {
	Projectile new_projectile = Projectile();
	new_projectile.Set_Initial(start_point, target_point, myspeed, mysize);
	projectiles.push_back(new_projectile);
}
void ProjectileController::update_projectiles() {
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i].update_location();
	}
}
void ProjectileController::render_projectiles(Mat frame) {
	for (size_t i = 0; i < projectiles.size(); i++) {
		circle(frame, Point(projectiles[i].location.x, projectiles[i].location.y) , projectiles[i].size, Scalar(255, 255, 255), 2);
	}
}
bool ProjectileController::check_collisions(float x, float y) {
	for (size_t i = 0; i < projectiles.size(); i++) {
		if (abs(y - projectiles[i].location.y) + abs(x - projectiles[i].location.x) < projectiles[i].size) {
			return true;
		}
	}
	return false;
}
