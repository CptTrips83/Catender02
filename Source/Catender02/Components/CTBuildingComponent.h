
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Character/CTPlayerCharacter.h"
#include "Catender02/Components/CTWorldResourceComponent.h"
#include "Components/ActorComponent.h"
#include "CTBuildingComponent.generated.h"

class ACTBuildable;

UENUM(BlueprintType)
enum EBuildingState
{
	Invisible = 0,
	Inactive = 1,
	Active = 2,
	Construction = 3,
	Destroyed = 4,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FBuildingStateChanged,
	ACTBuildable*, Buildable,
	EBuildingState, OldState,
	EBuildingState, NewState
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FCurrentLevelChange,
	ACTBuildable*, Buildable,
	int, OldLevel,
	int, NewLevel
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FConstructionFinished,
	ACTBuildable*, Building
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FConstructionStarted,
	ACTBuildable*, Building
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FConstructionProgressChanged,
	ACTBuildable*, Building,
	float, OldProgress,
	float, NewProgress
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams
(
	FConstructionFailed,
	ACTBuildable*, Building,
	TArray<FResource>, NeededResources
);

USTRUCT(BlueprintType)
struct FBuildingLevelInformation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ProgressNeeded = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperFlipbook* ConstructionFlipbook = nullptr;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperFlipbook* FinishFlipbook = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperFlipbook* DestroyedFlipbook = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FResource> Resources;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UPaperFlipbook* DefaultFlipbook = nullptr;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int CurrentLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TEnumAsByte<EBuildingState> BuildingState = EBuildingState::Invisible;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<FBuildingLevelInformation> BuildingLevelInformation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float CurrentProgress = 0;

	void ResetCurrentProgress();
	
public:	
	UCTBuildingComponent();

	UFUNCTION(BlueprintPure)
	virtual int GetMaxBuildingLevel();
	UFUNCTION(BlueprintPure)
	virtual int GetCurrentBuildingLevel();	
	UFUNCTION(BlueprintPure)
	virtual EBuildingState GetBuildingState();
	virtual void SetBuildingState(EBuildingState NewBuildingState);	
	UFUNCTION(BlueprintCallable)
	virtual void AddProgressToBuilding(float Amount);	
	UFUNCTION(BlueprintPure)
	virtual float GetProgressNeededForCurrentBuildingLevel();		
	UFUNCTION(BlueprintPure)
	virtual bool CheckResourceRequirements();	
	UFUNCTION(BlueprintCallable)
	virtual bool UpgradeBuilding();
	UFUNCTION (BlueprintCallable)
	virtual void UpdateBuilding();
	UFUNCTION()
	virtual bool CanBeBuild();
	UFUNCTION(BlueprintPure)
	virtual TArray<FResource> GetResourcesCostForCurrentLevel();
	
protected:
	ACTBuildable* OwningBuildable = nullptr;	
	virtual void BeginPlay() override;
	virtual FBuildingLevelInformation GetBuildingLevelInformation(int Level);
	virtual void SetCurrentBuildingLevel(int NewLevel);
	virtual void UpdateSprite();
	virtual void UpdateCollision(EBuildingState NewBuildingState);
	virtual void PayResources();
	virtual bool HasLevel();

	UFUNCTION()
	virtual void ConstructionFinished(ACTBuildable* Buildable);
	UFUNCTION()
	virtual void ConstructionProgressChanged(ACTBuildable* Buildable, float OldProgress, float NewProgress);
	UFUNCTION()
	virtual void ConstructionFailed(ACTBuildable* Buildable, TArray<FResource> NeededResources);
	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldBuildingState, EBuildingState NewBuildingState);
	UFUNCTION()
	virtual void CurrentLevelChanged(ACTBuildable* Buildable, int OldLevel, int NewLevel);
	
public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FBuildingStateChanged OnBuildingStateChanged;
	UPROPERTY(BlueprintAssignable)
	FCurrentLevelChange OnCurrentLevelChanged;
	UPROPERTY(BlueprintAssignable)
	FConstructionProgressChanged OnConstructionProgressChanged;
	UPROPERTY(BlueprintAssignable)
	FConstructionStarted OnConstructionStarted;
	UPROPERTY(BlueprintAssignable)
	FConstructionFinished OnConstructionFinished;
	UPROPERTY(BlueprintAssignable)
	FConstructionFailed OnConstructionFailed;
};
