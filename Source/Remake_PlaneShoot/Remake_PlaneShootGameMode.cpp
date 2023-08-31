// Copyright Epic Games, Inc. All Rights Reserved.

#include "Remake_PlaneShootGameMode.h"
#include "Remake_PlaneShootCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARemake_PlaneShootGameMode::ARemake_PlaneShootGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
