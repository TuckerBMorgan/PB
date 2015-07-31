// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PB.h"
#include "PBGameMode.h"
#include "PBCharacter.h"

APBGameMode::APBGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScroller/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
