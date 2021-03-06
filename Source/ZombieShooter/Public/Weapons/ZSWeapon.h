// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZSWeapon.generated.h"


namespace EWeaponState
{
	enum Type
	{
		Idle,
		Firing,
		Reloading,
		Equipping,
	};
}

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	bool bInfiniteAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		bool bInfiniteClip;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 AmmoPerClip;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int32 InitialClips;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponStats")
		float TimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponStats")
		float NoAnimReloadDuration;

	/** defaults */
	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteClip = false;
		MaxAmmo = 100;
		AmmoPerClip = 20;
		InitialClips = 4;
		TimeBetweenShots = 0.2f;
		NoAnimReloadDuration = 1.0f;
	}



};

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

		/** animation played on pawn (1st person view) */
		UPROPERTY(EditDefaultsOnly, Category = Animation)
		class  UAnimMontage* Pawn1P;

	/** animation played on pawn (3rd person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		class UAnimMontage* Pawn3P;
};

UCLASS(Abstract, Blueprintable)
class ZOMBIESHOOTER_API AZSWeapon : public AActor
{
	GENERATED_UCLASS_BODY()


	virtual void PostInitializeComponents() override;

	virtual void Destroyed() override;

	enum class EAmmoType
	{
		EBullet,
		ERocket,
		EMax
	};


	void GiveAmmo(int AddAmount);

	void UseAmmo();

	virtual EAmmoType GetAmmoType() const
	{
		return EAmmoType::EBullet;
	}


	/** get weapon mesh (needs pawn owner to determine variant) */
	USkeletalMeshComponent* GetWeaponMesh() const;



	/*
	* Inventory
	*/


	virtual void OnEquip(const AZSWeapon* LastWeapon);

	virtual void OnEquipFinished();

	virtual void OnUnEquip();

	virtual void OnEnterInventory(class APlayerCharacter* NewOwner);

	virtual void OnLeaveInventory();

	bool IsEquipped() const;

	bool IsAttachedToPawn() const;

	/*
	* Input
	*/

	virtual void StartFire();

	virtual void StopFire();

	virtual void StartReload(bool FromReplication = false);

	virtual void StopReload();

	virtual void ReloadWeapon();

	UFUNCTION(Reliable, Client)
		void ClientStartReload();

	/*
	* Control
	*/

	bool CanFire() const;

	bool CanReload() const;

	/** check if weapon has infinite ammo (include owner's cheats) */
	bool HasInfiniteAmmo() const;

	/** check if weapon has infinite clip (include owner's cheats) */
	bool HasInfiniteClip() const;




protected:

	void AttachMeshToPawn();

	void DetachMeshFromPawn();



private:
	/** weapon mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** weapon mesh: 3rd person view */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh3P;

protected:

	/** pawn owner */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_MyPawn)
		class APlayerCharacter* MyPawn;

	/** weapon data */
	UPROPERTY(EditDefaultsOnly, Category = Config)
		FWeaponData WeaponConfig;

	//////////////////////////////////////////////////////////////////////////
	// Replication & effects

	UFUNCTION()
		void OnRep_MyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** set the weapon's owning pawn */
	void SetOwningPawn(APlayerCharacter* NewOwner);

};
