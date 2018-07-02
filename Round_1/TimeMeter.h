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
	std::chrono::steady_clock::time_point _start;
	std::chrono::steady_clock::time_point _end;
};


#endif // ifndef __TIME_METER__
