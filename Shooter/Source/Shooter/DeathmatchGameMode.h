// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "DeathmatchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ADeathmatchGameMode : public AShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* KilledPawn) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
