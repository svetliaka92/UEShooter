// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, CrosshairClass);
	if (HUD)
		HUD->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	//GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	HUD->RemoveFromViewport();

	// finalize score
	// when the widgets get created they'll get the score and show it

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
}

void AShooterPlayerController::UpdateScore(const int32 NewScore)
{
	Score = NewScore;
}

int32 AShooterPlayerController::GetScore()
{
	return Score;
}
