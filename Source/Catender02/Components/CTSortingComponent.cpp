#include "CTSortingComponent.h"

UCTSortingComponent::UCTSortingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTSortingComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UCTSortingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

