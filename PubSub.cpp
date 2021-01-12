//
// Created by andreasbuhr on 10.01.21.
//

#include "PubSub.h"


void UntypedBinding::markDirty() {
    dirty_ = true;
    myProperty_->markDirty();
}

void UntypedBinding::connectToUpstreamProperty(UntypedProperty *prop) {
    prop->addDownstreamBinding(this);
}

void UntypedBinding::disconnectFromUpstreamProperty(UntypedProperty *prop) {
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


UntypedPublisher::~UntypedPublisher() {
    for( auto* s : downstreamBindings_){
        s->markBroken();
    }
}

void UntypedPublisher::markDirty() const {
    for( auto* s : downstreamBindings_){
        s->markDirty();
    }
}

void UntypedPublisher::addDownstreamBinding(UntypedBinding *binding) {
    if(std::find(downstreamBindings_.begin(), downstreamBindings_.end(), binding) == downstreamBindings_.end())
        downstreamBindings_.push_back(binding);
}

void UntypedPublisher::removeDownstreamBinding(UntypedBinding *binding) {
    auto it = std::remove(downstreamBindings_.begin(), downstreamBindings_.end(), binding);
    downstreamBindings_.erase(it, downstreamBindings_.end());
}

void UntypedPublisher::evaluate() {
    if (myBinding_.get() != nullptr){
        myBinding_->evaluation();
    }
}

void UntypedPublisher::potentialEagerEvaluation() {
    for( auto* s : downstreamBindings_){
        s->potentialEagerEvaluation();
    }
}

void UntypedPublisher::removeBinding() {
    if (myBinding_.get() != nullptr){
        myBinding_.reset();
    }
}

void UntypedPublisher::setBinding(UntypedBinding *binding) {
    myBinding_.reset(binding);
}

void UntypedProperty::markDirty() const {
    if (publisher_.get() != nullptr){
        publisher_->markDirty();
    }
}

void UntypedProperty::potentialEagerEvaluation() const {
    if (publisher_.get() != nullptr){
        publisher_->potentialEagerEvaluation();
    }
}

void UntypedProperty::addDownstreamBinding(UntypedBinding *binding) {
    if (publisher_.get() == nullptr)
        publisher_.reset(new UntypedPublisher);
    publisher_->addDownstreamBinding(binding);
}

void UntypedProperty::removeDownstreamBinding(UntypedBinding *binding) {
    if (publisher_.get() == nullptr)
        exit(1);
    publisher_->removeDownstreamBinding(binding);
}
