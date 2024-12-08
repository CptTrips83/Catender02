// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Catender02/Character/CTEnemyNPCCharacter.h"
#include "CTWildlife.generated.h"

UCLASS()
class CATENDER02_API ACTWildlife : public ACTEnemyNPCCharacter
{
	GENERATED_BODY()

public:
	ACTWildlife();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
