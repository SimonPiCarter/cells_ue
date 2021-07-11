// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeBuffEffect.h"
#include "../../../MobEntity.h"
#include "../../../TowerEntity.h"
#include "../../Slot/EffectMaker/BuffOnHit.h"

UTimeBuffEffect::UTimeBuffEffect() : UBuffEffect(), _duration(0.), _fullElapsedTime(0.)
{}

UTimeBuffEffect::UTimeBuffEffect(float duration_p) : UBuffEffect(), _duration(duration_p), _fullElapsedTime(0.)
{}

void UTimeBuffEffect::runEffect(float elapsedTime_p)
{
	// if first application
	if(!_applied)
	{
		// if not already registered we add it
		if(!isRegistered())
		{
			_applied = true;
			// add a stack
			++_stack;
			// apply buff
			apply();
			// register buff in target
			registerBuff();
		}
		// else just refresh
		else
		{
			getRegisteredBuff().refresh();
			// if we have refreshed the other instance of the same buff
			// we delete this sone asap
			over = true;
		}
	}

	_fullElapsedTime += elapsedTime_p;

	over = _fullElapsedTime > _duration;

	// if last application we revert the buff
	if(over && _applied)
	{
		revert();
		unregisterBuff();
	}
}
