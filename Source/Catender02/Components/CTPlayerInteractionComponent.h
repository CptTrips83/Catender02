#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTPlayerInteractionComponent.generated.h"


class ACTInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FAddedInteractable,
	ACTInteractable*, Interactable
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FRemoveInteractable,
	ACTInteractable*, Interactable
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<ACTInteractable*> OverlappingInteractables;

	/**
	 * Sorts the list of overlapping interactables by their translucency sort priority, in descending order.
	 * Only interactables that can be interacted with are considered in the sorting process.
	 */
	void SortInteractablesBySortingLayer();

	/**
	 * Refreshes the list of interactables by resetting their highlight state and interaction widget visibility.
	 * For the interactable at the front, it will highlight and enable its interaction widget if it can be interacted with.
	 */
	void RefreshInteractables();
	
public:	
	UCTPlayerInteractionComponent();

	/**
	 * Adds an interactable item to the list of currently overlapping interactables.
	 * This method also sorts the list of interactables by their translucency sort priority
	 * and triggers the OnAddedInteractable event.
	 *
	 * @param Interactable The interactable item to be added to the overlapping list.
	 */
	UFUNCTION(BlueprintCallable)
	void AddToOverlappingInteractables(ACTInteractable* Interactable);
	/**
	 * Removes an interactable item from the list of currently overlapping interactables.
	 * This method also sorts the list of remaining interactables by their translucency sort priority
	 * and triggers the OnRemovedInteractable event.
	 *
	 * @param Interactable The interactable item to be removed from the overlapping list.
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveFromOverlappingInteractables(ACTInteractable* Interactable);
	/**
	 * Gets the interactable object that is currently at the front of the interaction list.
	 * The front interactable is the first item in the list of overlapping interactables.
	 *
	 * @return The front interactable if available, otherwise returns nullptr.
	 */
	UFUNCTION(BlueprintCallable)
	ACTInteractable* GetFrontInteractable();	
	
protected:
	virtual void BeginPlay() override;

	/**
	 * Handles the logic when a new interactable is added to the interaction component.
	 * This method refreshes the list of interactables to ensure it is updated.
	 *
	 * @param Interactable The interactable item that is added to the component.
	 */
	UFUNCTION()
	void AddedInteractable(ACTInteractable* Interactable);
	/**
	 * Handles the logic when an interactable is removed from the interaction component.
	 * This method disables the highlight and visibility of the interaction widget for the removed interactable
	 * and refreshes the list of interactables to ensure it is updated.
	 *
	 * @param Interactable The interactable item that is removed from the component.
	 */
	UFUNCTION()
	void RemovedInteractable(ACTInteractable* Interactable);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Delegate for handling events when an interactable item is added to the player's interaction component.
	 */
	UPROPERTY(BlueprintAssignable)
	FAddedInteractable OnAddedInteractable;
	/**
	 * Delegate for handling events when an interactable item is removed from the player's interaction component.
	 */
	UPROPERTY(BlueprintAssignable)
	FRemoveInteractable OnRemovedInteractable;
};
