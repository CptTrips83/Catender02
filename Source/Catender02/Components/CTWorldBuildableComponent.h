
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldBuildableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTWorldBuildableComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
