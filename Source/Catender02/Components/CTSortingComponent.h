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

public:	
	UCTSortingComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ESortingLayer SortingLayer = ESortingLayer::Background;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 9))
	int SortingIndex = 0;

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
		
	UPROPERTY(BlueprintAssignable)
	FSortingLayerChanged OnSortingLayerChanged;
	UPROPERTY(BlueprintAssignable)
	FSortingIndexChanged OnSortingIndexChanged;
};
