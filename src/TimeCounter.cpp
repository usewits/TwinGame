#include "System.h"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void System::initializeTimer(){
	__int64 freq;
	QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
	Frequency = float(freq);
	QueryPerformanceCounter( (LARGE_INTEGER*)&CurrentTime );
}

float System::GetElapsedTime(){
	__int64 NewTime;
	QueryPerformanceCounter( (LARGE_INTEGER*)&NewTime );
	float TimeDiff = float(NewTime - CurrentTime)/Frequency;
	CurrentTime = NewTime;
	return TimeDiff;
}

#else

void mach_absolute_difference(uint64_t end, uint64_t start, struct timespec *tp) {  
    uint64_t difference = end - start;  
    static mach_timebase_info_data_t info = {0,0};  
    	
    if (info.denom == 0)  
        mach_timebase_info(&info);  
    
    uint64_t elapsednano = difference * (info.numer / info.denom);  
    
    tp->tv_sec = elapsednano * 1e-9;  
    tp->tv_nsec = elapsednano - (tp->tv_sec * 1e9);  
}  

void System::Initialize(){
}

float System::GetElapsedTime(){
    struct timespec tp;  
    end = mach_absolute_time();  
    mach_absolute_difference(end, start, &tp);  
    start = mach_absolute_time();  
    return tp.tv_nsec * 1e-9;   
}

#endif