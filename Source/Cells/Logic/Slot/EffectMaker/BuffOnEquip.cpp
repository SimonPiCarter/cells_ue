// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffOnEquip.h"

#include <sstream>
#include <iomanip>
#include <cmath>

#include "../../Effect/Buff/BuffEquipEffect.h"

UBuffOnEquip::UBuffOnEquip() : UEffectMaker(), _buff(nullptr)
{}

void UBuffOnEquip::equip(ALogicEngine* engine, ATowerEntity* tower)
{
    _buff = spawnEffectOnEquipImpl(engine, tower);
    _buff->apply();
}

void UBuffOnEquip::unequip(ALogicEngine*, ATowerEntity*)
{
    _buff->revert();
    _buff->over = true;
}
