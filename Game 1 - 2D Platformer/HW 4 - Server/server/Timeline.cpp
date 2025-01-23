#include "Timeline.hpp"

Timeline::Timeline(Timeline* anchor, int64_t tic)
	: anchor(anchor), tic(tic), paused(false), elapsed_paused_time(0), last_paused_time(0), last_time(0) {
	start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

Timeline::Timeline() : Timeline(nullptr, 1) {}

int64_t Timeline::getTime()
{
	std::lock_guard<std::mutex> lock(m);
	if (paused) {
		return (last_paused_time - start_time - elapsed_paused_time);
	}
	else {
		return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - start_time - elapsed_paused_time);
	}
}

int64_t Timeline::getFrameD()
{
	if (last_time == 0)
	{
		last_time = start_time;
	}

	int64_t current_time = getTime();
	int64_t frame_delta = (current_time - last_time) / getTic();
	last_time = current_time;

	if (frame_delta < 0 || isPaused()) {
		frame_delta = 0;
	}

	return frame_delta;
}

void Timeline::pause()
{
	std::lock_guard<std::mutex> lock(m);

	if (!paused) {
		paused = true;
		last_paused_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		elapsed_paused_time = 0;
	}
}

void Timeline::unpause()
{
	std::lock_guard<std::mutex> lock(m);

	if (paused) {
		paused = false;
		elapsed_paused_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - last_paused_time;
	}
}

void Timeline::changeTic(int newTic)
{
	std::lock_guard<std::mutex> lock(m);

	tic = newTic;
}

bool Timeline::isPaused()
{
	std::lock_guard<std::mutex> lock(m);
	return paused;
}

int64_t Timeline::getTic() {
	std::lock_guard<std::mutex> lock(m);
	return tic;
}