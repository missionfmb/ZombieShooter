// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Weapons/ZSWeapon.h"
#include "../../Public/Player/PlayerCharacter.h"
#include "../../ZombieShooter.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AZSWeapon::AZSWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh1P"));
	Mesh1P->bReceivesDecals = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = Mesh1P;

	Mesh3P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh3P"));
	Mesh3P->bReceivesDecals = false;
	Mesh3P->CastShadow = true;
	Mesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh3P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	Mesh3P->SetupAttachment(Mesh1P);


}

void AZSWeapon::OnRep_MyPawn()
{
	if (MyPawn)
	{
		OnEnterInventory(MyPawn);
	}
	else
	{
		OnLeaveInventory();
	}
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
	Super::PostInitializeComponents();
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

USkeletalMeshComponent * AZSWeapon::GetWeaponMesh() const
{
	return (MyPawn != NULL && MyPawn->IsFirstPerson()) ? Mesh1P : Mesh3P;
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

void AZSWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		DetachMeshFromPawn();

		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		if (MyPawn->IsLocallyControlled() == true)
		{
			USkeletalMeshComponent* PawnMesh1P = MyPawn->GetSpecificPawnMesh(true);
			USkeletalMeshComponent* PawnMesh3P = MyPawn->GetSpecificPawnMesh(false);

			Mesh1P->SetHiddenInGame(false);
			Mesh3P->SetHiddenInGame(false);
			Mesh1P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
			Mesh3P->AttachToComponent(PawnMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
		}
		else
		{
			USkeletalMeshComponent* UseWeaponMesh = GetWeaponMesh();
			USkeletalMeshComponent* UsePawnMesh = MyPawn->GetPawnMesh();
			UseWeaponMesh->AttachToComponent(UsePawnMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
			UseWeaponMesh->SetHiddenInGame(false);
		}
	}
}

void AZSWeapon::DetachMeshFromPawn()
{
	Mesh1P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh1P->SetHiddenInGame(true);

	Mesh3P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh3P->SetHiddenInGame(true);
}

void AZSWeapon::SetOwningPawn(APlayerCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		Instigator = NewOwner;
		MyPawn = NewOwner;
		// net owner for RPC calls
		SetOwner(NewOwner);
	}
}

void AZSWeapon::OnEquip(const AZSWeapon * LastWeapon)
{
	AttachMeshToPawn();
}

void AZSWeapon::OnEquipFinished()
{
}

void AZSWeapon::OnUnEquip()
{
}

void AZSWeapon::OnEnterInventory(APlayerCharacter * NewOwner)
{
	SetOwningPawn(NewOwner);
}

void AZSWeapon::OnLeaveInventory()
{
	if (IsAttachedToPawn())
	{
		OnUnEquip();
	}
	if (Role == ROLE_Authority)
	{
		SetOwningPawn(NULL);
	}
}

bool AZSWeapon::IsEquipped() const
{
	return false;
}

bool AZSWeapon::IsAttachedToPawn() const
{
	return false;
}

void AZSWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AZSWeapon, MyPawn);
}