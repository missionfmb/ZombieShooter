// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "..\..\Public\Player\PlayerCharacter.h"

void APlayerCharacter::AddWeapon(AZSWeapon * Weapon)
{
	//TODO
}

void APlayerCharacter::RemoveWeapon(AZSWeapon * Weapon)
{
	//TODO
}

void APlayerCharacter::StartWeaponFire()
{
	//TODO
}

void APlayerCharacter::StopWeaponFire()
{
	//TODO
}

bool APlayerCharacter::CanFire() const
{
	//TODO
	return false;
}

bool APlayerCharacter::CanReload() const
{
	//TODO
	return false;
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

