
#include "CTWorldBuildingVisibilityComponent.h"

#include "Catender02/Objects/CTDestroyable.h"


UCTWorldBuildingVisibilityComponent::UCTWorldBuildingVisibilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCTWorldBuildingVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCTWorldBuildingVisibilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UCTWorldBuildingVisibilityComponent::HasLineOfSight(FVector Start, FVector End)
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
