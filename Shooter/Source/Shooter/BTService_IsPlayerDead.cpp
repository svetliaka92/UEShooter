#include "BTService_IsPlayerDead.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

UBTService_IsPlayerDead::UBTService_IsPlayerDead()
{
	NodeName = "Update Is Player Dead";
}

void UBTService_IsPlayerDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter == nullptr)
		return;
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(PlayerCharacter);
	if (ShooterCharacter == nullptr)
		return;
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	if (!ShooterCharacter->IsDead())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), !ShooterCharacter->IsDead());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
