// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoundingBox.h"

#include <array>
#include <list>
#include <string>
#include <unordered_map>

#include "MapLayout.generated.h"

class ABluePrintLibrary;

struct TileLayout
{
	std::string tile_category;
	std::string tile_name;
	double x;
	double y;
	int height;
	bool constructible;
};

struct MobEntityLayout
{
	std::string mob_category;
	std::string mob_name;
	int quantity;
	float delay;
};

struct WaveLayout
{
	double time;
	std::list<MobEntityLayout> mobLayout;
};

struct MapLayout
{
	BoundingBox boundingBox;
	std::array<double, 2> _spawnPoint;
	std::list<std::array<double, 2> > _checkPoints;
};

UCLASS()
class CELLS_API AMapLayout : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapLayout();
	~AMapLayout();

	MapLayout getMapLayout();
	std::list<WaveLayout *> getWaveLayouts();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	std::unordered_map<int, WaveLayout*> _waves;

	std::list<TileLayout> _tiles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLayout")
		TArray<FVector2D> checkpoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLayout")
		FVector2D spawnpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLayout")
		FVector2D pos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLayout")
		FVector2D size;

	UPROPERTY(BlueprintReadOnly, Category = "MapLayout")
		TArray<AActor*> tiles;

	UFUNCTION(BlueprintCallable, Category = "MapLayout")
		void addMobEntityLayout(int wave, FString const& cat, FString const& name, int qty, float delay);

	UFUNCTION(BlueprintCallable, Category = "MapLayout")
		void setWaveTimeToPrepare(int wave, float delay);

	UFUNCTION(BlueprintCallable, Category = "MapLayout")
		void addTile(FString const& cat, FString const& name, float x, float y, int height, bool constructible);

	void spawnMap(ABluePrintLibrary* library_p);
};
