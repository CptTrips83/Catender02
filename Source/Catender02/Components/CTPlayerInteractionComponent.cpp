#include "CTPlayerInteractionComponent.h"

#include "Catender02/Objects/CTInteractable.h"

/**
 * Sorts the interactable objects in the `OverlappingInteractables` array
 * based on their translucency sort priority, in descending order.
 *
 * This function uses a lambda comparator to compare the `TranslucencySortPriority`
 * property of the sprites associated with the `ACTInteractable` objects.
 *
 * It ensures that interactables with higher translucency sort priority
 * appear before those with lower priority.
 */
void UCTPlayerInteractionComponent::SortInteractablesBySortingLayer()
{
	OverlappingInteractables.Sort([](const ACTInteractable& A, const ACTInteractable& B) {
		return A.GetSprite()->TranslucencySortPriority > B.GetSprite()->TranslucencySortPriority;
	});
}

UCTPlayerInteractionComponent::UCTPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * Adds an interactable object to the `OverlappingInteractables` array,
 * ensuring it is added uniquely. The array is then sorted by the
 * translucency sort priority of the interactables in descending order.
 * Finally, the `OnAddedInteractable` event is broadcast with the added interactable.
 *
 * @param Interactable The interactable object to be added to the array.
 */
void UCTPlayerInteractionComponent::AddToOverlappingInteractables(ACTInteractable* Interactable)
{	
	this->OverlappingInteractables.AddUnique(Interactable);
	SortInteractablesBySortingLayer();
	this->OnAddedInteractable.Broadcast(Interactable);
}

/**
 * Removes the specified interactable from the `OverlappingInteractables` array.
 *
 * This function also sorts the remaining interactables by their translucency sort priority
 * and broadcasts an event indicating that an interactable has been removed.
 *
 * @param Interactable The interactable object to remove from the overlapping interactables list.
 */
void UCTPlayerInteractionComponent::RemoveFromOverlappingInteractables(ACTInteractable* Interactable)
{
	this->OverlappingInteractables.Remove(Interactable);
	SortInteractablesBySortingLayer();
	this->OnRemovedInteractable.Broadcast();
}

/**
 * Retrieves the interactable object that is at the front of the `OverlappingInteractables` array.
 *
 * @return A pointer to the front `ACTInteractable` object if the array is not empty; otherwise, returns nullptr.
 */
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

