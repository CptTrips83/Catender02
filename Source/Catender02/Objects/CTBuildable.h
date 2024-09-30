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
	UBoxComponent* ConstructionBoxComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* WaitingBoxComponent = nullptr;
	
public:
	ACTBuildable();	
	
	virtual void Interact(ACTSortable* OtherSortable) override;

	virtual void Destroyed() override;
	
	UCTBuildingComponent* GetBuildingComponent() const;
	UBoxComponent* GetConstructionBoxComponent() const;
	UBoxComponent* GetWaitingBoxComponent() const;
};
