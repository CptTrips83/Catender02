
#include "CTBuildable.h"

#include "Components/BoxComponent.h"

ACTBuildable::ACTBuildable()
{
	BuildingComponent = CreateDefaultSubobject<UCTBuildingComponent>(TEXT("Building Component"));
	AddOwnedComponent(BuildingComponent);

	BuildingWorkSiteComponent = CreateDefaultSubobject<UCTBuildingWorkSiteComponent>(TEXT("WorkSite Component"));
	AddOwnedComponent(BuildingWorkSiteComponent);
	
	ConstructionSiteBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WorkSite Box"));
	ConstructionSiteBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructionSiteBoxComponent->SetupAttachment(GetRootComponent());

	WaitingBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Waiting Box"));
	WaitingBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WaitingBoxComponent->SetupAttachment(GetRootComponent());
}

void ACTBuildable::BeginPlay()
{
	Super::BeginPlay();

	GetBuildingComponent()->OnBuildingStateChanged.AddDynamic(this, &ACTBuildable::BuildingStateChanged);
}

void ACTBuildable::InteractInternal(ACTSortable* OtherSortable)
{
	Super::InteractInternal(OtherSortable);

	if(!BuildingComponent->UpgradeBuilding()) return;

	const ACTPlayerCharacter* Player = Cast<ACTPlayerCharacter>(OtherSortable);
	Player->PlayInteractSound();

	Highlight(false);
}

void ACTBuildable::Destroyed()
{		
	Super::Destroyed();			
}

void ACTBuildable::UpdateConstructionCollision(const bool IsActive)
{
	GetConstructionSiteBoxComponent()->SetCollisionEnabled(IsActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

UCTBuildingComponent* ACTBuildable::GetBuildingComponent() const
{
	return BuildingComponent;
}

UCTBuildingWorkSiteComponent* ACTBuildable::GetBuildingWorkSiteComponent() const
{
	return BuildingWorkSiteComponent;
}

UBoxComponent* ACTBuildable::GetConstructionSiteBoxComponent() const
{
	return ConstructionSiteBoxComponent;
}

UBoxComponent* ACTBuildable::GetWaitingBoxComponent() const
{
	return WaitingBoxComponent;
}

bool ACTBuildable::CanInteractInternal() const
{	
	return BuildingComponent->CanBeBuild();
}

void ACTBuildable::ProcessWorking_Implementation(ACTFriendlyNPCCharacter* NPCCharacter)
{
}

void ACTBuildable::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState)
{
	if(NewState == EBuildingState::Construction)
	{
		UpdateInteractionCollision(false);
		UpdateConstructionCollision(true);
		return;
	}
	if(OldState == EBuildingState::Construction)
	{
		UpdateInteractionCollision(true);
		UpdateConstructionCollision(false);
	}
}

void ACTBuildable::OnDayNightChanged(int OldHour, int NewHour, bool OldIsDay, bool NewIsDay)
{
	UpdateLights(!NewIsDay && GetBuildingComponent()->GetBuildingState() == Active);
}

void ACTBuildable::OnBuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState)
{
	UpdateLights(!GetGameMode()->GetWorldDayTimeComponent()->IsDay() && NewState == Active);
}

TArray<FResource> ACTBuildable::GetNeededResourcesForInteraction_Implementation()
{
	return GetBuildingComponent()->GetResourcesCostForCurrentLevel();
}



