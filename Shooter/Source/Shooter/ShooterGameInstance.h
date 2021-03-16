// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

UENUM(BlueprintType)
enum class ESoundChannel : uint8
{
	Master = 0,
	Effects = 1,
	Music = 2,
};

UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString SaveOptionsName = "";

	UPROPERTY(EditAnywhere)
	class UShooterSaveGame* SaveGameData = nullptr;

	UPROPERTY(EditAnywhere)
	ESoundChannel SoundChannel;

	UFUNCTION(BlueprintCallable)
	void SetVolume(ESoundChannel Channel, float Value);

	UFUNCTION(BlueprintCallable)
	void LoadGameOptions(FString SaveName);
};
