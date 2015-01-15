// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Escape_Vector.h"
#include "Escape_VectorGameMode.h"
#include "Escape_VectorHUD.h"

AEscape_VectorGameMode::AEscape_VectorGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));

	DefaultPawnClass = AEscape_VectorCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = AEscape_VectorHUD::StaticClass();
}
/*
void AEscape_VectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}*/