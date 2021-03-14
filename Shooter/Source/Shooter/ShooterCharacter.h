// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGunActor;

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount,
							 struct FDamageEvent const& DamageEvent,
							 class AController* EventInstigator,
							 AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void Shoot();

	void ReloadGun();

	UFUNCTION(BlueprintPure)
	void UpdateGunUI() const;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	template<int32 Index>
	void SwitchToWeaponTemplate()
	{
		SwitchToWeapon(Index);
	}

	template<int32 NextIndex>
	void CycleWeaponTemplate()
	{
		CycleWeapon(NextIndex);
	}

	void SwitchToWeapon(int32 WeaponIndex);
	void CycleWeapon(int32 CycleDirection);

	UPROPERTY(EditAnywhere)
	float RotationRateUp = 10.0f;
	UPROPERTY(EditAnywhere)
	float RotationRateRight = 10.f;

	UPROPERTY(EditAnywhere)
	bool bCanUseMultipleGuns = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunActor> GunClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGunActor>> GunClasses;

	UPROPERTY()
	TArray<AGunActor*> Guns;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentGunIndex = 0;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health = 0.f;

	UPROPERTY(VisibleAnywhere)
	int32 GunMagazines = 2;

};
