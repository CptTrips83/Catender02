

#include "CTWorldWildlifeComponent.h"


#include "Catender02/Objects/CTWildlife.h"

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

