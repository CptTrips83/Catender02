
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

	UCTBuildingComponent* BuildingComponent = nullptr;
	ACTBuildable* OwningBuildable = nullptr;
	
public:
	UCTBuildingWorkSiteComponent();

	

	virtual void AddFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	virtual void RemoveFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);

	virtual bool HasFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	virtual int CountFriendlyNPCCharacters();
	virtual bool HasOpenWorkPlace();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState);

	void GetBuildingComponentFromOwner();
	void GetOwningBuildableFromOwner();
	
	UFUNCTION(BlueprintPure)
	UBoxComponent* GetActiveWorkSite() const;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
