// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShooterSaveGame.generated.h"

class USoundOptions;

UCLASS()
class SHOOTER_API UShooterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	USoundOptions* GetSoundOptionsData();

	UFUNCTION(BlueprintCallable)
	void SetOptions(USoundOptions* SoundOptionsToSet);

	UFUNCTION(BlueprintCallable)
	void SaveOptions(FString SlotName = "Slot0");

protected:
	USoundOptions* SavedSoundOptions;

private:
	
};
