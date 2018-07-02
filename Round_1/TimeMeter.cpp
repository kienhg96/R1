#include "TimeMeter.h"

TimeMeter::TimeMeter() {}


TimeMeter::~TimeMeter() {}

void TimeMeter::start() {
	_start = std::chrono::steady_clock::now();
}

void TimeMeter::end() {
	_end = std::chrono::steady_clock::now();
}

double TimeMeter::getTime() {
	return std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count();
}
