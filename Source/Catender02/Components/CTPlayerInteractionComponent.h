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

DECLARE_DYNAMIC_MULTICAST_DELEGATE
(
	FRemoveInteractable
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<ACTInteractable*> OverlappingInteractables;	

	void SortInteractablesBySortingLayer();
	
public:	
	UCTPlayerInteractionComponent();

	UFUNCTION(BlueprintCallable)
	void AddToOverlappingInteractables(ACTInteractable* Interactable);
	UFUNCTION(BlueprintCallable)
	void RemoveFromOverlappingInteractables(ACTInteractable* Interactable);
	UFUNCTION(BlueprintCallable)
	ACTInteractable* GetFrontInteractable();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FAddedInteractable OnAddedInteractable;
	UPROPERTY(BlueprintAssignable)
	FRemoveInteractable OnRemovedInteractable;
};
