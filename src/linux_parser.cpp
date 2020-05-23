#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>  //for a test

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


std::string LinuxParser::getLineStartsWith(std::string filename, std::string key) {  
  std::string line;
  std::ifstream stream(filename);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      if (line.rfind(key) == 0) {          
          break;
      }
    } 
  }
  return line; 
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  /*string line;
  string key;
  string value;  
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }*/
  string line(getLineStartsWith(kOSPath, "PRETTY_NAME"));
  if (!line.empty()) {
    std::replace(line.begin(), line.end(), ' ', '_');
    std::replace(line.begin(), line.end(), '=', ' ');
    std::replace(line.begin(), line.end(), '"', ' ');
    std::istringstream linestream(line);
    linestream >> line >> line;
    std::replace(line.begin(), line.end(), '_', ' ');
  }
  return line;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memUsage = 0.;
  std::string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {  
    int totelMem = 0;  
    std::istringstream linestream;
    while (std::getline(stream, line)) {
      if (line.rfind("MemTotal:") == 0) {   
        linestream.clear();
        linestream.str(line);        
        linestream>>line>>totelMem;   
        if (memUsage)    
          break;
      }
      if (line.rfind("MemFree:") == 0) {
        linestream.clear();
        linestream.str(line);        
        linestream>>line>>memUsage;   
        if (totelMem)    
          break;
      }
    } 
    
    if (totelMem) memUsage = memUsage*100/totelMem;
  }
  
  return memUsage; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  float time = 0.;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::string line;
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time;
  }  
  return time; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int num = 0;
  /*std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::string line;
    while (std::getline(stream, line)) {
      if (line.rfind("processes") == 0) {          
          std::istringstream linestream(line);
          linestream>>line>>num;
          break;
      }
    } 
  }*/
  std::string line = getLineStartsWith(kProcDirectory + kStatFilename, "processes");
  if (!line.empty()) {
    std::istringstream linestream (line);
    linestream>>line>>num;
  }
  
  return num; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int num = 0;
  std::string line = getLineStartsWith(kProcDirectory + kStatFilename, "procs_running");
  if (!line.empty()) {
    std::istringstream linestream (line);
    linestream>>line>>num;
  }
  
  return num; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }