// Fill out your copyright notice in the Description page of Project Settings.


#include "Slot.h"
#include <cmath>

// Sets default values
USlot::USlot() : _isAttackModifier(false), _isEffectMaker(false), _descriptor(nullptr)
{}
USlot::USlot(bool attackModifier_p, bool effectMaker_p) : _isAttackModifier(attackModifier_p), _isEffectMaker(effectMaker_p)
{}
USlot::~USlot()
{
    delete _descriptor;
}
float USlot::cround(float val_p)
{
    return std::ceil(val_p * 100.f) / 100.f;
}

void USlot::updateDescription()
{
    if(_descriptor)
    {
        description = FString(_descriptor->createDescription().c_str());
    }
}

void USlot::setSlotDescriptor(SlotDescriptor * descriptor_p)
{
    _descriptor = descriptor_p;
    updateDescription();
}
