
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

