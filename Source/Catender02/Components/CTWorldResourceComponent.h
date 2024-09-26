
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 20))
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

	UFUNCTION(BlueprintCallable)
	int GetResourceAmount(const EResourceType ResourceType);
	UFUNCTION(BlueprintCallable)
	int TryAddResourceAmount(const EResourceType ResourceType, int Amount);
	UFUNCTION(BlueprintCallable)
	bool TrySubtractResourceAmount(const EResourceType ResourceType, int Amount);
	UFUNCTION(BlueprintCallable)
	bool IsUnlockResource(const EResourceType ResourceType);
	UFUNCTION(BlueprintCallable)
	int GetAmountAllResources();
	UFUNCTION(BlueprintCallable)
	int GetMaxResources();
};
