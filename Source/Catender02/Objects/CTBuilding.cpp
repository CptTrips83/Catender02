// Fill out your copyright notice in the Description page of Project Settings.


#include "CTBuilding.h"


// Sets default values
ACTBuilding::ACTBuilding()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACTBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACTBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

