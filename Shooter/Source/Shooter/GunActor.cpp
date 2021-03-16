// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentFireMode = DefaultFireMode;
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::Fire()
{
	if (Ammo <= 0)
	{
		// empty mag sound
		return;
	}

	--Ammo;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFX, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			AController* OwnerController = GetOwnerController();
			if (OwnerController == nullptr)
				return;

			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

void AGunActor::BurstFire()
{
	Fire();

	++BurstFires;
	if (BurstFires >= BurstFireShots)
	{
		StopBurstFire();
		return;
	}
}

void AGunActor::StopBurstFire()
{
	if (GetWorldTimerManager().IsTimerActive(BurstFireTimer))
		GetWorldTimerManager().ClearTimer(BurstFireTimer);

	bIsBurstFiring = false;
}

void AGunActor::PullTrigger()
{
	if (CurrentFireMode == EFireMode::FM_SingleFire)
	{
		Fire();
	}
	else if (CurrentFireMode == EFireMode::FM_FullAuto)
	{
		Fire();

		float FireRate = 1.f / ShotsPerSecond;
		GetWorldTimerManager().SetTimer(FireTimer, this, &AGunActor::Fire, FireRate, true, FireRate);
	}
	else if (CurrentFireMode == EFireMode::FM_Burst)
	{
		if (bIsBurstFiring)
			return;

		bIsBurstFiring = true;
		BurstFires = 0;
		float FireRate = 0.15f;

		GetWorldTimerManager().SetTimer(BurstFireTimer, this, &AGunActor::BurstFire, FireRate, true, FireRate);
	}
}

void AGunActor::ReleaseTrigger()
{
	if (GetWorldTimerManager().IsTimerActive(FireTimer))
		GetWorldTimerManager().ClearTimer(FireTimer);
}

bool AGunActor::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		End,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);
}

AController* AGunActor::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;

	return OwnerPawn->GetController();
}

void AGunActor::SwitchFireMode()
{
	int32 FireModeIndex = CurrentFireModeIndex + 1;
	if (FireModeIndex >= FireModes.Num())
		FireModeIndex = 0;

	//UE_LOG(LogTemp, Warning, TEXT("The current fire mode index is: %i"), FireModeIndex);
	CurrentFireModeIndex = FireModeIndex;
	CurrentFireMode = FireModes[CurrentFireModeIndex];
}

void AGunActor::Reload()
{
	Ammo = AmmoPerMagazine;
}

int32 AGunActor::GetAmmoCount() const
{
	return Ammo;
}

FString AGunActor::GetDisplayName() const
{
	return DisplayName;
}
