#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldBuildingVisibilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTWorldBuildingVisibilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCTWorldBuildingVisibilityComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool HasLineOfSight(FVector Start, FVector End);
};
