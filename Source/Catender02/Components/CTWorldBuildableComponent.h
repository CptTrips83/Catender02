
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldBuildableComponent.generated.h"

UENUM(BlueprintType)
enum ECTDirection
{
	Left,
	Right
};

class ACTSortable;
class ACTBuildable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<ACTBuildable*> Buildables;

	void SortBuildablesByNearest(ACTSortable* Sortable);
	void SortBuildablesByNearestAndDirection(ACTSortable* Sortable, ECTDirection BuildableDirection);
	
public:	
	UCTWorldBuildableComponent();
	void PopulateBuildables();
	void RemoveBuildable(ACTBuildable* Buildable);
	UFUNCTION(BlueprintPure)
	ACTBuildable* GetNearestBuildable(ACTSortable* Sortable);
	UFUNCTION(BlueprintPure)
	ACTBuildable* GetNearestBuildableByDirection(ACTSortable* Sortable, ECTDirection BuildableDirection);
	UFUNCTION(BlueprintPure)
	ACTBuildable* GetNearestConstructionSite(ACTSortable* Sortable);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
