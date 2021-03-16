// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChangerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULevelChangerComponent::ULevelChangerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULevelChangerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void ULevelChangerComponent::ChangeLevel(FName LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
