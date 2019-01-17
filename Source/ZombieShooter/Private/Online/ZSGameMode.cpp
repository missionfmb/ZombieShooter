// Fill out your copyright notice in the Description page of Project Settings.

#include "ZSGameMode.h"
#include "../../Public/Player/PlayerCharacter.h"
#include "../../Public/Player/ZombieShooterPlayerController.h"
#include "../../Public/Online/ZSPlayerState.h"
#include "../../Public/Online/ZSGameState.h"


AZSGameMode::AZSGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnOb(TEXT("/Game/Blueprints/Pawns/PlayerPawn"));
	DefaultPawnClass = PlayerPawnOb.Class;

	PlayerControllerClass = AZombieShooterPlayerController::StaticClass();
	PlayerStateClass = AZSPlayerState::StaticClass();
	GameStateClass = AZSGameState::StaticClass();

	bUseSeamlessTravel = true;
}