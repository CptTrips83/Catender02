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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTSortingComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true, Category="Sorting"))
	ESortingLayer SortingLayer = ESortingLayer::Background;

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

	virtual void SetSpriteLayerIndex();

	UFUNCTION(BlueprintCallable)
	virtual void SetSortingLayer(ESortingLayer NewSortingLayer);
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
