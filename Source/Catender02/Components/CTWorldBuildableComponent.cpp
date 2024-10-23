
#include "CTWorldBuildableComponent.h"

#include "Catender02/Objects/CTBuildable.h"
#include "Kismet/GameplayStatics.h"
#include "CTBuildingComponent.h"

ACTBuildable* UCTWorldBuildableComponent::GetNearestConstructionSite(ACTSortable* Sortable)
{	
	TArray<ACTBuildable*> Result;

	for(ACTBuildable* Buildable : this->Buildables)
	{
		if(Buildable->GetBuildingComponent()->GetBuildingState() == EBuildingState::Construction)
		{
			Result.Add(Buildable);
		}
	}

	if(Result.Num() > 0) return Result[0];
	return nullptr;
}

void UCTWorldBuildableComponent::SortBuildablesByNearest(ACTSortable* Sortable)
{
	Buildables.Sort([&Sortable] (const ACTBuildable& Buildable1, const ACTBuildable& Buildable2)
	{
		return Buildable1.GetDistanceTo(Sortable) < Buildable2.GetDistanceTo(Sortable);
	});
}

void UCTWorldBuildableComponent::SortBuildablesByNearestAndDirection(ACTSortable* Sortable,
                                                                    ECTDirection BuildableDirection)
{
	Buildables.Sort([&Sortable, BuildableDirection] (ACTBuildable& Buildable1, ACTBuildable& Buildable2)
	{
		const FVector Direction = Sortable->GetActorLocation() - Buildable2.GetActorLocation();
		const float DirectionX = Direction.X;

		bool CorrectDirection = false;
		switch (BuildableDirection)
		{
			case ECTDirection::Left:
				{
					if (DirectionX < 0.f) CorrectDirection = true;
					break;
				}
			case ECTDirection::Right:
				{
					if (DirectionX >= 0.f) CorrectDirection = true;
					break;
				}
		}
		
		return (Buildable1.GetDistanceTo(Sortable) < Buildable2.GetDistanceTo(Sortable)) && CorrectDirection;
	});
}

UCTWorldBuildableComponent::UCTWorldBuildableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWorldBuildableComponent::PopulateBuildables()
{
	Buildables.Empty();
	TArray<AActor*> OutActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACTBuildable::StaticClass(), OutActors);
	for (AActor* Actor : OutActors)
	{
		if (ACTBuildable* Buildable = Cast<ACTBuildable>(Actor))
		{
			Buildables.Add(Buildable);
		}
	}
}

void UCTWorldBuildableComponent::RemoveBuildable(ACTBuildable* Buildable)
{
	if (Buildable == nullptr) return;
	Buildables.Remove(Buildable);
}

ACTBuildable* UCTWorldBuildableComponent::GetNearestBuildable(ACTSortable* Sortable)
{
	ACTBuildable* NearestBuildable = nullptr;
	
	if (Buildables.Num() <= 0) return nullptr;

	const ACTFriendlyNPCCharacter* FriendlyNPCCharacter = Cast<ACTFriendlyNPCCharacter>(Sortable);

	if (FriendlyNPCCharacter == nullptr) return nullptr;

	SortBuildablesByNearest(Sortable);

	for(ACTBuildable* Buildable : Buildables)
	{
		if(Buildable->GetBuildingWorkSiteComponent()->HasActiveWorkSite(FriendlyNPCCharacter))
		{
			NearestBuildable = Buildable;
			break;
		}
	}
	
	return NearestBuildable;
}

ACTBuildable* UCTWorldBuildableComponent::GetNearestBuildableByDirection(ACTSortable* Sortable,
                                                                         const ECTDirection BuildableDirection)
{
	// TODO Work-Site Mechanic
	
	if (Buildables.Num() <= 0) return nullptr;

	SortBuildablesByNearestAndDirection(Sortable, BuildableDirection);
	
	return Buildables[0];
}

void UCTWorldBuildableComponent::BeginPlay()
{
	Super::BeginPlay();

	PopulateBuildables();
}


void UCTWorldBuildableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

