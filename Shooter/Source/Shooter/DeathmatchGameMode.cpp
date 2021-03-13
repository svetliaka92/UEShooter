// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchGameMode.h"

void ADeathmatchGameMode::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);

	UE_LOG(LogTemp, Warning, TEXT("Killed pawn: %s"), *KilledPawn->GetName());
}
