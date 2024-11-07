#include "CTSortingLayerDataComponent.h"

UCTSortingLayerDataComponent::UCTSortingLayerDataComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}


void UCTSortingLayerDataComponent::UpdateSortingLayers()
{
	int CurrentLayer = this->SortingLayerStart;

	for ( ESortingLayer e : TEnumRange<ESortingLayer>())
	{
		this->SortingLayers.Add(e, CurrentLayer);

		CurrentLayer += this->SortingLayerWidth;
	}
}

void UCTSortingLayerDataComponent::BeginPlay()
{	
	UpdateSortingLayers();
	
	Super::BeginPlay();

}


void UCTSortingLayerDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UCTSortingLayerDataComponent::GetSortingLayerIndex(ESortingLayer SortingLayer)
{
	const int* Result = this->SortingLayers.Find(SortingLayer);

	return Result != nullptr ? *Result : this->SortingLayerStart;
}

