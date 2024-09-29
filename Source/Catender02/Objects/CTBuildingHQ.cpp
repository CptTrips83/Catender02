// Fill out your copyright notice in the Description page of Project Settings.


#include "CTBuildingHQ.h"


// Sets default values
ACTBuildingHQ::ACTBuildingHQ()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACTBuildingHQ::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTBuildingHQ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACTBuildingHQ::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

