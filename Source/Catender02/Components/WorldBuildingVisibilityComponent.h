
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldBuildingVisibilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UWorldBuildingVisibilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWorldBuildingVisibilityComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool HasLineOfSight(FVector Start, FVector End);
};
