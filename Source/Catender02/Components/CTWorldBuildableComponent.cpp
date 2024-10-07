
#include "CTWorldBuildableComponent.h"

#include "Catender02/Objects/CTBuildable.h"
#include "Kismet/GameplayStatics.h"
#include "CTBuildingComponent.h"

/**
 * Sorts the Buildables array by the nearest distance to the given Sortable actor .
 *
 * @param Sortable Pointer to the actor used as the reference point for sorting the buildables by distance.
 */
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

/**
 * Sorts the Buildables array by the nearest distance to the given Sortable actor.
 *
 * @param Sortable Pointer to the actor used as the reference point for sorting the buildables by distance.
 */
void UCTWorldBuildableComponent::SortBuildablesByNearest(ACTSortable* Sortable)
{
	Buildables.Sort([&Sortable] (const ACTBuildable& Buildable1, const ACTBuildable& Buildable2)
	{
		return Buildable1.GetDistanceTo(Sortable) < Buildable2.GetDistanceTo(Sortable);
	});
}

/**
 * Sorts the Buildables array by distance to the given Sortable actor, considering only buildables that match the specified direction.
 *
 * @param Sortable Pointer to the actor used as the reference point for sorting the buildables by distance.
 * @param BuildableDirection Enum specifying the direction (Left or Right) in which buildables should be considered for sorting.
 */
void UCTWorldBuildableComponent::SortBuildablesByNearestAndDirection(ACTSortable* Sortable,
                                                                    EBuildableDirection BuildableDirection)
{
	Buildables.Sort([&Sortable, BuildableDirection] (ACTBuildable& Buildable1, ACTBuildable& Buildable2)
	{
		const FVector Direction = Sortable->GetActorLocation() - Buildable2.GetActorLocation();
		const float DirectionX = Direction.X;

		bool CorrectDirection = false;
		switch (BuildableDirection)
		{
			case EBuildableDirection::Left:
				{
					if (DirectionX < 0.f) CorrectDirection = true;
					break;
				}
			case EBuildableDirection::Right:
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

/**
 * Populates the Buildables array with all instances of ACTBuildable actors present in the world.
 *
 * Clears the current list of buildable objects and retrieves all actors of class ACTBuildable in the current world.
 * It then casts the retrieved actors to ACTBuildable and adds them to the Buildables array.
 */
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

/**
 * Removes the specified buildable from the Buildables array if it is not null.
 *
 * @param Buildable Pointer to the buildable actor to be removed from the Buildables array.
 */
void UCTWorldBuildableComponent::RemoveBuildable(ACTBuildable* Buildable)
{
	if (Buildable == nullptr) return;
	Buildables.Remove(Buildable);
}

/**
 * Retrieves the nearest buildable object relative to the specified sortable actor.
 *
 * @param Sortable Pointer to the actor used as the reference point for finding the nearest buildable.
 * @return Pointer to the nearest buildable object, or nullptr if there are no buildables.
 */
ACTBuildable* UCTWorldBuildableComponent::GetNearestBuildable(ACTSortable* Sortable)
{
	if (Buildables.Num() <= 0) return nullptr;

	SortBuildablesByNearest(Sortable);
	
	return Buildables[0];
}

/**
 * Returns the nearest buildable to the given sortable actor,
 * further filtered by the specified direction.
 *
 * @param Sortable Pointer to the actor used as the reference point for determining the nearest buildable.
 * @param BuildableDirection The direction criteria used to filter the buildables.
 * @return Pointer to the nearest buildable that satisfies the given direction, or nullptr if no buildables are available.
 */
ACTBuildable* UCTWorldBuildableComponent::GetNearestBuildableByDirection(ACTSortable* Sortable,
                                                                         const EBuildableDirection BuildableDirection)
{
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

