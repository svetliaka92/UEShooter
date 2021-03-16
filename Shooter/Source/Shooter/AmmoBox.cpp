// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "Engine/TriggerVolume.h"
#include "ShooterCharacter.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(Mesh);
	
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnBoxOverlap);
}

void AAmmoBox::OnBoxOverlap(UPrimitiveComponent* me,
							AActor* OtherActor,
							UPrimitiveComponent* OtherComp,
							int32 idx,
							bool FromSweep,
							const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
		if (ShooterCharacter)
		{
			ShooterCharacter->AddMagazines(Capacity);
			bIsAvailable = false;

			if (Mesh)
			{
				Mesh->SetVisibility(false);
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}

			if (bCanRespawn)
			{
				GetWorldTimerManager().SetTimer(RespawnTimer, this, &AAmmoBox::RespawnBox, RespawnSeconds);
			}
		}
	}
}

void AAmmoBox::RespawnBox()
{
	bIsAvailable = true;

	if (Mesh)
	{
		Mesh->SetVisibility(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
