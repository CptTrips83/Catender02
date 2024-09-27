
#include "CTWorldBuildableComponent.h"

UCTWorldBuildableComponent::UCTWorldBuildableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWorldBuildableComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCTWorldBuildableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

