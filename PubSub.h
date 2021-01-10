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

class UntypedProperty {
public:
    UntypedProperty() = default;
    UntypedProperty(const UntypedProperty&) = delete;
    UntypedProperty(UntypedProperty&&) = delete;
    UntypedProperty& operator=(const UntypedProperty&) = delete;
    UntypedProperty& operator=(UntypedProperty&&) = delete;
    ~UntypedProperty();

protected:
    void markDirty() const;
    void potentialEagerEvaluation();
    void evaluate();

    std::unique_ptr<UntypedBinding> myBinding_;

private:
    friend class UntypedBinding;

    std::vector<UntypedBinding*> downstreamBindings_;
    void addDownstreamBinding(UntypedBinding* binding);
    void removeDownstreamBinding(UntypedBinding* binding);

};

class UntypedBinding {
public:
    UntypedBinding() = delete;
    UntypedBinding(UntypedProperty* const myProperty);
    UntypedBinding(const UntypedBinding&) = delete;
    UntypedBinding(UntypedBinding&&) = delete;
    UntypedBinding& operator=(const UntypedBinding&) = delete;
    UntypedBinding& operator=(UntypedBinding&&) = delete;
    virtual ~UntypedBinding();

protected:
    void connectToUpstreamProperty(UntypedProperty* prop);
    void disconnectFromPublisher(UntypedProperty* prop);

    bool dirty_ = true;
    bool broken_ = false; // broken dependency because of deleted publisher
    bool eagerEvaluation_ = false;

    UntypedProperty* const myProperty_;

private:
    friend class UntypedProperty;

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

template<typename T>
class Property : public UntypedProperty {
public:
    Property(T value) : value_(value) {}
    void setValue(T value);

    T getValue();

    template<typename Callable, typename... Probs>
    void setBinding(const Callable& c, Probs&&... args);

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
        (disconnectFromPublisher(&p), ...);
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
            return c_(p.getValue() ...);
        }, upstreamProperties_);
        dirty_ = false;
    }
}

void UntypedBinding::markDirty() {
    dirty_ = true;
    myProperty_->markDirty();
}

void UntypedBinding::connectToUpstreamProperty(UntypedProperty *prop) {
    prop->addDownstreamBinding(this);
}

void UntypedBinding::disconnectFromPublisher(UntypedProperty *prop) {
    prop->removeDownstreamBinding(this);
}

void UntypedBinding::markBroken() {
    broken_ = true;
}

void UntypedBinding::potentialEagerEvaluation() {
    if (eagerEvaluation_){
        evaluation();
    }
    myProperty_->potentialEagerEvaluation();
}

UntypedBinding::~UntypedBinding() {

}

UntypedBinding::UntypedBinding(UntypedProperty *const myProperty) : myProperty_(myProperty) {

}


template<typename T>
void Property<T>::setValue(T value) {
    if (myBinding_.get() != nullptr){
        myBinding_.reset();
    }
    value_ = value;
    markDirty();
}

template<typename T>
T Property<T>::getValue() {
    evaluate();
    return value_;
}

template<typename T>
template<typename Callable, typename... Probs>
void Property<T>::setBinding(const Callable &c, Probs &&... args) {
    using result_type = decltype(c(args.getValue()...));
    static_assert(std::is_same_v<result_type, T>, "incompatible return type");
    myBinding_.reset(new Binding<result_type, Callable, Probs...>{this, c, args...});
}

UntypedProperty::~UntypedProperty() {
    for( auto* s : downstreamBindings_){
        s->markBroken();
    }
}

void UntypedProperty::markDirty() const {
    for( auto* s : downstreamBindings_){
        s->markDirty();
    }
}

void UntypedProperty::addDownstreamBinding(UntypedBinding *binding) {
    if(std::find(downstreamBindings_.begin(), downstreamBindings_.end(), binding) == downstreamBindings_.end())
        downstreamBindings_.push_back(binding);
}

void UntypedProperty::removeDownstreamBinding(UntypedBinding *binding) {
    auto it = std::remove(downstreamBindings_.begin(), downstreamBindings_.end(), binding);
    downstreamBindings_.erase(it);
}

void UntypedProperty::evaluate() {
    if (myBinding_.get() != nullptr){
        myBinding_->evaluation();
    }
}

void UntypedProperty::potentialEagerEvaluation() {
    for( auto* s : downstreamBindings_){
        s->potentialEagerEvaluation();
    }
}

#endif //QPROPERTY_PERFORMANCE_REPORT_PUBSUB_H
