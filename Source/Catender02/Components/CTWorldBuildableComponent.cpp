
#include "CTWorldBuildableComponent.h"

#include "Catender02/Objects/CTBuildable.h"
#include "Kismet/GameplayStatics.h"

/**
 * Sorts the Buildables array by the nearest distance to the given Sortable actor.
 *
 * @param Sortable Pointer to the actor used as the reference point for sorting the buildables by distance.
 */
void UCTWorldBuildableComponent::SortBuildablesByNearest(ACTSortable* Sortable)
{
	Buildables.Sort([&Sortable] (ACTBuildable& Buildable1, ACTBuildable& Buildable2)
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

void UCTWorldBuildableComponent::PopulateBuildables()
{
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

