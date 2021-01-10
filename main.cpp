#include <iostream>
#include <fstream>
#include <QObject>

#include "private/qproperty_p.h"
#include <sys/resource.h>

#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

#include <malloc.h>

#include "omp.h"

using namespace std;
double getMemUsage() {
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

const int num_samples = 10000000;

void print_sizeofs(){
    std::ofstream sizeofs("sizeofs.txt");
    sizeofs << "name value" << std::endl;
    sizeofs << "sizeof(int) " << sizeof(int) << std::endl;
    sizeofs << "sizeof(QObject) " << sizeof(QObject) << std::endl;

    // QProperty and its base types
    sizeofs << "sizeof(QUntypedPropertyData) " << sizeof(QUntypedPropertyData) << std::endl;
    sizeofs << "sizeof(QPropertyData<int>) " << sizeof(QPropertyData<int>) << std::endl;
    sizeofs << "sizeof(QProperty<int>) " << sizeof(QProperty<int>) << std::endl;

    // QObjectBindableProperty and friends
    sizeofs << "sizeof(QObjectBindableProperty<void,int,0>) " << sizeof(QObjectBindableProperty<void,int,0>) << std::endl;
    sizeofs << "sizeof(QObjectCompatProperty<void,int,0,0>) " << sizeof(QObjectCompatProperty<void,int,0,0>) << std::endl;
    sizeofs << "sizeof(QObjectComputedProperty<void,int,0,0>) " << sizeof(QObjectComputedProperty<void,int,0,0>) << std::endl;

    // internals
    sizeofs << "sizeof(QPropertyBindingData) " << sizeof(QtPrivate::QPropertyBindingData) << std::endl;
    sizeofs << "sizeof(QPropertyObserverBase) " << sizeof(QPropertyObserverBase) << std::endl;
    sizeofs << "sizeof(QPropertyObserver) " << sizeof(QPropertyObserver) << std::endl;

    sizeofs << "sizeof(BindingFunctionVTable) " << sizeof(QtPrivate::BindingFunctionVTable) << std::endl;
    sizeofs << "sizeof(QPropertyBindingPrivate) " << sizeof(QPropertyBindingPrivate) << std::endl;
}

double memory_usage_for_binding_0(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 0; ++i){
        properties2[i].setBinding(
                [&](){
                    return 0;
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_1(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 0; ++i){
        QProperty<int>
                &a=properties[i]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_2(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 1; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_3(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 2; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_4(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 3; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double memory_usage_for_binding_5(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 4; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_6(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 5; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                    + f.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_7(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 6; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5],
                &g=properties[i+6]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_8(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 7; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5],
                &g=properties[i+6],
                &h=properties[i+7]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value() + h.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double memory_usage_for_binding_9(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 8; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5],
                &g=properties[i+6],
                &h=properties[i+7],
                &j=properties[i+8]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value() + h.value() + j.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double memory_usage_for_binding_10(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 9; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5],
                &g=properties[i+6],
                &h=properties[i+7],
                &j=properties[i+8],
                &k=properties[i+9]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value() + h.value() + j.value() + k.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double memory_usage_for_binding_11(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 10; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5],
                &g=properties[i+6],
                &h=properties[i+7],
                &j=properties[i+8],
                &k=properties[i+9],
                &l=properties[i+10]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value() + h.value() + j.value() + k.value()
                           + l.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double memory_usage_for_binding_12(){
    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 11; ++i){
        QProperty<int>
                &a=properties[i],
                &b=properties[i+1],
                &c=properties[i+2],
                &d=properties[i+3],
                &e=properties[i+4],
                &f=properties[i+5],
                &g=properties[i+6],
                &h=properties[i+7],
                &j=properties[i+8],
                &k=properties[i+9],
                &l=properties[i+10],
                &m=properties[i+11]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value() + h.value() + j.value() + k.value()
                                        + l.value() + m.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[12]).observerCount() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

void print_binding_memusage() {
    std::ofstream outfile("binding_memusage.txt");
    outfile << "connections memory" << std::endl;
    outfile << "0 " << memory_usage_for_binding_0() << std::endl;
    outfile << "1 " << memory_usage_for_binding_1() << std::endl;
    outfile << "2 " << memory_usage_for_binding_2() << std::endl;
    outfile << "3 " << memory_usage_for_binding_3() << std::endl;
    outfile << "4 " << memory_usage_for_binding_4() << std::endl;
    outfile << "5 " << memory_usage_for_binding_5() << std::endl;
    outfile << "6 " << memory_usage_for_binding_6() << std::endl;
    outfile << "7 " << memory_usage_for_binding_7() << std::endl;
    outfile << "8 " << memory_usage_for_binding_8() << std::endl;
    outfile << "9 " << memory_usage_for_binding_9() << std::endl;
    outfile << "10 " << memory_usage_for_binding_10() << std::endl;
    outfile << "11 " << memory_usage_for_binding_11() << std::endl;
    outfile << "12 " << memory_usage_for_binding_12() << std::endl;
}
int main(){
    print_sizeofs();
    print_binding_memusage();
/*
    //num_samples = 20;
    double baseline = getMemUsage();

    for(auto& p : properties)
        p = 5;

    double after = getMemUsage();

    std::cout << "mem usage per QProperty<int> " << (after - baseline) / num_samples << std::endl;

    {
        std::vector<QProperty<int>> properties2(num_samples);
        baseline = getMemUsage();
        for(int i = 0; i < num_samples; ++i){
            properties2[i].setBinding(Qt::makePropertyBinding(properties[i]));
        }
        after = getMemUsage();
        std::cout << "mem usage per Qt::makePropertyBinding " << (after - baseline) / num_samples << std::endl;
    }
    {
        std::vector<QProperty<int>> properties2(num_samples);
        baseline = getMemUsage();
        double starttime = omp_get_wtime();
        for(int i = 0; i < num_samples - 10; ++i){
            QProperty<int>
                    &a=properties[i],
                    &b=properties[i+1],
                    &c=properties[i+2],
                    &d=properties[i+3],
                    &e=properties[i+4],
                    &f=properties[i+5],
                    &g=properties[i+6],
                    &h=properties[i+7],
                    &j=properties[i+8],
                    &k=properties[i+9];
            properties2[i].setBinding(
                    [&](){
                        return a.value() + b.value() + c.value() + d.value() + e.value() +
                        f.value() + g.value() + h.value() + j.value() + k.value();;
                    });
        }
        double endtime = omp_get_wtime();
        std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[0]).observerCount() << std::endl;
        after = getMemUsage();
        std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
        std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

        {
            baseline = getMemUsage();
            starttime = omp_get_wtime();
            // calculate sum to use:
            int sum(0);
            for(int i = 0; i < num_samples - 4; ++i){
                sum += properties2[i].value();
            }
            after = getMemUsage();
            endtime = omp_get_wtime();

            std::cout << "mem usage per binding evaluation " << (after - baseline) / double(num_samples) << std::endl;
            std::cout << "time usage per binding evaluation " << (endtime - starttime) / double(num_samples) << std::endl;
            std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[0]).observerCount() << std::endl;
        }
        for(int i = 0; i < num_samples; ++i){
            properties[i] = 7;
        }
        {
            baseline = getMemUsage();
            starttime = omp_get_wtime();
            // calculate sum to use:
            int sum(0);
            for(int i = 0; i < num_samples - 4; ++i){
                sum += properties2[i].value();
            }
            after = getMemUsage();
            endtime = omp_get_wtime();

            std::cout << "mem usage per binding evaluation " << (after - baseline) / double(num_samples) << std::endl;
            std::cout << "time usage per binding evaluation " << (endtime - starttime) / double(num_samples) << std::endl;
            std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[0]).observerCount() << std::endl;
        }

        for(int i = 0; i < 5; ++i){
            std::cout << properties2[i].value() << std::endl;
        }
    }*/
}