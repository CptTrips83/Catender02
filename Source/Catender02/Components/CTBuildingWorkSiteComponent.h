
#pragma once

#include "CoreMinimal.h"
#include "CTBuildingComponent.h"
#include "Catender02/Character/CTFriendlyNPCCharacter.h"
#include "Components/ActorComponent.h"
#include "CTBuildingWorkSiteComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTBuildingWorkSiteComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<ACTFriendlyNPCCharacter*> WorkingFriendlyNPCCharacters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AmountWorkPlaces = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<TEnumAsByte<EBuildingState>, TSubclassOf<ACTFriendlyNPCCharacter>> BuildingStatesWorker;
	
	UCTBuildingComponent* BuildingComponent = nullptr;
	ACTBuildable* OwningBuildable = nullptr;
	
public:
	UCTBuildingWorkSiteComponent();

	

	virtual void AddFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	virtual void RemoveFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);

	virtual bool HasFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	virtual int CountFriendlyNPCCharacters();
	virtual bool HasOpenWorkPlace();
	void AddBuildingStateChangedListener();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState);

	void GetBuildingComponentFromOwner();
	void GetOwningBuildableFromOwner();

	/**
	 * Determines if a given NPC character is associated with an active work site.
	 *
	 * Checks the building state of the building component and cross-references it
	 * with the mapping of building states to NPC character subclasses to determine
	 * if the given NPC character corresponds to the required subclass for the current building state.
	 *
	 * @param NPCCharacter A pointer to an NPC character to check.
	 * @return true if the NPC character is associated with an active work site, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool HasActiveWorkSite(const ACTFriendlyNPCCharacter* NPCCharacter) const;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
