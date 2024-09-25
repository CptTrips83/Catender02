
#include "CTWorldInteractableComponent.h"

UCTWorldInteractableComponent::UCTWorldInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWorldInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCTWorldInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

