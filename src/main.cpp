#include "ncurses_display.h"
#include "system.h"
///test
#include <iostream>
#include "linux_parser.h"
#include "format.h"

using std::cout;
//end test

int main() {
  //cout<<LinuxParser::UpTime()<<std::endl;
  
  //cout<<p.Utilization()<<std::endl;
  
  System system;
  NCursesDisplay::Display(system);
  
}