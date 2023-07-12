// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealMultiThreadingGameMode.h"
#include "UnrealMultiThreadingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealMultiThreadingGameMode::AUnrealMultiThreadingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
