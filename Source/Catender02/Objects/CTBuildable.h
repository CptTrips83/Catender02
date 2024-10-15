// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTInteractable.h"
#include "Catender02/Components/CTBuildingComponent.h"
#include "CTBuildable.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class CATENDER02_API ACTBuildable : public ACTInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTBuildingComponent* BuildingComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* ConstructionSiteBoxComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* WaitingBoxComponent = nullptr;
	
public:
	ACTBuildable();

	virtual void BeginPlay() override;	
	virtual void Interact(ACTSortable* OtherSortable) override;
	virtual void Destroyed() override;
	virtual void UpdateConstructionCollision(bool IsActive);
	
	UCTBuildingComponent* GetBuildingComponent() const;
	UBoxComponent* GetConstructionSiteBoxComponent() const;
	UBoxComponent* GetWaitingBoxComponent() const;

	virtual bool CanInteract() const override;

	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState);
};
