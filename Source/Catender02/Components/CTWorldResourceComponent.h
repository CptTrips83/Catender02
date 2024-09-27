
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldResourceComponent.generated.h"

UENUM(BlueprintType)
enum EResourceType
{
	Gold,
	Meat,
	Wood,
	Stone,
	Iron
};

USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<EResourceType> ResourceType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	int Amount = 0;	
};

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FResource Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUnlockResource = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FResourceAmountChanged,
	EResourceType, Resource,
	int, OldAmount,
	int, NewAmount	
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTWorldResourceComponent();

protected:
	virtual void BeginPlay() override;

	FResourceData* GetResourceData(const EResourceType ResourceType);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxResources = 30;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceData> Resources;

	/**
	 * Delegate called when the amount of a resource changes.
	 * It broadcasts information about the resource type, old amount, and new amount.
	 *
	 * Usage scenarios:
	 * - When resource amounts are adjusted by adding or subtracting.
	 * - For UI or other gameplay elements to update based on resource changes.
	 */
	UPROPERTY(BlueprintAssignable)
	FResourceAmountChanged OnResourceAmountChanged;
	
	UFUNCTION(BlueprintPure)
	int GetResourceAmount(const EResourceType ResourceType);
	UFUNCTION(BlueprintCallable)
	int TryAddResourceAmount(const EResourceType ResourceType, int Amount);
	UFUNCTION(BlueprintCallable)
	bool TrySubtractResourceAmount(const EResourceType ResourceType, int Amount);
	UFUNCTION(BlueprintPure)
	bool IsUnlockResource(const EResourceType ResourceType);
	UFUNCTION(BlueprintPure)
	int GetAmountAllResources();
	UFUNCTION(BlueprintPure)
	int GetMaxResources() const;
};
