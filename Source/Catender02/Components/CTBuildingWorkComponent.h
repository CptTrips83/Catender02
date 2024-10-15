
#pragma once

#include "CoreMinimal.h"
#include "CTBuildingComponent.h"
#include "Catender02/Character/CTFriendlyNPCCharacter.h"
#include "Components/ActorComponent.h"
#include "CTBuildingWorkComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTBuildingWorkComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<ACTFriendlyNPCCharacter*> WorkingFriendlyNPCCharacters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AmountWorkPlaces = 1;

	UCTBuildingComponent* BuildingComponent = nullptr;
	
public:
	UCTBuildingWorkComponent();

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
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
