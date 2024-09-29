
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldBuildableComponent.generated.h"

UENUM(BlueprintType)
enum EBuildableDirection
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
	void SortBuildablesByNearestAndDirection(ACTSortable* Sortable, EBuildableDirection BuildableDirection);
	
public:	
	UCTWorldBuildableComponent();
	void PopulateBuildables();
	ACTBuildable* GetNearestBuildable(ACTSortable* Sortable);
	ACTBuildable* GetNearestBuildableByDirection(ACTSortable* Sortable, EBuildableDirection BuildableDirection);	
	ACTBuildable* GetNearestConstructionSite(ACTSortable* Sortable);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
