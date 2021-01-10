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

double new_memory_usage_for_binding_0(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_1(){
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
                properties[i]
                );
        properties2[i].value();
    }
    double endtime = omp_get_wtime();
    std::cout << "observers: " << properties[12].numDownstreamObservers() << std::endl;
    double after = getMemUsage();
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_2(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_3(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_4(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double new_memory_usage_for_binding_5(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_6(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_7(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_8(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

double new_memory_usage_for_binding_9(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double new_memory_usage_for_binding_10(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double new_memory_usage_for_binding_11(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}


double new_memory_usage_for_binding_12(){
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
    std::cout << "mem usage per lambda property binding " << (after - baseline) / double(num_samples) << std::endl;
    std::cout << "time usage per setBinding " << (endtime - starttime) / double(num_samples) << std::endl;
    return (after - baseline) / double(num_samples);
}

void print_newbinding_memusage() {
    std::ofstream outfile("newbinding_memusage.txt");
    outfile << "connections memory" << std::endl;
    outfile << "0 " << new_memory_usage_for_binding_0() << std::endl;
    outfile << "1 " << new_memory_usage_for_binding_1() << std::endl;
    outfile << "2 " << new_memory_usage_for_binding_2() << std::endl;
    outfile << "3 " << new_memory_usage_for_binding_3() << std::endl;
    outfile << "4 " << new_memory_usage_for_binding_4() << std::endl;
    outfile << "5 " << new_memory_usage_for_binding_5() << std::endl;
    outfile << "6 " << new_memory_usage_for_binding_6() << std::endl;
    outfile << "7 " << new_memory_usage_for_binding_7() << std::endl;
    outfile << "8 " << new_memory_usage_for_binding_8() << std::endl;
    outfile << "9 " << new_memory_usage_for_binding_9() << std::endl;
    outfile << "10 " << new_memory_usage_for_binding_10() << std::endl;
    outfile << "11 " << new_memory_usage_for_binding_11() << std::endl;
    outfile << "12 " << new_memory_usage_for_binding_12() << std::endl;
}