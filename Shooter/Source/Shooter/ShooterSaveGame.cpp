// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "SoundOptions.h"

void UShooterSaveGame::SetOptions(USoundOptions* SoundOptionsToSet)
{
	SavedSoundOptions = SoundOptionsToSet;
}

void UShooterSaveGame::SaveOptions(FString SlotName)
{
	UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

USoundOptions* UShooterSaveGame::GetSoundOptionsData()
{
	return SavedSoundOptions;
}
