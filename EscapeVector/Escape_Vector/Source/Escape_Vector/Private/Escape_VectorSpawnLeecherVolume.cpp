

#include "Escape_Vector.h"
#include "Escape_VectorSpawnLeecherVolume.h"


AEscape_VectorSpawnLeecherVolume::AEscape_VectorSpawnLeecherVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));

	sceneComponentSpawnLeecher = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("sceneComponentSpawnLeecher"));

	RootComponent = sceneComponentSpawnLeecher;

	WhereToSpawn->AttachParent = sceneComponentSpawnLeecher;


	spawnTimer = 0.0f;
	bVolumeActivate = false;
	SpawnDelay = 2.0f;
	iNbSpawnMax = 99.0f;
	iNbSpawnTotal = 0;

	PrimaryActorTick.bCanEverTick = true;

}

void AEscape_VectorSpawnLeecherVolume::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bVolumeActivate)
	{
		iNbSpawnTotal = 0;
	}

	if (!bVolumeActivate || iNbSpawnTotal >= iNbSpawnMax)
	{
		return;
	}

	spawnTimer += DeltaSeconds;

	if (spawnTimer > SpawnDelay)
	{
		SpawnLeecher();
		spawnTimer = 0;

	}


}

FVector AEscape_VectorSpawnLeecherVolume::GetRandomPointInVolume()
{
	FVector RandomLocation;
	float MinX, MinY, MinZ;
	float MaxX, MaxY, MaxZ;

	FVector Origin;
	FVector BoxExtent;

	Origin = WhereToSpawn->Bounds.Origin;
	BoxExtent = WhereToSpawn->Bounds.BoxExtent;

	MinX = Origin.X - BoxExtent.X / 2.f;
	MinY = Origin.Y - BoxExtent.Y / 2.f;
	MinZ = Origin.Z - BoxExtent.Z / 2.f;

	MaxX = Origin.X + BoxExtent.X / 2.f;
	MaxY = Origin.Y + BoxExtent.Y / 2.f;
	MaxZ = Origin.Z + BoxExtent.Z / 2.f;

	RandomLocation.X = FMath::FRandRange(MinX, MaxX);
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

	return RandomLocation;
}

void AEscape_VectorSpawnLeecherVolume::EnableSpawning()
{
	bVolumeActivate = true;
}

void AEscape_VectorSpawnLeecherVolume::DisableSpawning()
{
	bVolumeActivate = false;
}

void AEscape_VectorSpawnLeecherVolume::SpawnLeecher()
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetRandomPointInVolume();

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.f;
			SpawnRotation.Pitch = FMath::FRand() * 360.f;
			SpawnRotation.Roll = FMath::FRand() * 360.f;

			AActor* const SpawnedPickup = World->SpawnActor<AActor>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			iNbSpawnTotal++;


		}
	}
}