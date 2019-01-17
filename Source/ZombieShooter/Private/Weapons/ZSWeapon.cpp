// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Weapons/ZSWeapon.h"
#include "../../Public/Player/PlayerCharacter.h"

// Sets default values
AZSWeapon::AZSWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZSWeapon::ClientStartReload_Implementation()
{

}

void AZSWeapon::PostInitializeComponents()
{
}

void AZSWeapon::Destroyed()
{
}

void AZSWeapon::GiveAmmo(int AddAmount)
{
}

void AZSWeapon::UseAmmo()
{
}

void AZSWeapon::StartFire()
{
}

void AZSWeapon::StopFire()
{
}

void AZSWeapon::StartReload(bool FromReplication)
{
}

void AZSWeapon::StopReload()
{
}

void AZSWeapon::ReloadWeapon()
{
}


bool AZSWeapon::CanFire() const
{
	return false;
}

bool AZSWeapon::CanReload() const
{
	return false;
}

void AZSWeapon::OnEquip(const AZSWeapon * LastWeapon)
{
}

void AZSWeapon::OnEquipFinished()
{
}

void AZSWeapon::OnUnEquip()
{
}

void AZSWeapon::OnEnterInventory(APlayerCharacter * NewOwner)
{
}

void AZSWeapon::OnLeaveInventory()
{
}

bool AZSWeapon::IsEquipped() const
{
	return false;
}

bool AZSWeapon::IsAttachedToPawn() const
{
	return false;
}
