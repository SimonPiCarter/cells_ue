// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"

AEffect::AEffect()
	: onHold(false)
	, over(false)
{}

void AEffect::runlogic(float elapsedTime_p, float remainingTime_p)
{
	if (!onHold && !over)
	{
		runEffect(elapsedTime_p, remainingTime_p);
	}
}
