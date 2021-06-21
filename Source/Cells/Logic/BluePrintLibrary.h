// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <unordered_map>
#include <string>

#include "BluePrintLibrary.generated.h"

UCLASS()
class CELLS_API ABluePrintLibrary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABluePrintLibrary();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	std::unordered_map<std::string, UBlueprint*> lib;

	static std::string computeKey(std::string const& category_p, std::string const& name_p);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "BluePrintLibrary")
		void addBluePrint(FString const& category_p, FString const& name_p, UBlueprint * bp_p);

	UBlueprint* getBluePrint(std::string const& category_p, std::string const& name_p);
};
