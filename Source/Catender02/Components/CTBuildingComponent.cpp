
#include "CTBuildingComponent.h"

#include "Catender02/Objects/CTBuildable.h"

UCTBuildingComponent::UCTBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

int UCTBuildingComponent::GetMaxBuildingLevel()
{
	return BuildingLevelInformation.Num();
}

int UCTBuildingComponent::GetCurrentBuildingLevel()
{
	return CurrentLevel;
}

EBuildingState UCTBuildingComponent::GetBuildingState()
{
	return BuildingState;
}

void UCTBuildingComponent::SetCurrentBuildingLevel(int NewLevel)
{
}

void UCTBuildingComponent::UpdateSprite()
{
}

bool UCTBuildingComponent::HasLevel()
{
	return BuildingLevelInformation.Num() > 0;
}

void UCTBuildingComponent::AddProgressToBuilding(float Amount)
{
}

float UCTBuildingComponent::GetProgressNeededForCurrentBuildingLevel()
{
	return 0.0f;
}

void UCTBuildingComponent::UpdateCollision(EBuildingState NewBuildingState)
{
}

bool UCTBuildingComponent::PayResources()
{
	return false;
}

bool UCTBuildingComponent::CheckResourceRequirements()
{
	return false;
}

FBuildingLevelInformation UCTBuildingComponent::GetBuildingLevelInformation(int Level)
{
	return BuildingLevelInformation[Level];
}

void UCTBuildingComponent::SetBuildingState(EBuildingState NewBuildingState)
{
}

void UCTBuildingComponent::ConstructionFinished(ACTBuildable* Buildable)
{
}

void UCTBuildingComponent::ConstructionProgressChanged(ACTBuildable* Buildable, float OldProgress, float NewProgress)
{
}

void UCTBuildingComponent::ConstructionFailed(ACTBuildable* Buildable, TArray<FResource> NeededResources)
{
}

void UCTBuildingComponent::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldBuildingState,
	EBuildingState NewBuildingState)
{
}

void UCTBuildingComponent::CurrentLevelChanged(ACTBuildable* Buildable, int OldLevel, int NewLevel)
{
}

void UCTBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningBuildable = Cast<ACTBuildable>(GetOwner());

	OnBuildingStateChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::BuildingStateChanged
	);
	OnCurrentLevelChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::CurrentLevelChanged
	);
	OnConstructionProgressChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionProgressChanged
	);
	OnConstructionFinished.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionFinished
	);
	OnConstructionFailed.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionFailed
	);
}

void UCTBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

