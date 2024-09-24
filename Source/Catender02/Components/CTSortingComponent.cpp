#include "CTSortingComponent.h"

#include "Catender02/CTSortable.h"

UCTSortingComponent::UCTSortingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTSortingComponent::BeginPlay()
{
	Super::BeginPlay();

    Owner = static_cast<ACTSortable*>(GetOwner());
	GameModeLevel = static_cast<ACTGameModeLevel*>(GetWorld()->GetAuthGameMode());

	SetSpriteLayerIndex();
}

void UCTSortingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/**
 * Sets the sorting layer index of the sprite component owned by this component.
 *
 * This function retrieves the sprite component from the owner actor and calculates its
 * translucent sort priority based on the current sorting layer and sorting index.
 * It then sets this priority to the sprite component to control its rendering order.
 *
 * @note The actual sorting index is a sum of the sorting layer index and an additional sorting index.
 */
void UCTSortingComponent::SetSpriteLayerIndex()
{
	UPaperFlipbookComponent* FlipbookComponent = Owner->GetSprite();

	int Index = GameModeLevel->SortingLayerDataComponent->GetSortingLayerIndex(SortingLayer);

	Index += SortingIndex;
	
	FlipbookComponent->SetTranslucentSortPriority(Index);
}

/**
 * Sets the sorting layer of the component and updates the sprite's sorting index accordingly.
 *
 * This function updates the existing sorting layer to the new specified layer, recalculates
 * the sorting index for the sprite component, and broadcasts an event informing about the
 * change in sorting layer.
 *
 * @param NewSortingLayer The new sorting layer to be set for this component.
 */
void UCTSortingComponent::SetSortingLayer(const ESortingLayer NewSortingLayer)
{
	const ESortingLayer OldSortingLayer = SortingLayer;
	SortingLayer = NewSortingLayer;

	SetSpriteLayerIndex();
	
	OnSortingLayerChanged.Broadcast(OldSortingLayer, NewSortingLayer);
}

/**
 * Sets the sorting index within the current sorting layer.
 *
 * This function modifies the sorting index of the object to control its rendering order.
 * It clamps the new sorting index value to ensure it stays within the valid range (0 to 9),
 * updates the sprite layer index, and then broadcasts the change in sorting index.
 *
 * @param NewSortingIndex The new sorting index to be set, must be within the range of 0 to 9.
 */
void UCTSortingComponent::SetSortingIndex(int NewSortingIndex)
{
	int OldSortingLayer = SortingIndex;
	SortingIndex = FMath::Clamp(NewSortingIndex, 0, 9);
	
	SetSpriteLayerIndex();
	
	OnSortingIndexChanged.Broadcast(NewSortingIndex, OldSortingLayer);
}

