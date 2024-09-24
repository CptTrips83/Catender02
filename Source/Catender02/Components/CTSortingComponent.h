#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTSortingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTSortingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTSortingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
