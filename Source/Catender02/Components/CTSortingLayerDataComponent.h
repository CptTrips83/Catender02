#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTSortingLayerDataComponent.generated.h"

UENUM(BlueprintType)
enum class ESortingLayer : uint8
{
	Background,
	BuildingBackground,
	DestroyableBackground,
	InteractableBackground,
	Pickup,
	FriendlyNPC,
	Enemy,
	Player,
	BuildingForeground,
	InteractableForeground,
	DestroyableForeground,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ESortingLayer, ESortingLayer::Count);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTSortingLayerDataComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UFUNCTION()
	void UpdateSortingLayers();

	UPROPERTY()
	int SortingLayerWidth = 10;
	UPROPERTY()
	int SortingLayerStart = 0;
	
public:	
	UCTSortingLayerDataComponent();	

protected:
	UPROPERTY()
	TMap<ESortingLayer, int> SortingLayers;
	
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	int GetSortingLayerIndex(ESortingLayer SortingLayer);
	
};
