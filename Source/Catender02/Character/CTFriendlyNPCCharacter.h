
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "CTFriendlyNPCCharacter.generated.h"

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
	
public:
	ACTFriendlyNPCCharacter();

protected:
	virtual void BeginPlay() override;

	virtual ACTBuildable* GetAssignedBuildable();
	
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

	
};
