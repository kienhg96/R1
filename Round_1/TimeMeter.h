#ifndef __TIME_METER__
#define __TIME_METER__

#include <chrono>
class TimeMeter {
public:
	TimeMeter();
	~TimeMeter();

	void start();
	void end();
	double getTime();
private:
	std::chrono::time_point<std::chrono::steady_clock> _start;
	std::chrono::time_point<std::chrono::steady_clock> _end;
};


#endif // ifndef __TIME_METER__
