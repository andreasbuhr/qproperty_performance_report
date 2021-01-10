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