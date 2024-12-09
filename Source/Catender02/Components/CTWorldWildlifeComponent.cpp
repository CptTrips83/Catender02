

#include "CTWorldWildlifeComponent.h"


#include "Catender02/Objects/CTWildlife.h"

void UCTWorldWildlifeComponent::SortWildlifeByNearest(ACTSortable* Sortable)
{
	Wildlife.Sort([&Sortable](const TSoftObjectPtr<ACTWildlife>& A, const TSoftObjectPtr<ACTWildlife>& B)
	{
		return A->GetDistanceTo(Sortable) < B->GetDistanceTo(Sortable);
	});
}

UCTWorldWildlifeComponent::UCTWorldWildlifeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWorldWildlifeComponent::BeginPlay()
{
	Super::BeginPlay();	
}


void UCTWorldWildlifeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UCTWorldWildlifeComponent::GetMaxWildlife()
{
	return MaxWildlife;
}

int UCTWorldWildlifeComponent::GetNumWildlife()
{
	return Wildlife.Num();
}

void UCTWorldWildlifeComponent::AddWildlife(ACTWildlife* WildlifeToAdd)
{
	Wildlife.Add(WildlifeToAdd);
	OnWildlifeChanged.Broadcast(Wildlife);
}

void UCTWorldWildlifeComponent::RemoveWildlife(ACTWildlife* WildlifeToRemove)
{
	Wildlife.Remove(WildlifeToRemove);
	OnWildlifeChanged.Broadcast(Wildlife);
}

TSoftObjectPtr<ACTWildlife> UCTWorldWildlifeComponent::SpawnWildlife(TSubclassOf<ACTWildlife> WildlifeClass,
	FVector Location)
{
	if (GetNumWildlife() >= MaxWildlife) return nullptr;
	
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    ACTWildlife* SpawnedWildlife =	GetWorld()->SpawnActor<ACTWildlife>(WildlifeClass, Location, Rotation, SpawnInfo);

	return TSoftObjectPtr<ACTWildlife>(SpawnedWildlife);
}

TSoftObjectPtr<ACTWildlife> UCTWorldWildlifeComponent::GetNearestWildlife(ACTSortable* Sortable)
{
	if (Wildlife.Num() == 0) return nullptr;

	SortWildlifeByNearest(Sortable);

	return Wildlife[0];
}

