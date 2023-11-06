// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test50GameMode.h"
#include "Test50Character.h"
#include "UObject/ConstructorHelpers.h"

ATest50GameMode::ATest50GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
