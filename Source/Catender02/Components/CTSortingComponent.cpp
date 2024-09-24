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

void UCTSortingComponent::SetSpriteLayerIndex()
{
	UPaperFlipbookComponent* FlipbookComponent = Owner->GetSprite();

	int Index = GameModeLevel->SortingLayerDataComponent->GetSortingLayerIndex(SortingLayer);

	Index += SortingIndex;
	
	FlipbookComponent->SetTranslucentSortPriority(Index);
}

void UCTSortingComponent::SetSortingLayer(const ESortingLayer NewSortingLayer)
{
	const ESortingLayer OldSortingLayer = SortingLayer;
	SortingLayer = NewSortingLayer;

	SetSpriteLayerIndex();
	
	OnSortingLayerChanged.Broadcast(OldSortingLayer, NewSortingLayer);
}

void UCTSortingComponent::SetSortingIndex(int NewSortingIndex)
{
	int OldSortingLayer = SortingIndex;
	SortingIndex = NewSortingIndex;

	SetSpriteLayerIndex();
	
	OnSortingIndexChanged.Broadcast(NewSortingIndex, OldSortingLayer);
}

