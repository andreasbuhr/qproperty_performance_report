//
// Created by andreasbuhr on 08.01.21.
//

#ifndef QPROPERTY_PERFORMANCE_REPORT_PUBSUB_H
#define QPROPERTY_PERFORMANCE_REPORT_PUBSUB_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

class UntypedBinding;

template<typename T, typename Callable, typename... Probs>
class Binding;

template<typename T>
class Property;

class UntypedPublisher {
public:
    UntypedPublisher() = default;
    UntypedPublisher(const UntypedPublisher&) = delete;
    UntypedPublisher(UntypedPublisher&&) = delete;
    UntypedPublisher& operator=(const UntypedPublisher&) = delete;
    UntypedPublisher& operator=(UntypedPublisher&&) = delete;
    ~UntypedPublisher();

    int numDownstreamObservers() const { return downstreamBindings_.size(); }
    void removeBinding();
    void setBinding(UntypedBinding *binding);

    void markDirty() const;
    void potentialEagerEvaluation();
    void evaluate();

    std::unique_ptr<UntypedBinding> myBinding_;

private:
    friend class UntypedBinding;
    friend class UntypedProperty;
    template<typename T2>
    friend class Property;

    std::vector<UntypedBinding*> downstreamBindings_;
    void addDownstreamBinding(UntypedBinding* binding);
    void removeDownstreamBinding(UntypedBinding* binding);

};

class UntypedProperty;

class UntypedBinding {
public:
    UntypedBinding() = delete;
    UntypedBinding(UntypedProperty *const myProperty);
    UntypedBinding(const UntypedBinding&) = delete;
    UntypedBinding(UntypedBinding&&) = delete;
    UntypedBinding& operator=(const UntypedBinding&) = delete;
    UntypedBinding& operator=(UntypedBinding&&) = delete;
    virtual ~UntypedBinding();

protected:
    void connectToUpstreamProperty(UntypedProperty *prop);
    void disconnectFromUpstreamProperty(UntypedProperty *prop);

    bool dirty_ = true;
    bool broken_ = false; // broken dependency because of deleted publisher
    bool eagerEvaluation_ = false;

    UntypedProperty* const myProperty_;

private:
    friend class UntypedPublisher;

    void markDirty();
    void potentialEagerEvaluation();
    void markBroken();
    virtual void evaluation() = 0;
};


template<typename T, typename Callable, typename... Props>
class Binding : public UntypedBinding {
public:
    explicit Binding(Property<T>* myProperty, Callable c, Props ...props);
    ~Binding();
private:
    void evaluation() override final;

    Callable c_;
    std::tuple<Props...> upstreamProperties_;
};


class UntypedProperty{
public:
    void markDirty() const;
    void potentialEagerEvaluation() const;

    void addDownstreamBinding(UntypedBinding* binding);
    void removeDownstreamBinding(UntypedBinding* binding);

protected:
    std::unique_ptr<UntypedPublisher> publisher_;
};

template<typename T>
class Property : public UntypedProperty {
public:
    Property() = default;
    Property(T value) : value_(value) {}
    void setValue(T value);

    T value();

    template<typename Callable, typename... Probs>
    void setBinding(const Callable& c, Probs&&... args);

    int numDownstreamObservers() const;

private:
    template<typename T2, typename Callable, typename... Probs>
    friend class Binding;

    T value_;
};

/////////////////////////////////////////////////
// definitions
/////////////////////////////////////////////////


template<typename T, typename Callable, typename... Props>
Binding<T, Callable, Props...>::Binding(Property<T>* myProperty, Callable c, Props... props)
        : UntypedBinding(myProperty), c_(c), upstreamProperties_({props...})
{
    static_assert(sizeof(c_) == 1); // no captures in lambda
    (connectToUpstreamProperty(&props), ...);
}

template<typename T, typename Callable, typename... Probs>
Binding<T, Callable, Probs...>::~Binding() {
    // disconnect from publishers:
    std::apply([this](Probs... p){
        (disconnectFromUpstreamProperty(&p), ...);
    }, upstreamProperties_);
}

template<typename T, typename Callable, typename... Probs>
void Binding<T, Callable, Probs...>::evaluation() {
    if(broken_){
        exit(1);
    }
    if(dirty_){
        Property<T>* myprop = (Property<T>*) myProperty_;
        myprop->value_ = std::apply([this](Probs... p){
            return c_(p.value() ...);
        }, upstreamProperties_);
        dirty_ = false;
    }
}



template<typename T>
void Property<T>::setValue(T value) {
    if(publisher_.get() != nullptr)
        publisher_->removeBinding();

    value_ = value;
    if(publisher_.get() != nullptr)
        publisher_->markDirty();
}

template<typename T>
T Property<T>::value() {
    if(publisher_.get() != nullptr)
        publisher_->evaluate();

    return value_;
}

template<typename T>
template<typename Callable, typename... Probs>
void Property<T>::setBinding(const Callable &c, Probs &&... args) {
    using result_type = decltype(c(args.value()...));
    static_assert(std::is_same_v<result_type, T>, "incompatible return type");
    static bool printed = false;
    if(!printed){
        std::cout << sizeof(Binding<result_type, Callable, Probs...>) << std::endl;
        printed=true;
    }
    if(publisher_.get() == nullptr)
        publisher_.reset(new UntypedPublisher);

    publisher_->setBinding(new Binding<result_type, Callable, Probs...>{this, c, args...});
}

template<typename T>
int Property<T>::numDownstreamObservers() const {
    if(publisher_.get() != nullptr)
        return publisher_->numDownstreamObservers();
    return 0;
}

#endif //QPROPERTY_PERFORMANCE_REPORT_PUBSUB_H
