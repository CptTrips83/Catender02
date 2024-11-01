
#include "CTFriendlyNPCCharacter.h"

#include "Catender02/Objects/CTBuilding.h"
#include "Components/CapsuleComponent.h"


void ACTFriendlyNPCCharacter::ResetWorkSiteCapsule()
{
	GetWorkSiteCapsule()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorkSiteCapsule()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

ACTFriendlyNPCCharacter::ACTFriendlyNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WorkSiteCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Work Site Capsule"));
	WorkSiteCapsule->SetupAttachment(GetRootComponent());

	GetCapsuleComponent()->OnComponentBeginOverlap.Clear();
	GetCapsuleComponent()->OnComponentEndOverlap.Clear();

	GetWorkSiteCapsule()->OnComponentBeginOverlap.AddDynamic(this, &ACTFriendlyNPCCharacter::OnWorkSiteBoxBeginOverlap);
	GetWorkSiteCapsule()->OnComponentEndOverlap.AddDynamic(this, &ACTFriendlyNPCCharacter::OnWorkSiteBoxEndOverlap);
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
	if (!AssignedBuildable) return;
	AssignedBuildable->ProcessWorking(this);
}

void ACTFriendlyNPCCharacter::OnWorkSiteBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	ACTBuildable* Buildable = Cast<ACTBuildable>(OtherActor);

	if(!Buildable) return;
	if(!Buildable->GetBuildingWorkSiteComponent()->HasActiveWorkSite(this)) return;
	
	if(AssignedBuildable == Buildable)
	{
		SetIsWorking(true);
		StartWorking();
		ProcessWorking();
	}	
}

void ACTFriendlyNPCCharacter::OnWorkSiteBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBoxEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	
	ACTBuildable* Buildable = Cast<ACTBuildable>(OtherActor);

	if(!Buildable) return;

	if(AssignedBuildable == Buildable)
	{
		WithdrawFromBuildingWorkSite(Buildable);
		StopWorking();
	}	
}

void ACTFriendlyNPCCharacter::Wait()
{
	
	if(!GetIsWaiting())
	{
		WaitingTimerHandle.Invalidate();
		return;
	}

	if(WaitingTimerHandle.IsValid()) return;

	WaitingTimerHandle = FTimerHandle();

	GetWorld()->GetTimerManager().SetTimer(
		WaitingTimerHandle,
		this,
		&ACTFriendlyNPCCharacter::WaitMovement_Implementation,
		CalculateWaitingTime()		
	);
}

void ACTFriendlyNPCCharacter::WaitMovement_Implementation()
{
	if(!GetIsWaiting()) return;
	WaitingTimerHandle.Invalidate();
	WaitMovement();
}


float ACTFriendlyNPCCharacter::CalculateWaitingTime()
{
	return FMath::RandRange(MinWaitingInterval, MaxWaitingInterval);
}

void ACTFriendlyNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetIsWorking())
	{
		ProcessWorking();
	}
}

void ACTFriendlyNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACTFriendlyNPCCharacter::AssignToBuildingWorkSite(ACTBuildable* Buildable)
{
	if(!Buildable) return;
	AssignedBuildable = Buildable;
	ResetWorkSiteCapsule();
	Buildable->GetBuildingWorkSiteComponent()->AddFriendlyNPCCharacter(this);
}

void ACTFriendlyNPCCharacter::WithdrawFromBuildingWorkSite(ACTBuildable* Buildable)
{	
	if(!Buildable) return;
	SetIsWorking(false);
	ResetWorkSiteCapsule();
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

void ACTFriendlyNPCCharacter::SetIsWaiting(bool NewValue)
{
	bool OldValue = IsWaiting;

	if(OldValue == NewValue) return;
	
	IsWaiting = NewValue;
		
	OnWaitingIsChanged.Broadcast(this, OldValue, NewValue);
}

bool ACTFriendlyNPCCharacter::GetIsWaiting()
{
	return IsWaiting;
}

void ACTFriendlyNPCCharacter::SetIsWorking(bool NewValue)
{
	bool OldValue = IsWorking;

	if(OldValue == NewValue) return;
	
	IsWorking = NewValue;
		
	OnWorkingIsChanged.Broadcast(this, OldValue, NewValue);
}

bool ACTFriendlyNPCCharacter::GetIsWorking()
{
	return IsWorking;
}

void ACTFriendlyNPCCharacter::SetHomeBuilding(ACTBuilding* Building)
{
	HomeBuilding = Building;
}

TSoftObjectPtr<ACTBuilding> ACTFriendlyNPCCharacter::GetHomeBuilding()
{
	return HomeBuilding;
}

UCapsuleComponent* ACTFriendlyNPCCharacter::GetWorkSiteCapsule()
{
	return WorkSiteCapsule;
}

