// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffOnHit.h"

#include <sstream>
#include <iomanip>
#include <cmath>

UBuffOnHit::UBuffOnHit() : UEffectMaker()
{}

void UBuffOnHit::spawnEffectOnHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const
{
    this->spawnEffectImpl(engine, source, target);
}
