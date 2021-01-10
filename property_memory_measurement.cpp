//
// Created by andreasbuhr on 10.01.21.
//

#include "property_memory_measurement.h"

#include "configuration.h"


#include <iostream>
#include <fstream>
#include "omp.h"
#include <vector>
#include "PubSub.h"

#include "private/qproperty_p.h"

auto new_memory_usage_for_binding_0(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 0; ++i){
        properties2[i].setBinding(
                [](){
                    return 0;
                });
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_1(){
    std::vector<int> access_pattern;
    int num_upstream = 1;
    for(int i = 0; i < num_samples; ++i){
        for(int i = 0; i < num_upstream; ++i){
            access_pattern.push_back(i);
        }
    }
    std::random_shuffle(access_pattern.begin(), access_pattern.end());

    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 0; ++i){
        properties2[i].setBinding(
                [](int a){
                    return a;
                },
                properties[access_pattern[num_upstream*i+0]]
                );
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_2(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 1; ++i){
        properties2[i].setBinding(
                [](int a, int b){
                    return a + b;
                },
                properties[i],
                properties[i+1]
                );
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_3(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 2; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c){
                    return a + b + c;
                },
                properties[i],
                properties[i+1],
                properties[i+2]
                );
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_4(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 3; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d){
                    return a + b + c + d;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3]
                );
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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


auto new_memory_usage_for_binding_5(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 4; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e){
                    return a + b + c + d + e;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_6(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 5; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f){
                    return a + b + c + d + e
                           + f;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_7(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 6; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g){
                    return a + b + c + d + e
                           + f, + g;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_8(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 7; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g, int h){
                    return a + b + c + d + e
                           + f, + g + h;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6],
                properties[i+7]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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

auto new_memory_usage_for_binding_9(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 8; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g, int h, int j){
                    return a + b + c + d + e
                           + f, + g + h + j;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6],
                properties[i+7],
                properties[i+8]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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


auto new_memory_usage_for_binding_10(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 9; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g, int h, int j, int k){
                    return a + b + c + d + e
                           + f, + g + h + j + k;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6],
                properties[i+7],
                properties[i+8],
                properties[i+9]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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


auto new_memory_usage_for_binding_11(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 10; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g, int h, int j, int k, int l){
                    return a + b + c + d + e
                           + f, + g + h + j + k
                                        + l;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6],
                properties[i+7],
                properties[i+8],
                properties[i+9],
                properties[i+10]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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


auto new_memory_usage_for_binding_12(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 11; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g, int h, int j, int k, int l, int m){
                    return a + b + c + d + e
                           + f, + g + h + j + k
                                        + l + m;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6],
                properties[i+7],
                properties[i+8],
                properties[i+9],
                properties[i+10],
                properties[i+11]);
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
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


auto new_memory_usage_for_binding_16(){
    std::vector<Property<int>> properties(num_samples);
    for(auto& p : properties)
        p.setValue(5);
    std::vector<Property<int>> properties2(num_samples);
    double baseline = getMemUsage();
    double starttime = omp_get_wtime();
    for(int i = 0; i < num_samples - 15; ++i){
        properties2[i].setBinding(
                [](int a, int b, int c, int d, int e, int f, int g, int h, int j, int k, int l, int m, int n, int o, int p, int q){
                    return a + b + c + d + e
                           + f, + g + h + j + k
                                + l + m + n + o + p
                                + q;
                },
                properties[i],
                properties[i+1],
                properties[i+2],
                properties[i+3],
                properties[i+4],
                properties[i+5],
                properties[i+6],
                properties[i+7],
                properties[i+8],
                properties[i+9],
                properties[i+10],
                properties[i+11],
                properties[i+12],
                properties[i+13],
                properties[i+14],
                properties[i+15]
        );
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[15].numDownstreamObservers() << std::endl;
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

void print_newbinding_memusage() {
    // measurements:
    auto result0 = new_memory_usage_for_binding_0(); 
    auto result1 = new_memory_usage_for_binding_1 () ;
    auto result2 = new_memory_usage_for_binding_2 () ;
    auto result3 = new_memory_usage_for_binding_3 () ;
    auto result4 = new_memory_usage_for_binding_4 () ;
    auto result5 = new_memory_usage_for_binding_5 () ;
    auto result6 = new_memory_usage_for_binding_6 () ;
    auto result7 = new_memory_usage_for_binding_7 () ;
    auto result8 = new_memory_usage_for_binding_8 () ;
    auto result9 = new_memory_usage_for_binding_9 () ;
    auto result10 = new_memory_usage_for_binding_10();
    auto result11 = new_memory_usage_for_binding_11();
    auto result12 = new_memory_usage_for_binding_12();
    auto result16 = new_memory_usage_for_binding_16();


    {
        std::ofstream outfile("newbinding_memusage.txt");
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
        std::ofstream outfile("newbinding_nondirtyread.txt");
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
        std::ofstream outfile("newbinding_setnotify.txt");
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
        std::ofstream outfile("newbinding_dirtyread.txt");
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