
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldInteractableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTWorldInteractableComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
