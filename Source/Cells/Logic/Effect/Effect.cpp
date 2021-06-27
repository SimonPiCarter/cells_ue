// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"

UEffect::UEffect()
	: onHold(false)
	, over(false)
{}

void UEffect::runlogic(float elapsedTime_p)
{
	if (!onHold && !over)
	{
		runEffect(elapsedTime_p);
	}
}
