
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "CTFriendlyNPCCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FWaitingIsChanged,
	ACTFriendlyNPCCharacter*, NPC,
	bool, OldValue,
	bool, NewValue
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FWorkingIsChanged,
	ACTFriendlyNPCCharacter*, NPC,
	bool, OldValue,
	bool, NewValue
);

class ACTBuilding;

/**
 * Represents a friendly non-playable character (NPC) within the game world that can interact with building work sites.
 */
UCLASS()
class CATENDER02_API ACTFriendlyNPCCharacter : public ACTCharacter
{
	GENERATED_BODY()

	/**
	 * Pointer to a buildable object representing the current building work site assigned to the friendly NPC character.
	 */
	UPROPERTY()
	ACTBuildable* AssignedBuildable;

	UPROPERTY()
	bool IsWaiting = false;

	UPROPERTY()
	bool IsWorking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TSoftObjectPtr<ACTBuilding> HomeBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	float WaitingInterval = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FTimerHandle WaitingTimerHandle;
	
public:
	ACTFriendlyNPCCharacter();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartWorking();

	UFUNCTION(BlueprintNativeEvent)
	void ProcessWorking();
	
	UFUNCTION(BlueprintImplementableEvent)	
	void StopWorking();
	
	virtual void OnBoxBeginOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	) override;
	
	virtual void OnBoxEndOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	) override;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	virtual ACTBuildable* GetAssignedBuildable();
	
	/**
	 * Assigns the friendly NPC character to a specified building work site.
	 *
	 * @param Buildable A pointer to the buildable object representing the work site to assign the NPC to.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AssignToBuildingWorkSite(ACTBuildable* Buildable);
	/**
	 * Withdraws the friendly NPC character from a specified building work site.
	 *
	 * @param Buildable A pointer to the buildable object representing the work site to withdraw the NPC from.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void WithdrawFromBuildingWorkSite(ACTBuildable* Buildable);

	/**
	 * Retrieves the nearest working site for the friendly NPC character.
	 *
	 * @return A pointer to the nearest ACTBuildable object representing the work site, or nullptr if no suitable site is found.
	 */
	UFUNCTION(BlueprintPure)
	virtual ACTBuildable* GetNearestWorkingSite();

	UFUNCTION(BlueprintCallable)
	virtual void SetIsWaiting(bool NewValue);

	UFUNCTION(BlueprintPure)
	virtual bool GetIsWaiting();

	UFUNCTION(BlueprintCallable)
	virtual void SetIsWorking(bool NewValue);

	UFUNCTION(BlueprintPure)
	virtual bool GetIsWorking();

	UFUNCTION(BlueprintCallable)
	virtual void SetHomeBuilding(ACTBuilding* Building);

	UFUNCTION(BlueprintPure)
	virtual TSoftObjectPtr<ACTBuilding> GetHomeBuilding();
	
	//UFUNCTION(BlueprintPure)
	//virtual float GetRandomPositionInBox(USceneComponent* Box);
	
	UPROPERTY(BlueprintAssignable)
	FWaitingIsChanged OnWaitingIsChanged;

	UPROPERTY(BlueprintAssignable)
	FWorkingIsChanged OnWorkingIsChanged;
};
