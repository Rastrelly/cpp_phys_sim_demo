#include "stdafx.h"
#include <string>
#include "simulated_enity.h"


simulated_enity::simulated_enity()
{
	myPos = { 0.0f, 100.0f };
	lastUpdate = std::chrono::steady_clock::now();
	velocity = {0.0f, 0.0f};
	accel = { 0.0f, -9.82f };
	h = 1000.0f;
	b = 0.1;
		
	needRefresh = true;

	iters = 0;
}

float simulated_enity::getDeltaTime()
{
	auto now = std::chrono::steady_clock::now();
	float dt = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
	if (dt != 0.0f)
	{
		lastUpdate = now;
		deltaTime = dt;
		return dt;
	}
	else
		return 0;
}

void simulated_enity::runSimActions()
{
	getDeltaTime();
	move();
}

void simulated_enity::move()
{
	//Y axis actions
	
	//include gravity into velocity
	velocity.y += accel.y * deltaTime;

	//change position based on current velocity
	myPos.y += velocity.y * deltaTime;

	if (myPos.y < 0.0f)
	{
		myPos.y = 0.0f;
		velocity.y = velocity.y * ((-1.0f)*b);
	}

	//refresh after all done
	setNeedRefresh(true);

	iters++;

	//logData("Current pos: "+std::to_string(myPos.y));
}

void simulated_enity::setupSim(float mass, float height, float grav, float bounce)
{
	h = height;
	m = mass;
	b = bounce;
	myPos.x = 0.0f;
	myPos.y = height;
	accel.y = grav;
	velocity = {0.0f, 0.0f};

	if (!needRefresh) setNeedRefresh(true);

	log = "";

	iters = 0;

	logData("++ Simulation started ++");
}