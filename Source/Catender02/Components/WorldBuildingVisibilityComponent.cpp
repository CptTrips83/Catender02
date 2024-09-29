
#include "WorldBuildingVisibilityComponent.h"

#include "Catender02/Objects/CTDestroyable.h"


UWorldBuildingVisibilityComponent::UWorldBuildingVisibilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWorldBuildingVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UWorldBuildingVisibilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UWorldBuildingVisibilityComponent::HasLineOfSight(FVector Start, FVector End)
{
	TArray<FHitResult> Hit;
	GetWorld()->LineTraceMultiByProfile(Hit, Start, End, "Buildable");

	for (FHitResult HitResult : Hit)
	{
		if (!HitResult.GetActor()) continue;

		if (Cast<ACTDestroyable>(HitResult.GetActor())) return false;
	}

	return true;
}
