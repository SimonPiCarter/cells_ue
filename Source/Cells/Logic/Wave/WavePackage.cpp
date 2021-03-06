// Fill out your copyright notice in the Description page of Project Settings.


#include "WavePackage.h"


UWavePackage::UWavePackage()
{
	_wave.time = 0;
}

void UWavePackage::addMobEntityLayout(FString const& cat, FString const& name, int qty, float delay
	, float maxHitpoint, float speed, float damageLife, float scrapReward)
{
	MobEntityLayout layout_l;
	layout_l.mob_category = TCHAR_TO_UTF8(*cat);
	layout_l.mob_name = TCHAR_TO_UTF8(*name);
	layout_l.quantity = qty;
	layout_l.delay = delay;
	layout_l.maxHitpoint = maxHitpoint;
	layout_l.speed = speed;
	layout_l.damageLife = damageLife;
	layout_l.scrapReward = scrapReward;

	_wave.mobLayout.push_back(layout_l);
}

void UWavePackage::setWaveTimeToPrepare(float delay)
{
	_wave.time = delay;
}
