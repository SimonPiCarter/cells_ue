// Fill out your copyright notice in the Description page of Project Settings.


#include "MultDmgEffect.h"
#include "../../../../MobEntity.h"

UMultDmgEffect::UMultDmgEffect() : UTimeBuffEffect()
{
	setId("MultDmgEffect");
}
UMultDmgEffect::UMultDmgEffect(float duration_p, float mult_p) : UTimeBuffEffect(duration_p), _mult(mult_p)
{
	setId("MultDmgEffect");
}

void UMultDmgEffect::apply()
{
	_mobTarget->damageMultiplier = _mobTarget->damageMultiplier + _mult*_stack;
}

void UMultDmgEffect::revert()
{
	_mobTarget->damageMultiplier = _mobTarget->damageMultiplier - _mult*_stack;
}
