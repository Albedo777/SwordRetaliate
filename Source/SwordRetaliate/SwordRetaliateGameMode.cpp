// Copyright Epic Games, Inc. All Rights Reserved.

#include "SwordRetaliateGameMode.h"
#include "SwordRetaliateCharacter.h"

ASwordRetaliateGameMode::ASwordRetaliateGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASwordRetaliateCharacter::StaticClass();	
}
