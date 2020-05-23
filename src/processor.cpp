#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    long totalTime{0}, idleTime{0};
    LinuxParser::GetCPUTotalandIdleTime(totalTime, idleTime);
    float deltaTotal = totalTime - prevTotalTime;
    float deltaIdle = idleTime - prevIdleTime;
    prevTotalTime = totalTime;
    prevIdleTime = idleTime;
    return (1. - deltaIdle/deltaTotal);
}