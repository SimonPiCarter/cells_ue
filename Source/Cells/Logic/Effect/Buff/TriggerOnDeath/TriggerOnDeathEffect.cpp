// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerOnDeathEffect.h"
#include "../../../../MobEntity.h"
#include "../../../LogicEngine.h"
#include "../../AttackEffect.h"

UTriggerOnDeathEffect::UTriggerOnDeathEffect() : UTimeBuffEffect(), _triggered(false)
{
	setId("TriggerOnDeathEffect");
}

void UTriggerOnDeathEffect::updateBuff(float)
{
	if(_mobTarget && _mobTarget->hitpoint <= 0.f)
	{
		if(!_triggered)
		{
			// trigger effect
			deathTrigger();
		}
		_triggered = true;
		over = true;
		return;
	}
}
