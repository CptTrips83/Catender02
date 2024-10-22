#pragma once

#include "CoreMinimal.h"
#include "CTSortingLayerDataComponent.h"
#include "Components/ActorComponent.h"
#include "PaperFlipbookComponent.h"
#include "CTSortingComponent.generated.h"


class ACTGameModeLevel;
class ACTSortable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams
(
	FSortingLayerChanged,
	ESortingLayer, OldSortingLayer,
	ESortingLayer, NewSortingLayer
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams
(
	FSortingIndexChanged,
	int, OldSortingIndex,
	int, NewSortingIndex
);

/**
 * Custom component that manages the sorting layer and index of an actor for rendering purposes.
 * It allows for precise control over the order in which sprites are drawn within the game world.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTSortingComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * The sorting layer of the component.
	 * It determines the draw order of the component within the game world.
	 * Editable in the editor and can be read and written through blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true, Category="Sorting"))
	ESortingLayer SortingLayer = ESortingLayer::Background;

	/**
	 * The sorting index of the component.
	 * It determines the relative draw order within the specified sorting layer.
	 * Editable in the editor and can be read and written through blueprints.
	 * The value is clamped between a minimum of 0 and a maximum of 9.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 9, AllowPrivateAccess = true, Category="Sorting"))
	int SortingIndex = 0;

public:	
	UCTSortingComponent();


protected:
	ACTSortable* Owner = nullptr;
	ACTGameModeLevel* GameModeLevel = nullptr;
	
	virtual void BeginPlay() override;

	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Updates the sprite's layer index based on the current sorting layer and sorting index.
	 * Retrieves the appropriate sorting layer index from the game mode's sorting layer data component,
	 * adjusts it by the component's sorting index, and applies the resulting priority to the sprite's
	 * translucent sort priority.
	 */
	virtual void SetSpriteLayerIndex();

	/**
	 * Sets the sorting layer of the component.
	 * This determines the draw order of the component within the game world.
	 * It updates the sprite's layer index based on the new sorting layer and triggers the OnSortingLayerChanged delegate.
	 * @param NewSortingLayer The new sorting layer to be assigned to the component.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetSortingLayer(ESortingLayer NewSortingLayer);
	/**
	 * Sets the sorting index of the component.
	 * This determines the relative draw order within the assigned sorting layer.
	 * The value is clamped between a minimum of 0 and a maximum of 9.
	 * It updates the sprite's layer index based on the new sorting index and
	 * triggers the OnSortingIndexChanged delegate.
	 * @param NewSortingIndex The new sorting index to be assigned to the component.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetSortingIndex(int NewSortingIndex);

	/**
	 * This delegate is broadcast whenever the sorting layer of a component changes.
	 * It allows subscribers to respond to changes in the actor's sorting layer.
	 *
	 * Signature: void OnSortingLayerChanged(ESortingLayer OldSortingLayer, ESortingLayer NewSortingLayer)
	 */
	UPROPERTY(BlueprintAssignable)
	FSortingLayerChanged OnSortingLayerChanged;
	/**
	 * This delegate is broadcast whenever the sorting index of a component changes.
	 * It allows subscribers to respond to changes in the actor's sorting index.
	 *
	 * Signature: void OnSortingIndexChanged(int NewSortingIndex, int OldSortingIndex)
	 */
	UPROPERTY(BlueprintAssignable)
	FSortingIndexChanged OnSortingIndexChanged;
};
