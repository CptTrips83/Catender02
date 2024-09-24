#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTSortingLayerDataComponent.generated.h"

UENUM(BlueprintType)
enum class ESortingLayer : uint8
{
	Background,
	Building,
	InteractableBackground,
	Pickup,
	FriendlyNPC,
	Enemy,
	Player,
	InteractableForeground,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(ESortingLayer, ESortingLayer::Count);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTSortingLayerDataComponent : public UActorComponent
{
	GENERATED_BODY()
	
	void UpdateSortingLayers();
	
public:	
	UCTSortingLayerDataComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SortingLayerWidth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SortingLayerStart = -50;
	

protected:	
	TMap<ESortingLayer, int> SortingLayers;
	
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	int GetSortingLayerIndex(ESortingLayer SortingLayer);
	
};
