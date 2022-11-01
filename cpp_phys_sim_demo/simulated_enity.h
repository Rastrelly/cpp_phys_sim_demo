#pragma once
#include <chrono>

struct coord { float x, y; };

class simulated_enity
{
private:
	coord myPos;
	coord accel;
	coord velocity;
	std::chrono::steady_clock::time_point lastUpdate;
	float deltaTime;
	bool needRefresh;
	bool needClose;

	float m;
	float g;
	float h;
	float b;

	std::string log;

	long int iters;
public:
	simulated_enity();
	float getX() { return myPos.x; };
	float getY() { return myPos.y; };
	coord getPos() { return myPos; };
	float simulated_enity::getDeltaTime();
	void runSimActions();
	void move();
	bool getNeedRefresh() { return needRefresh; };
	void setNeedRefresh(bool val) { needRefresh = val; };
	void setupSim(float mass, float height, float grav, float bounce);
	float getHeight() { return h; };
	void logData(std::string txt) { log += (txt + "\n"); };
	std::string getLog() { return log; };
	long int getIterations() { return iters; };
	bool getNeedClose() { return needClose; };
	void setNeedClose(bool val) { needClose = val; };
};


