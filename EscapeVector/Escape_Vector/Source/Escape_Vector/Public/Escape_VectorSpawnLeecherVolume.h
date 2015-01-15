

#pragma once

#include "GameFramework/Actor.h"
#include "Escape_VectorSpawnLeecherVolume.generated.h"

/**
*
*/
UCLASS()
class AEscape_VectorSpawnLeecherVolume : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Leecher)
	TSubobjectPtr<class USceneComponent> sceneComponentSpawnLeecher;

	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	TSubobjectPtr<UBoxComponent> WhereToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AActor> WhatToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float iNbSpawnMax;

	UFUNCTION(BlueprintCallable, Category = "SpawnLeecherVolume")
	void EnableSpawning();

	UFUNCTION(BlueprintCallable, Category = "SpawnLeecherVolume")
	void DisableSpawning();

private:

	bool bVolumeActivate;

	float spawnTimer;

	int iNbSpawnTotal;

	void SpawnLeecher();

	FVector GetRandomPointInVolume();


	virtual void Tick(float DeltaSeconds) override;



};
