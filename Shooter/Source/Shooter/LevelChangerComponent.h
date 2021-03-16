// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LevelChangerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API ULevelChangerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelChangerComponent();

	UFUNCTION(BlueprintCallable)
	void ChangeLevel(FName LevelName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
