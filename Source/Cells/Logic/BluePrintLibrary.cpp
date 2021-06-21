// Fill out your copyright notice in the Description page of Project Settings.


#include "BluePrintLibrary.h"

// Sets default values
ABluePrintLibrary::ABluePrintLibrary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABluePrintLibrary::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABluePrintLibrary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

std::string ABluePrintLibrary::computeKey(std::string const& category_p, std::string const& name_p)
{
	return category_p + "/" + name_p;
}

void ABluePrintLibrary::addBluePrint(FString const& category_p, FString const& name_p, UBlueprint* bp_p)
{
	std::string key_p = computeKey(TCHAR_TO_UTF8(*category_p), TCHAR_TO_UTF8(*name_p));
	lib[key_p] = bp_p;
}

UBlueprint* ABluePrintLibrary::getBluePrint(std::string const& category_p, std::string const& name_p)
{
	return lib[computeKey(category_p, name_p)];
}
