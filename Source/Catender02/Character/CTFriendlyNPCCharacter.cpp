
#include "CTFriendlyNPCCharacter.h"

#include "Catender02/Objects/CTBuilding.h"


ACTFriendlyNPCCharacter::ACTFriendlyNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTFriendlyNPCCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ACTFriendlyNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTFriendlyNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACTFriendlyNPCCharacter::AssignToBuildingWorkSite(ACTBuildable* Buildable)
{
	if(!Buildable) return;
	AssignedBuildable = Buildable;
	Buildable->GetBuildingWorkSiteComponent()->AddFriendlyNPCCharacter(this);
}

void ACTFriendlyNPCCharacter::WithdrawFromBuildingWorkSite(ACTBuildable* Buildable)
{	
	if(!Buildable) return;
	AssignedBuildable = nullptr;
	Buildable->GetBuildingWorkSiteComponent()->RemoveFriendlyNPCCharacter(this);
}

ACTBuildable* ACTFriendlyNPCCharacter::GetNearestWorkingSite()
{
	ACTBuildable* NearestWorkingSite = GetGameMode()->GetWorldBuildableComponent()->GetNearestBuildable(this);

	if (NearestWorkingSite == nullptr)
	{
		return nullptr;	
	}

	if(NearestWorkingSite != AssignedBuildable)
	{
		WithdrawFromBuildingWorkSite(AssignedBuildable);
		AssignToBuildingWorkSite(NearestWorkingSite);
	}
	
    return NearestWorkingSite;
}

