
#pragma once

#include "CoreMinimal.h"
#include "CTBuildable.h"
#include "CTDestroyable.generated.h"

UCLASS()
class CATENDER02_API ACTDestroyable : public ACTBuildable
{
	GENERATED_BODY()

public:
	ACTDestroyable();

protected:
	virtual void BeginPlay() override;

	virtual void UpdateInteractionCollision(bool CollisionEnabled) override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void ConstructionFinished(ACTBuildable* Buildable);
};
