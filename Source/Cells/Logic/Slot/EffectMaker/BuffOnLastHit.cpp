// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffOnLasHit.h"

#include <sstream>
#include <iomanip>
#include <cmath>

UBuffOnLasHit::UBuffOnLasHit() : UEffectMaker(false, false, true, false)
{}

void UBuffOnLasHit::spawnEffect(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target) const
{
    this->spawnEffectImpl(engine, source, target);
}
