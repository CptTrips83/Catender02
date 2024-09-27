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

	
public:
	ACTBuildable();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCTBuildingComponent* BuildingComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* ConstructionBoxComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* WaitingBoxComponent = nullptr;
	
	virtual void Interact(ACTSortable* OtherSortable) override;
};
