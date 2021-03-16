// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "SoundOptions.generated.h"

UCLASS()
class SHOOTER_API USoundOptions : public UUserDefinedStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float MasterVolume = 0.5f;
	UPROPERTY(EditAnywhere)
	float EffectsVolume = 1.0f;
	UPROPERTY(EditAnywhere)
	float MusicVolume = 1.f;
};
