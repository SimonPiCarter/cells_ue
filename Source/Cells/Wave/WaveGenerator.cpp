// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveGenerator.h"

UWavePackage* UWaveGenerator::getNextWavePackage()
{
	return spawnNextWavePackage();
}
