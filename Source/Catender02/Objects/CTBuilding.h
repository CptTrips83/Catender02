#pragma once

#include "CoreMinimal.h"
#include "CTBuildable.h"
#include "CTBuilding.generated.h"

UCLASS()
class CATENDER02_API ACTBuilding : public ACTBuildable
{
	GENERATED_BODY()

public:
	ACTBuilding();

protected:
	virtual void BeginPlay() override;
	
	virtual bool HasLineOfSightToHQ();
	virtual void UpdateInteractionCollision();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
