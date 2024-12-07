// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Catender02/CTSortable.h"
#include "Catender02/Character/CTEnemyNPCCharacter.h"
#include "CTWildlife.generated.h"

UCLASS()
class CATENDER02_API ACTWildlife : public ACTEnemyNPCCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTWildlife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
