
#include "CTBuildingComponent.h"

#include "Catender02/Objects/CTBuildable.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void UCTBuildingComponent::ResetCurrentProgress()
{
	CurrentProgress = 0;
}

UCTBuildingComponent::UCTBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

int UCTBuildingComponent::GetMaxBuildingLevel()
{
	if(!HasLevel()) return 0;
	return BuildingLevelInformation.Num() -1;
}

int UCTBuildingComponent::GetCurrentBuildingLevel()
{
	return CurrentLevel;
}

EBuildingState UCTBuildingComponent::GetBuildingState()
{
	return BuildingState;
}

void UCTBuildingComponent::SetCurrentBuildingLevel(const int NewLevel)
{
	const int OldLevel = CurrentLevel;
	
	if (BuildingLevelInformation.Num() == 0)
	{
		CurrentLevel = 0;
		return;
	}
		
	CurrentLevel = FMath::Clamp(NewLevel, 0, BuildingLevelInformation.Num() - 1);

	OnCurrentLevelChanged.Broadcast(OwningBuildable, OldLevel, NewLevel);
}

void UCTBuildingComponent::UpdateSprite()
{
	UPaperFlipbookComponent* FlipbookComponent = OwningBuildable->GetSprite();
	
	if(!FlipbookComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("FlipbookComponent ist null!"));
		return;		
	}
	
	FlipbookComponent->SetVisibility(true);
	
	if(!HasLevel())
	{
		FlipbookComponent->SetFlipbook(DefaultFlipbook);
		return;
	}

	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	switch (GetBuildingState())
	{
		case EBuildingState::Invisible:
			{
				FlipbookComponent->SetVisibility(false);
				break;
			}
		case EBuildingState::Inactive:
			{
				FlipbookComponent->SetFlipbook(DefaultFlipbook);
				break;
			}
		case EBuildingState::Active:
			{
				FlipbookComponent->SetFlipbook(LevelInformation.FinishFlipbook);
				break;
			}
		case EBuildingState::Construction:
			{
				FlipbookComponent->SetFlipbook(LevelInformation.ConstructionFlipbook);
				break;
			}
		case EBuildingState::Destroyed:
			{
				FlipbookComponent->SetFlipbook(LevelInformation.DestroyedFlipbook);
				break;
			}
		default:
			{
				FlipbookComponent->SetFlipbook(DefaultFlipbook);
			}
	}

	OwningBuildable->CreateDynamicMaterialForSprite();
}

bool UCTBuildingComponent::HasLevel()
{
	return BuildingLevelInformation.Num() > 0;
}

void UCTBuildingComponent::AddProgressToBuilding(const float Amount)
{
	if (!OwningBuildable)
    {
        UE_LOG(LogTemp, Warning, TEXT("OwningBuildable ist null!"));
        return;
    }
 
    if (!HasLevel()) return;
    if (BuildingState != EBuildingState::Construction) return;
 
    const float ProgressNeeded = GetProgressNeededForCurrentBuildingLevel();
    if (ProgressNeeded <= 0) return;
 
    const float OldProgress = CurrentProgress;
    
    CurrentProgress += Amount;
	float NewProgress = CurrentProgress;
    OnConstructionProgressChanged.Broadcast(OwningBuildable, OldProgress, NewProgress);
 
    if (CurrentProgress >= ProgressNeeded)
    {
        OnConstructionFinished.Broadcast(OwningBuildable);
    }
}

float UCTBuildingComponent::GetProgressNeededForCurrentBuildingLevel()
{
	if(!HasLevel()) return 0;
	return GetBuildingLevelInformation(CurrentLevel).ProgressNeeded;
}

void UCTBuildingComponent::UpdateCollision(EBuildingState NewBuildingState)
{
	if(!OwningBuildable) return;

	UBoxComponent* ConstructionBox = OwningBuildable->GetConstructionSiteBoxComponent();
	if(!ConstructionBox) return;
	
	if(NewBuildingState == EBuildingState::Construction)
	{
		ConstructionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		ConstructionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


void UCTBuildingComponent::PayResources()
{
	if(!OwningBuildable) return;

	UCTWorldResourceComponent* ResourceComponent = OwningBuildable->GetGameMode()->WorldResourceComponent;
	
	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	for (FResource NeededResource : LevelInformation.Resources)
	{
		if(ResourceComponent->IsUnlockResource(NeededResource.ResourceType)) continue;

		ResourceComponent->TrySubtractResourceAmount(NeededResource.ResourceType, NeededResource.Amount);
	}
}


bool UCTBuildingComponent::CheckResourceRequirements()
{
	if(!OwningBuildable) return false;

	UCTWorldResourceComponent* ResourceComponent = OwningBuildable->GetGameMode()->WorldResourceComponent;
	
	bool Result = false;

	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	for (FResource Resource : LevelInformation.Resources)
	{
		Result = ResourceComponent->CheckResource(Resource.ResourceType, Resource.Amount);
		if (!Result) break;
	}

	if (!Result)
	{
		OnConstructionFailed.Broadcast(OwningBuildable, LevelInformation.Resources);
	}
	
	return Result;
}


 bool UCTBuildingComponent::UpgradeBuilding()
{
	if (!OwningBuildable)
		return false;
   
	if (!CheckResourceRequirements())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough Resources to Upgrade Buildable!"));
		return false;
	}
   
	switch (GetBuildingState())
	{
	case EBuildingState::Invisible:
	case EBuildingState::Construction:
		return false;
   
	case EBuildingState::Inactive:
		{
			SetBuildingState(EBuildingState::Construction);
			PayResources();
			UpdateBuilding();
			ResetCurrentProgress();
			OnConstructionStarted.Broadcast(OwningBuildable);
			return true;
		}
	case EBuildingState::Active:
		{
			if (GetMaxBuildingLevel() == GetCurrentBuildingLevel())
				return false;
   
			SetBuildingState(EBuildingState::Construction);
			SetCurrentBuildingLevel(GetCurrentBuildingLevel() + 1);
			PayResources();
			UpdateBuilding();
			ResetCurrentProgress();
			OnConstructionStarted.Broadcast(OwningBuildable);	
			return true;
		}
 
	case EBuildingState::Destroyed:
		{
			SetBuildingState(EBuildingState::Construction);
			UpdateBuilding();
			PayResources();
			ResetCurrentProgress();
			OnConstructionStarted.Broadcast(OwningBuildable);
			return true;
		}
   
	default:
		return false;
	}
}


void UCTBuildingComponent::UpdateBuilding()
{
	UpdateSprite();
	UpdateCollision(GetBuildingState());
}

bool UCTBuildingComponent::CanBeBuild()
{	
	if (GetBuildingState() == EBuildingState::Inactive)
	{
		UKismetSystemLibrary::PrintString(this, "CanBeBuild(): Inactive");
		return true;
	}

	if (GetBuildingState() == EBuildingState::Destroyed)
	{
		UKismetSystemLibrary::PrintString(this, "CanBeBuild(): Destroyed");
		return true;
	}
	
	if (GetMaxBuildingLevel() > GetCurrentBuildingLevel()
		&& GetBuildingState() == EBuildingState::Active)
	{		
		UKismetSystemLibrary::PrintString(this, "CanBeBuild(): Active and Max Level not Reached");
		return true;
	}

	
	return false;
}

TArray<FResource> UCTBuildingComponent::GetResourcesCostForCurrentLevel()
{
	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	TArray<FResource> Resources;
	
	for (FResource Resource : LevelInformation.Resources)
	{
		Resources.Add(Resource);
	}

	return Resources;
}


FBuildingLevelInformation UCTBuildingComponent::GetBuildingLevelInformation(int Level)
{
	return BuildingLevelInformation[Level];
}

void UCTBuildingComponent::SetBuildingState(EBuildingState NewBuildingState)
{
	EBuildingState OldBuildingState = GetBuildingState();

	BuildingState = NewBuildingState;

	OnBuildingStateChanged.Broadcast(OwningBuildable, OldBuildingState, NewBuildingState);
}

void UCTBuildingComponent::ConstructionFinished(ACTBuildable* Buildable)
{
	SetBuildingState(EBuildingState::Active);
	UpdateBuilding();
}

void UCTBuildingComponent::ConstructionProgressChanged(ACTBuildable* Buildable, float OldProgress, float NewProgress)
{
}

void UCTBuildingComponent::ConstructionFailed(ACTBuildable* Buildable, TArray<FResource> NeededResources)
{
}

void UCTBuildingComponent::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldBuildingState,
                                                EBuildingState NewBuildingState)
{
}

void UCTBuildingComponent::CurrentLevelChanged(ACTBuildable* Buildable, int OldLevel, int NewLevel)
{
}

void UCTBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningBuildable = Cast<ACTBuildable>(GetOwner());

	UpdateBuilding();
	
	OnBuildingStateChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::BuildingStateChanged
	);
	OnCurrentLevelChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::CurrentLevelChanged
	);
	OnConstructionProgressChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionProgressChanged
	);
	OnConstructionFinished.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionFinished
	);
	OnConstructionFailed.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionFailed
	);
}

void UCTBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

