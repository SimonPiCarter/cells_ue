// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowEffect.h"
#include "../../../../MobEntity.h"
#include "../../../../TowerEntity.h"
#include "../TimeBuffEffect.h"

USlowEffect::USlowEffect() : UTimeBuffEffect()
{
	setId("SlowEffect");
}
USlowEffect::USlowEffect(float duration_p, float slow_p) : UTimeBuffEffect(duration_p), _slow(slow_p)
{
	setId("SlowEffect");
}

void USlowEffect::apply()
{
	_mobTarget->speed = _mobTarget->speed * ( 1.f-std::min<float>(0.99f,_slow*_stack) );
}

void USlowEffect::revert()
{
	_mobTarget->speed = _mobTarget->speed / ( 1.f-std::min<float>(0.99f,_slow*_stack) );
}
