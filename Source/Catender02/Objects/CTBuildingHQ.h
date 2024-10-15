
#pragma once

#include "CoreMinimal.h"
#include "CTBuilding.h"
#include "CTBuildingHQ.generated.h"

UCLASS()
class CATENDER02_API ACTBuildingHQ : public ACTBuilding
{
	GENERATED_BODY()

public:
	ACTBuildingHQ();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
