// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Abstract)
class ZOMBIESHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()


	void AddWeapon(class AZSWeapon* Weapon);

	void RemoveWeapon(class AZSWeapon* Weapon);



	/*Locally Starts weapon fire*/
	void StartWeaponFire();

	void StopWeaponFire();

	bool CanFire() const;

	bool CanReload() const;

	void SetTargeting(bool bNewTargeting);

	/*
	*	Movement
	*/

	void SetRunning(bool bNewRunning, bool bToggle);

	/*
	*	Input Handlers
	*/

	void MoveForward(float Val);

	void MoveRight(float Val);

	void MoveUp(float Val);

	void TurnAtRate(float Val);

	void LookUpAtRate(float Val);

	/** get weapon attach point */
	FName GetWeaponAttachPoint() const;
	/*
* Get either first or third person mesh.
*
* @param	WantFirstPerson		If true returns the first person mesh, else returns the third
*/
	USkeletalMeshComponent* GetSpecificPawnMesh(bool WantFirstPerson) const;

	/** get camera view type */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

	/** check if pawn is still alive */
	bool IsAlive() const;

	USkeletalMeshComponent* GetPawnMesh() const;


protected:

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName WeaponAttachPoint;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class AZSWeapon>> DefaultInventoryClasses;

	UPROPERTY(Transient, Replicated)
		TArray<class AZSWeapon*> Inventory;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_CurrentWeapon)
		class AZSWeapon* CurrentWeapon;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	float BaseLookUpRate;

private:

	/** pawn mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

protected:

	void SetCurrentWeapon(class AZSWeapon* NewWeapon, class AZSWeapon* LastWeapon = NULL);

	/** current weapon rep handler */
	UFUNCTION()
		void OnRep_CurrentWeapon(class AZSWeapon* LastWeapon);

protected:
	/** Returns Mesh1P subobject **/
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		uint32 bIsDying : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
		float Health;



};
