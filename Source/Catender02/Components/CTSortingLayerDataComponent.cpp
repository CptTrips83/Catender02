#include "CTSortingLayerDataComponent.h"

UCTSortingLayerDataComponent::UCTSortingLayerDataComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}


/**
 * @brief Updates the sorting layers of an actor component.
 *
 * This method initializes the sorting layers starting from the value specified
 * by `SortingLayerStart` and increments by `SortingLayerWidth` for each subsequent
 * sorting layer in the enum `ESortingLayer`. The resulting mapping is stored in the
 * `SortingLayers` map, associating each `ESortingLayer` value with its corresponding
 * layer index.
 */
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

/**
 * @brief Retrieves the sorting layer index for the specified sorting layer.
 *
 * This method looks up the index associated with the provided `SortingLayer` in the
 * `SortingLayers` map. If the `SortingLayer` is not found, the method returns the default
 * starting sorting layer index.
 *
 * @param SortingLayer The sorting layer for which to retrieve the index.
 * @return The index associated with the specified sorting layer, or the default starting
 * sorting layer index if the sorting layer is not found.
 */
int UCTSortingLayerDataComponent::GetSortingLayerIndex(ESortingLayer SortingLayer)
{
	const int* Result = this->SortingLayers.Find(SortingLayer);

	return Result != nullptr ? *Result : this->SortingLayerStart;
}

