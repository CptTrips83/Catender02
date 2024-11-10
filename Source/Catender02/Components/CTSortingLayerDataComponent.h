#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTSortingLayerDataComponent.generated.h"

/**
 * ESortingLayer is an enumeration used to define various sorting layers in a game environment.
 * These layers facilitate the rendering order of game objects, enabling finer control over what appears in front of or behind other objects.
 * This enumeration supports a wide range of layer types, including background, foreground, and character layers.
 */
UENUM(BlueprintType)
enum class ESortingLayer : uint8
{
	Background,
	BuildingBackground,
	DestroyableBackground,
	InteractableBackground,
	DecorationBackground,
	Pickup,
	FriendlyNPC,
	Enemy,
	Player,
	BuildingForeground,
	InteractableForeground,
	DestroyableForeground,
	DecorationForeground,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ESortingLayer, ESortingLayer::Count);

/**
 * UCTSortingLayerDataComponent is a custom actor component class designed to manage the sorting layers for different game objects.
 * This component tracks sorting layers, calculates their indices based on predefined settings,
 * and provides functionalities to update and retrieve sorting layer indices.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTSortingLayerDataComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * Updates the sorting layers for the game objects managed by this component.
	 * Iterates through all enumerated sorting layers, assigning and storing their respective indices based on the
	 * starting layer and layer width properties.
	 * This method ensures that each sorting layer is assigned a unique index which can later be used for rendering order and other logic that depends on layer-specific settings.
	 */
	UFUNCTION()
	void UpdateSortingLayers();

	/**
	 * SortingLayerWidth determines the width of each sorting layer in the game.
	 * It is used to calculate the indices of different sorting layers, ensuring that
	 * each layer occupies a distinct range based on its width and starting point.
	 */
	UPROPERTY()
	int SortingLayerWidth = 10;
	/**
	 * SortingLayerStart represents the initial sorting layer index from which the calculation of further layers begins.
	 * This value is used as the starting point in algorithms that assign and manage sorting layer indices
	 * for various game objects. Modifying this value impacts the base index from which all subsequent
	 * sorting layer indices are derived.
	 */
	UPROPERTY()
	int SortingLayerStart = 0;
	
public:	
	UCTSortingLayerDataComponent();	

protected:
	/**
	 * SortingLayers is a mapping between different sorting layers and their corresponding indices.
	 * This TMap structure allows for efficient lookup and management of sorting layers,
	 * enabling the retrieval of unique indices assigned to each enumerated sorting layer.
	 */
	UPROPERTY()
	TMap<ESortingLayer, int> SortingLayers;
	
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Retrieves the sorting layer index for the specified sorting layer.
	 * This function looks up the given sorting layer in the internal map of sorting layers,
	 * returning its corresponding index if found. If the sorting layer is not found,
	 * it returns the starting index defined in the component.
	 *
	 * @param SortingLayer The sorting layer enum value for which the index is requested.
	 * @return The index associated with the provided sorting layer, or the starting index if the layer is not found.
	 */
	UFUNCTION(BlueprintCallable)
	int GetSortingLayerIndex(ESortingLayer SortingLayer);
	
};
