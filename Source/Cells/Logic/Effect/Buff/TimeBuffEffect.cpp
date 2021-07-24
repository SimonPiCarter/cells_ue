// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeBuffEffect.h"
#include "../../../MobEntity.h"
#include "../../../TowerEntity.h"
#include "../../Slot/EffectMaker/BuffOnHit.h"

UTimeBuffEffect::UTimeBuffEffect() : UBuffEffect(), _duration(0.), _fullElapsedTime(0.), _registered(false)
{}

UTimeBuffEffect::UTimeBuffEffect(float duration_p) : UBuffEffect(), _duration(duration_p), _fullElapsedTime(0.), _registered(false)
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
			_registered = true;
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

	over |= _fullElapsedTime > _duration && _duration > 0.f;

	// if last application we revert the buff
	if(over && _applied)
	{
		revert();
		if(_registered)
		{
			unregisterBuff();
		}
	} else if(_applied)
	{
		updateBuff(elapsedTime_p);
	}
}

void UTimeBuffEffect::refresh()
{
	if(_stack < _maxStack)
	{
		// revert buff with old stack count
		revert();
		// add a stack
		++_stack;
		// apply back buff with new stack count
		apply();
	}
	// reset elapsed time
	_fullElapsedTime = 0.;
}
