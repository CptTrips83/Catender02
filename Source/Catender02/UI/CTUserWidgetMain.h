// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTUserWidgetMain.generated.h"

class ACTInteractable;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CATENDER02_API UCTUserWidgetMain : public UUserWidget
{
	GENERATED_BODY()

	ACTInteractable* OwningInteractable;

public:
	UFUNCTION(BlueprintPure)
	ACTInteractable* GetOwningInteractable() const;

	UFUNCTION(BlueprintCallable)
	void SetOwningInteractable(ACTInteractable* Interactable);

};
