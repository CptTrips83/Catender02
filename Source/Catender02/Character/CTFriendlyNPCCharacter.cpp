
#include "CTFriendlyNPCCharacter.h"

#include "Catender02/Objects/CTBuilding.h"
#include "Components/CapsuleComponent.h"


ACTFriendlyNPCCharacter::ACTFriendlyNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTFriendlyNPCCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

ACTBuildable* ACTFriendlyNPCCharacter::GetAssignedBuildable()
{
	return AssignedBuildable;
}

void ACTFriendlyNPCCharacter::ProcessWorking_Implementation()
{
	AssignedBuildable->ProcessWorking(this);
}

void ACTFriendlyNPCCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// TODO IsWorking Mechanik umbauen
	
	ACTBuildable* Buildable = Cast<ACTBuildable>(OtherActor);

	if(!Buildable) return;

	if(AssignedBuildable == Buildable)
	{
		StartWorking();
		ProcessWorking();
	}	
}

void ACTFriendlyNPCCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	
	ACTBuilding* Buildable = Cast<ACTBuilding>(OtherActor);

	if(!Buildable) return;

	if(AssignedBuildable == Buildable)
	{
		WithdrawFromBuildingWorkSite(Buildable);
		StopWorking();		
	}	
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

