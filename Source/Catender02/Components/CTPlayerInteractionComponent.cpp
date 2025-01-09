#include "CTPlayerInteractionComponent.h"

#include "Catender02/Objects/CTInteractable.h"
#include "Kismet/KismetSystemLibrary.h"

void UCTPlayerInteractionComponent::SortInteractablesBySortingLayer()
{
	OverlappingInteractables.Sort([](const ACTInteractable& A, const ACTInteractable& B) {
		return A.GetSprite()->TranslucencySortPriority > B.GetSprite()->TranslucencySortPriority && A.CanInteract();
	});
}

void UCTPlayerInteractionComponent::RefreshInteractables()
{
	for(ACTInteractable* Interactable : OverlappingInteractables)
	{
		Interactable->Highlight(false);
		Interactable->SetVisibilityInteractionWidget(false);
	}

	ACTInteractable* FrontInteractable = GetFrontInteractable();
	if(!FrontInteractable) return;
	
	if (FrontInteractable->CanInteract())
	{
		FrontInteractable->Highlight(true);
		FrontInteractable->SetVisibilityInteractionWidget(true);
	}
}

UCTPlayerInteractionComponent::UCTPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OnAddedInteractable.AddDynamic(this, &UCTPlayerInteractionComponent::AddedInteractable);
	OnRemovedInteractable.AddDynamic(this, &UCTPlayerInteractionComponent::RemovedInteractable);
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
	this->OnRemovedInteractable.Broadcast(Interactable);
}

ACTInteractable* UCTPlayerInteractionComponent::GetFrontInteractable()
{	
	return this->OverlappingInteractables.Num() > 0 ? this->OverlappingInteractables[0] : nullptr;	
}

void UCTPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCTPlayerInteractionComponent::AddedInteractable(ACTInteractable* Interactable)
{
	RefreshInteractables();
}

void UCTPlayerInteractionComponent::RemovedInteractable(ACTInteractable* Interactable)
{
	Interactable->Highlight(false);
	Interactable->SetVisibilityInteractionWidget(false);
	RefreshInteractables();
}

void UCTPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

