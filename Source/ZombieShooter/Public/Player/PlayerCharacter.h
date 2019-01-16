// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ZOMBIESHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


	void AddWeapon(class AZSWeapon* Weapon);

	void RemoveWeapon(class AZSWeapon* Weapon);



	/*Locally Starts weapon fire*/
	void StartWeaponFire();

	void StopWeaponFire();

	bool CanFire() const;

	bool CanReload() const;
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
