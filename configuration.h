//
// Created by andreasbuhr on 10.01.21.
//

#ifndef QPROPERTY_PERFORMANCE_REPORT_CONFIGURATION_H
#define QPROPERTY_PERFORMANCE_REPORT_CONFIGURATION_H


#include <malloc.h>
#include <fstream>
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

static double getMemUsage() {
    using namespace std;
    malloc_trim(0);
    double vm_usage;
    double resident_set;
    vm_usage = 0.0;
    resident_set = 0.0;
    ifstream stat_stream("/proc/self/stat",ios_base::in); //get info from proc directory
    //create some variables to get info
    string pid, comm, state, ppid, pgrp, session, tty_nr;
    string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    string utime, stime, cutime, cstime, priority, nice;
    string O, itrealvalue, starttime;
    unsigned long vsize;
    long long rss;
    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                >> utime >> stime >> cutime >> cstime >> priority >> nice
                >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest
    stat_stream.close();
    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
    return resident_set * 1024;
}

//const int num_samples = 5000000; // 6 per cent
//const int num_samples = 500000; // 0.6 per cent
//const int num_samples = 5000; // 0.006 per cent
const int num_samples = 50000000; // 60 per cent

#endif //QPROPERTY_PERFORMANCE_REPORT_CONFIGURATION_H
