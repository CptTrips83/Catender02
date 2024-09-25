
#include "CTWorldResourceComponent.h"

UCTWorldResourceComponent::UCTWorldResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCTWorldResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCTWorldResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

