// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/Player/PlayerCharacter.h"
#include "../../Public/Player/ZSCharacterMovementComponent.h"
#include "../../Public/Weapons/ZSWeapon.h"
#include "Engine/World.h"
#include "ZombieShooter.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UZSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("PawnMesh1P"));
	Mesh1P->SetupAttachment(RootComponent);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	Mesh1P->SetCollisionObjectType(ECC_Pawn);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

}


void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Role == ROLE_Authority)
	{
		Health = GetMaxHealth();
		SpawnDefaultInventory();
	}
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

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

}

void APlayerCharacter::SetCurrentWeapon(class AZSWeapon* NewWeapon, class AZSWeapon* LastWeapon /*= NULL*/)
{
	AZSWeapon* LocalLastWeapon = nullptr;

	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon)
	{
		LocalLastWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void APlayerCharacter::OnRep_CurrentWeapon(AZSWeapon * LastWeapon)
{
	SetCurrentWeapon(CurrentWeapon, LastWeapon);
}



void APlayerCharacter::AddWeapon(AZSWeapon * Weapon)
{
	if (Weapon && Role == ROLE_Authority)
	{
		Weapon->OnEnterInventory(this);
		Inventory.AddUnique(Weapon);
	}
}

void APlayerCharacter::RemoveWeapon(AZSWeapon * Weapon)
{
	if (Weapon && Role == ROLE_Authority)
	{
		Weapon->OnLeaveInventory();
		Inventory.RemoveSingle(Weapon);
	}
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

void APlayerCharacter::SetTargeting(bool bNewTargeting)
{
}

void APlayerCharacter::SetRunning(bool bNewRunning, bool bToggle)
{
}

void APlayerCharacter::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		const FQuat Rotation = GetActorQuat();
		const FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}

void APlayerCharacter::MoveForward(float Val)
{
	if (Controller && Val != 0.f)
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}


void APlayerCharacter::MoveUp(float Val)
{
	if (Val != 0.f)
	{
		// Not when walking or falling.
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			return;
		}

		AddMovementInput(FVector::UpVector, Val);
	}
}

void APlayerCharacter::TurnAtRate(float Val)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Val * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Val)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Val * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

FName APlayerCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

USkeletalMeshComponent * APlayerCharacter::GetSpecificPawnMesh(bool WantFirstPerson) const
{
	return WantFirstPerson == true ? Mesh1P : GetMesh();
}

bool APlayerCharacter::IsFirstPerson() const
{
	return IsAlive() && Controller && Controller->IsLocalPlayerController();
}

bool APlayerCharacter::IsAlive() const
{
	return Health > 0;
}

int32 APlayerCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<APlayerCharacter>()->Health;
}

USkeletalMeshComponent * APlayerCharacter::GetPawnMesh() const
{
	return IsFirstPerson() ? Mesh1P : GetMesh();
}

void APlayerCharacter::EquipWeapon(class AZSWeapon* Weapon)
{
	if (Weapon)
	{
		if (Role == ROLE_Authority)
		{
			SetCurrentWeapon(Weapon, CurrentWeapon);
		}
		else
		{
			ServerEquipWeapon(Weapon);
		}
	}
}

bool APlayerCharacter::ServerEquipWeapon_Validate(AZSWeapon* Weapon)
{
	return true;
}

void APlayerCharacter::ServerEquipWeapon_Implementation(AZSWeapon* Weapon)
{
	EquipWeapon(Weapon);
}

void APlayerCharacter::SpawnDefaultInventory()
{
	if (Role < ROLE_Authority)
	{
		return;
	}

	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (DefaultInventoryClasses[i]) {
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AZSWeapon* NewWeapon = GetWorld()->SpawnActor<AZSWeapon>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}

}

void APlayerCharacter::DestroyInventory()
{

}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	DOREPLIFETIME_CONDITION(APlayerCharacter, Inventory, COND_OwnerOnly);

	// everyone
	DOREPLIFETIME(APlayerCharacter, CurrentWeapon);
	DOREPLIFETIME(APlayerCharacter, Health);
}




