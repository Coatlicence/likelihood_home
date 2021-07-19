// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TheHomeOfMyDreamGameMode.h"
#include "TheHomeOfMyDreamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheHomeOfMyDreamGameMode::ATheHomeOfMyDreamGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
