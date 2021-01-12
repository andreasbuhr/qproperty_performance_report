//
// Created by andreasbuhr on 10.01.21.
//

#include "qproperty_memory_measurement.h"

#include "configuration.h"


#include <iostream>
#include <fstream>
#include "omp.h"
#include <vector>
#include <QProperty>

#include "private/qproperty_p.h"

auto memory_usage_for_binding_0(){
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_1(){
    std::vector<int> access_pattern;
    int num_upstream = 1;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 0; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_2(){
    std::vector<int> access_pattern;
    int num_upstream = 2;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 1; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_3(){
    std::vector<int> access_pattern;
    int num_upstream = 3;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 2; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_4(){
    std::vector<int> access_pattern;
    int num_upstream = 4;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 3; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}


auto memory_usage_for_binding_5(){
    std::vector<int> access_pattern;
    int num_upstream = 5;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 4; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_6(){
    std::vector<int> access_pattern;
    int num_upstream = 6;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 5; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_7(){
    std::vector<int> access_pattern;
    int num_upstream = 7;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 6; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_8(){
    std::vector<int> access_pattern;
    int num_upstream = 8;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 7; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]],
                &h=properties[access_pattern[num_upstream*i+7]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

auto memory_usage_for_binding_9(){
    std::vector<int> access_pattern;
    int num_upstream = 9;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 8; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]],
                &h=properties[access_pattern[num_upstream*i+7]],
                &j=properties[access_pattern[num_upstream*i+8]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}


auto memory_usage_for_binding_10(){
    std::vector<int> access_pattern;
    int num_upstream = 10;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 9; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]],
                &h=properties[access_pattern[num_upstream*i+7]],
                &j=properties[access_pattern[num_upstream*i+8]],
                &k=properties[access_pattern[num_upstream*i+9]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}


auto memory_usage_for_binding_11(){
    std::vector<int> access_pattern;
    int num_upstream = 11;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 10; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]],
                &h=properties[access_pattern[num_upstream*i+7]],
                &j=properties[access_pattern[num_upstream*i+8]],
                &k=properties[access_pattern[num_upstream*i+9]],
                &l=properties[access_pattern[num_upstream*i+10]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}


auto memory_usage_for_binding_12(){
    std::vector<int> access_pattern;
    int num_upstream = 12;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 11; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]],
                &h=properties[access_pattern[num_upstream*i+7]],
                &j=properties[access_pattern[num_upstream*i+8]],
                &k=properties[access_pattern[num_upstream*i+9]],
                &l=properties[access_pattern[num_upstream*i+10]],
                &m=properties[access_pattern[num_upstream*i+11]]
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
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}



auto memory_usage_for_binding_16(){
    std::vector<int> access_pattern;
    int num_upstream = 16;
    for(int i = 0; i < num_samples; ++i){
        for(int j = 0; j < num_upstream; ++j){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<QProperty<int>> properties(num_samples);
    for(auto& p : properties)
        p = 5;
    std::vector<QProperty<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 15; ++i){
        QProperty<int>
                &a=properties[access_pattern[num_upstream*i+0]],
                &b=properties[access_pattern[num_upstream*i+1]],
                &c=properties[access_pattern[num_upstream*i+2]],
                &d=properties[access_pattern[num_upstream*i+3]],
                &e=properties[access_pattern[num_upstream*i+4]],
                &f=properties[access_pattern[num_upstream*i+5]],
                &g=properties[access_pattern[num_upstream*i+6]],
                &h=properties[access_pattern[num_upstream*i+7]],
                &j=properties[access_pattern[num_upstream*i+8]],
                &k=properties[access_pattern[num_upstream*i+9]],
                &l=properties[access_pattern[num_upstream*i+10]],
                &m=properties[access_pattern[num_upstream*i+11]],
                &n=properties[access_pattern[num_upstream*i+12]],
                &o=properties[access_pattern[num_upstream*i+13]],
                &p=properties[access_pattern[num_upstream*i+14]],
                &q=properties[access_pattern[num_upstream*i+15]]
        ;
        properties2[i].setBinding(
                [&](){
                    return a.value() + b.value() + c.value() + d.value() + e.value()
                           + f.value(), + g.value() + h.value() + j.value() + k.value()
                                        + l.value() + m.value() + n.value() + o.value()
                                        + p.value() + q.value();
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << QPropertyBindingDataPointer::get(properties[15]).observerCount() << std::endl;
    double after = getMemUsage();
    double memoryUsage = (after - baseline) / double(num_samples);
    std::cout << "mem usage per lambda property binding " << memoryUsage << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;

    // non-dirty read
    starttime = omp_get_wtime();
    int sum(0);
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double nonDirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "non dirty read time: " << nonDirtyReadTime << std::endl;

    starttime = omp_get_wtime();
    for(auto& p : properties){
        p.setValue(9);
    }
    endtime = omp_get_wtime();
    double setAndNotifyTime = (endtime - starttime ) / num_samples;
    std::cout << "set and mark dirty time: " << setAndNotifyTime << std::endl;


    starttime = omp_get_wtime();
    sum=0;
    for(auto& p : properties2){
        sum += p.value();
    }
    endtime = omp_get_wtime();
    double dirtyReadTime = (endtime - starttime ) / num_samples;
    std::cout << "dirty read time: " << dirtyReadTime << std::endl;

    return std::make_tuple(memoryUsage, nonDirtyReadTime, setAndNotifyTime, dirtyReadTime);
}

template<int element>
void printfile(std::string filename, std::string dataname){

}
void print_binding_memusage() {
    // measurements:
    auto result0 = memory_usage_for_binding_0();
    auto result1 = memory_usage_for_binding_1 () ;
    auto result2 = memory_usage_for_binding_2 () ;
    auto result3 = memory_usage_for_binding_3 () ;
    auto result4 = memory_usage_for_binding_4 () ;
    auto result5 = memory_usage_for_binding_5 () ;
    auto result6 = memory_usage_for_binding_6 () ;
    auto result7 = memory_usage_for_binding_7 () ;
    auto result8 = memory_usage_for_binding_8 () ;
    auto result9 = memory_usage_for_binding_9 () ;
    auto result10 = memory_usage_for_binding_10();
    auto result11 = memory_usage_for_binding_11();
    auto result12 = memory_usage_for_binding_12();
    auto result16 = memory_usage_for_binding_16();


    {
        std::ofstream outfile("binding_memusage.txt");
        outfile << "connections memory" << std::endl;
        outfile << "0 " << std::get<0>(result0) << std::endl;
        outfile << "1 " << std::get<0>(result1) << std::endl;
        outfile << "2 " << std::get<0>(result2) << std::endl;
        outfile << "3 " << std::get<0>(result3) << std::endl;
        outfile << "4 " << std::get<0>(result4) << std::endl;
        outfile << "5 " << std::get<0>(result5) << std::endl;
        outfile << "6 " << std::get<0>(result6) << std::endl;
        outfile << "7 " << std::get<0>(result7) << std::endl;
        outfile << "8 " << std::get<0>(result8) << std::endl;
        outfile << "9 " << std::get<0>(result9) << std::endl;
        outfile << "10 " << std::get<0>(result10) << std::endl;
        outfile << "11 " << std::get<0>(result11) << std::endl;
        outfile << "12 " << std::get<0>(result12) << std::endl;
        outfile << "16 " << std::get<0>(result16) << std::endl;
    }
    
    {
        std::ofstream outfile("binding_nondirtyread.txt");
        outfile << "connections time" << std::endl;
        outfile << "0 " << std::get<1>(result0) << std::endl;
        outfile << "1 " << std::get<1>(result1) << std::endl;
        outfile << "2 " << std::get<1>(result2) << std::endl;
        outfile << "3 " << std::get<1>(result3) << std::endl;
        outfile << "4 " << std::get<1>(result4) << std::endl;
        outfile << "5 " << std::get<1>(result5) << std::endl;
        outfile << "6 " << std::get<1>(result6) << std::endl;
        outfile << "7 " << std::get<1>(result7) << std::endl;
        outfile << "8 " << std::get<1>(result8) << std::endl;
        outfile << "9 " << std::get<1>(result9) << std::endl;
        outfile << "10 " << std::get<1>(result10) << std::endl;
        outfile << "11 " << std::get<1>(result11) << std::endl;
        outfile << "12 " << std::get<1>(result12) << std::endl;
        outfile << "16 " << std::get<1>(result16) << std::endl;
    }

    {
        std::ofstream outfile("binding_setnotify.txt");
        outfile << "connections time" << std::endl;
        outfile << "0 " << std::get<2>(result0) << std::endl;
        outfile << "1 " << std::get<2>(result1) << std::endl;
        outfile << "2 " << std::get<2>(result2) << std::endl;
        outfile << "3 " << std::get<2>(result3) << std::endl;
        outfile << "4 " << std::get<2>(result4) << std::endl;
        outfile << "5 " << std::get<2>(result5) << std::endl;
        outfile << "6 " << std::get<2>(result6) << std::endl;
        outfile << "7 " << std::get<2>(result7) << std::endl;
        outfile << "8 " << std::get<2>(result8) << std::endl;
        outfile << "9 " << std::get<2>(result9) << std::endl;
        outfile << "10 " << std::get<2>(result10) << std::endl;
        outfile << "11 " << std::get<2>(result11) << std::endl;
        outfile << "12 " << std::get<2>(result12) << std::endl;
        outfile << "16 " << std::get<2>(result16) << std::endl;
    }

    {
        std::ofstream outfile("binding_dirtyread.txt");
        outfile << "connections time" << std::endl;
        outfile << "0 " << std::get<3>(result0) << std::endl;
        outfile << "1 " << std::get<3>(result1) << std::endl;
        outfile << "2 " << std::get<3>(result2) << std::endl;
        outfile << "3 " << std::get<3>(result3) << std::endl;
        outfile << "4 " << std::get<3>(result4) << std::endl;
        outfile << "5 " << std::get<3>(result5) << std::endl;
        outfile << "6 " << std::get<3>(result6) << std::endl;
        outfile << "7 " << std::get<3>(result7) << std::endl;
        outfile << "8 " << std::get<3>(result8) << std::endl;
        outfile << "9 " << std::get<3>(result9) << std::endl;
        outfile << "10 " << std::get<3>(result10) << std::endl;
        outfile << "11 " << std::get<3>(result11) << std::endl;
        outfile << "12 " << std::get<3>(result12) << std::endl;
        outfile << "16 " << std::get<3>(result16) << std::endl;
    }
}