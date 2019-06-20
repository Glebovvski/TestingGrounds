// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	auto Guardian = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrollingComponent>();
	if (!ensure(Guardian)) return EBTNodeResult::Failed;

	auto PatrolPoints = Guardian->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard has no PATROL POINTS!"));
		return EBTNodeResult::Failed;
	}
	//GetBlackboard Value as int
	int32 index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName); 
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolPoints[index]);

	//Cycle index
	index++;
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, index % PatrolPoints.Num());

	UE_LOG(LogTemp,Warning, TEXT("Waypoint Index: %i"), index);
	return EBTNodeResult::Succeeded;
}
