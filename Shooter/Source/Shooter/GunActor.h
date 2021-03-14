// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"

#include "GunActor.generated.h"

UENUM(BlueprintType)
enum EFireMode
{
	FM_SingleFire = 0,
	FM_Burst = 1,
	FM_FullAuto = 2,
};

UCLASS()
class SHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();
	void Reload();
	int32 GetAmmoCount();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactFX;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 2000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly)
	int32 AmmoPerMagazine = 30;

	UPROPERTY(EditDefaultsOnly)
	int32 Ammo = 30;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;
	void SwitchFireMode();
};
