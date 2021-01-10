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


#include "omp.h"

#include "PubSub.h"

#include "configuration.h"

#include "qproperty_memory_measurement.h"

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

int main(){
    print_sizeofs();
    print_binding_memusage();

    double baseline = getMemUsage();

    std::vector<Property<int>> properties(num_samples);

    for(auto& p : properties)
        p.setValue(5);

    double after = getMemUsage();

    std::cout << "mem usage per Property<int> " << (after - baseline) / num_samples << std::endl;

    {
        std::vector<Property<int>> properties2(num_samples);
        baseline = getMemUsage();
        double starttime = omp_get_wtime();
        for(int i = 0; i < num_samples - 10; ++i){
            properties2[i].setBinding(
                    [](int a, int b, int c, int d, int e, int f, int g, int h){
                        return a+b+c+d+e+f+g+h;
                    },
                    properties[i],
                    properties[i+1],
                    properties[i+2],
                    properties[i+3],
                    properties[i+4],
                    properties[i+5],
                    properties[i+6],
                    properties[i+7]
                    );
        }
        double endtime = omp_get_wtime();
        std::cout << "observers: " << properties[10].numDownstreamObservers() << std::endl;
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
            std::cout << "observers: " << properties[10].numDownstreamObservers() << std::endl;
        }
        for(int i = 0; i < num_samples; ++i){
            properties[i].setValue(7);
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
            std::cout << "observers: " << properties[10].numDownstreamObservers() << std::endl;
        }

        for(int i = 0; i < 5; ++i){
            std::cout << properties2[i].value() << std::endl;
        }
    }
}