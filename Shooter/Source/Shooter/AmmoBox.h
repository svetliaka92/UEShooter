// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

class ATriggerVolume;

UCLASS()
class SHOOTER_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	int32 Capacity = 1;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	bool bIsAvailable = true;

	UPROPERTY(EditAnywhere)
	bool bCanRespawn = false;

	UPROPERTY(EditAnywhere)
	float RespawnSeconds = 10.f;

	FTimerHandle RespawnTimer;

	void RespawnBox();

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* me, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 idx, bool FromSweep, const FHitResult& SweepResult);
};
