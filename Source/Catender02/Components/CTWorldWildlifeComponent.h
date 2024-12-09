
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldWildlifeComponent.generated.h"

class ACTWildlife;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FWildlifeChanged,
	TArray<TSoftObjectPtr<ACTWildlife>>, Wildlife
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTWorldWildlifeComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<ACTWildlife>> Wildlife;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxWildlife = 10;

	UFUNCTION()
	void SortWildlifeByNearest(ACTSortable* Sortable);
	
public:
	UCTWorldWildlifeComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Wildlife")
	virtual int GetMaxWildlife();

	UFUNCTION(BlueprintPure, Category = "Wildlife")
	virtual int GetNumWildlife();
	
	UFUNCTION(BlueprintCallable, Category = "Wildlife")
	virtual void AddWildlife(ACTWildlife* WildlifeToAdd);

	UFUNCTION(BlueprintCallable, Category = "Wildlife")
	virtual void RemoveWildlife(ACTWildlife* WildlifeToRemove);

	UPROPERTY(BlueprintAssignable, Category = "Wildlife")
	FWildlifeChanged OnWildlifeChanged;

	UFUNCTION(BlueprintCallable, Category = "Wildlife")
	TSoftObjectPtr<ACTWildlife> SpawnWildlife(TSubclassOf<ACTWildlife> WildlifeClass, FVector Location);

	UFUNCTION(BlueprintPure, Category = "Wildlife")
	TSoftObjectPtr<ACTWildlife> GetNearestWildlife(ACTSortable* Sortable);
};
