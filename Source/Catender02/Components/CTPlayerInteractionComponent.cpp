#include "CTPlayerInteractionComponent.h"

#include "Catender02/Objects/CTInteractable.h"

void UCTPlayerInteractionComponent::SortInteractablesBySortingLayer()
{
	OverlappingInteractables.Sort([](const ACTInteractable& A, const ACTInteractable& B) {
		return A.GetSprite()->TranslucencySortPriority < B.GetSprite()->TranslucencySortPriority;
	});
}

UCTPlayerInteractionComponent::UCTPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTPlayerInteractionComponent::AddToOverlappingInteractables(ACTInteractable* Interactable)
{	
	this->OverlappingInteractables.AddUnique(Interactable);
	SortInteractablesBySortingLayer();
	this->OnAddedInteractable.Broadcast(Interactable);
}

void UCTPlayerInteractionComponent::RemoveFromOverlappingInteractables(ACTInteractable* Interactable)
{
	this->OverlappingInteractables.Remove(Interactable);
	SortInteractablesBySortingLayer();
	this->OnRemovedInteractable.Broadcast();
}

ACTInteractable* UCTPlayerInteractionComponent::GetFrontInteractable()
{	
	return this->OverlappingInteractables.Num() > 0 ? this->OverlappingInteractables[0] : nullptr;
}

void UCTPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	SortInteractablesBySortingLayer();
}

void UCTPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

