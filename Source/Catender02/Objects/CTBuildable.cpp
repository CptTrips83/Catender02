// Fill out your copyright notice in the Description page of Project Settings.


#include "CTBuildable.h"

ACTBuildable::ACTBuildable()
{
	BuildingComponent = CreateDefaultSubobject<UCTBuildingComponent>(TEXT("Building Component"));
	AddOwnedComponent(BuildingComponent);
}
