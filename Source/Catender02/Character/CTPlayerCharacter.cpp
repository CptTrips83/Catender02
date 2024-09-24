// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerCharacter.h"

ACTPlayerCharacter::ACTPlayerCharacter()
{
	PlayerInteractionComponent = CreateDefaultSubobject<UCTPlayerInteractionComponent>("PlayerInteractionComponent");
	AddOwnedComponent(PlayerInteractionComponent);
}
