#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include <chrono>
#include <cstdint>

class Timeline {
private:
	std::mutex m;
	int64_t start_time;
	int64_t elapsed_paused_time;
	int64_t last_paused_time;
	int64_t last_time;
	int64_t tic;
	bool paused;
	Timeline* anchor;
public:
	Timeline(Timeline* anchor, int64_t tic);
	Timeline();
	int64_t getTime();
	int64_t getFrameD();
	void pause();
	void unpause();
	void changeTic(int tic);
	bool isPaused();
	int64_t getTic();
};