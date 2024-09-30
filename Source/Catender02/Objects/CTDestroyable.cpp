// Fill out your copyright notice in the Description page of Project Settings.


#include "CTDestroyable.h"


// Sets default values
ACTDestroyable::ACTDestroyable()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACTDestroyable::BeginPlay()
{
	Super::BeginPlay();

	GetBuildingComponent()->OnConstructionFinished.AddDynamic(this, &ACTDestroyable::ConstructionFinished);
}

// Called every frame
void ACTDestroyable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACTDestroyable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACTDestroyable::ConstructionFinished(ACTBuildable* Buildable)
{
	Destroy();
}

