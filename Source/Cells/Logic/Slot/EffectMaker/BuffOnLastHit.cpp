// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffOnLastHit.h"

#include <sstream>
#include <iomanip>
#include <cmath>

UBuffOnLastHit::UBuffOnLastHit() : UEffectMaker()
{}

void UBuffOnLastHit::spawnEffectOnLastHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target)
{
    this->spawnEffectOnLastHitImpl(engine, source, target);
}
