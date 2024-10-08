// Fill out your copyright notice in the Description page of Project Settings.


#include "CTUserWidgetMain.h"

#include "Components/PanelWidget.h"

ACTInteractable* UCTUserWidgetMain::GetOwningInteractable() const
{
	return OwningInteractable;
}

void UCTUserWidgetMain::SetOwningInteractable(ACTInteractable* Interactable)
{
	OwningInteractable = Interactable;
}


