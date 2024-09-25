
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTWorldResourceComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
