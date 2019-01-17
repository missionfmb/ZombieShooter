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



protected:



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
	/** Returns Mesh1P subobject **/
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

};
