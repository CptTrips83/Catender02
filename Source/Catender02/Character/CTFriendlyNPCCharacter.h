
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "CTFriendlyNPCCharacter.generated.h"

class ACTBuilding;

UCLASS()
class CATENDER02_API ACTFriendlyNPCCharacter : public ACTCharacter
{
	GENERATED_BODY()

	ACTBuildable* AssignedBuildable;
	
public:
	ACTFriendlyNPCCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void AssignToBuildingWorkSite(ACTBuildable* Building);
	UFUNCTION(BlueprintCallable)
	virtual void WithdrawFromBuildingWorkSite(ACTBuildable* Building);

	UFUNCTION(BlueprintPure)
	virtual ACTBuildable* GetNearestWorkingSite();
};
