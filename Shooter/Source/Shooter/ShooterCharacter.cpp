// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GunActor.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	CurrentGunIndex = 0;
	if (bCanUseMultipleGuns)
	{
		for (int i = 0; i < 3; ++i)
		{
			AGunActor* Gun = GetWorld()->SpawnActor<AGunActor>(GunClasses[i]);
			
			if (Gun)
			{
				Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
				Gun->SetOwner(this);

				if (i != CurrentGunIndex)
					Gun->SetActorHiddenInGame(true);

				Guns.Push(Gun);
			}
		}
	}
	else
	{
		AGunActor* Gun = GetWorld()->SpawnActor<AGunActor>(GunClass);
		if (Gun)
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			Gun->SetOwner(this);

			Guns.Push(Gun);
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShooterCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("WeaponChange1"), IE_Pressed, this, &AShooterCharacter::SwitchToWeaponTemplate<1>);
	PlayerInputComponent->BindAction(TEXT("WeaponChange2"), IE_Pressed, this, &AShooterCharacter::SwitchToWeaponTemplate<2>);
	PlayerInputComponent->BindAction(TEXT("WeaponChange3"), IE_Pressed, this, &AShooterCharacter::SwitchToWeaponTemplate<3>);

	PlayerInputComponent->BindAction(TEXT("WeaponCycleNext"), IE_Pressed, this, &AShooterCharacter::CycleWeaponTemplate<1>);
	PlayerInputComponent->BindAction(TEXT("WeaponCycleBack"), IE_Pressed, this, &AShooterCharacter::CycleWeaponTemplate<-1>);

	PlayerInputComponent->BindAction(TEXT("ReloadGun"), IE_Pressed, this, &AShooterCharacter::ReloadGun);
}

float AShooterCharacter::TakeDamage(float DamageAmount,
									struct FDamageEvent const& DamageEvent,
									class AController* EventInstigator,
									AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Max(Health - DamageToApply, 0.f);

	if (IsDead())
	{
		// death
		AShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}

		
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0.f;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRateUp * GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRateRight * GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::Shoot()
{
	if (Guns[CurrentGunIndex])
	{
		Guns[CurrentGunIndex]->PullTrigger();

		UpdateGunUI();
	}
}

void AShooterCharacter::SwitchToWeapon(int32 WeaponIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Picked weapon is: %i"), WeaponIndex);

	// 1 for single-fire, 2 for full auto, 3 for launcher
	if (WeaponIndex > 0 && WeaponIndex < 4)
	{
		int32 Index = WeaponIndex - 1;
		Guns[CurrentGunIndex]->SetActorHiddenInGame(true);
		Guns[Index]->SetActorHiddenInGame(false);
		CurrentGunIndex = Index;

		UpdateGunUI();
	}
}

void AShooterCharacter::CycleWeapon(int32 CycleDirection)
{
	int32 Index = (CurrentGunIndex + CycleDirection);
	if (Index >= 3)
		Index = 0;
	else if (Index < 0)
		Index = 2;
	//UE_LOG(LogTemp, Warning, TEXT("New weapon index: %i"), Index);
	SwitchToWeapon(Index + 1);
}

void AShooterCharacter::ReloadGun()
{
	if (GunMagazines > 0)
	{
		--GunMagazines;

		Guns[CurrentGunIndex]->Reload();

		UpdateGunUI();
	}
}
