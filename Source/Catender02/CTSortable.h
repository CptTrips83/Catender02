#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/CTSortingComponent.h"
#include "GameMode/CTGameModeLevel.h"
#include "CTSortable.generated.h"


class UBoxComponent;

UCLASS()
class CATENDER02_API ACTSortable : public APaperZDCharacter
{
public:
	ACTSortable();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCTSortingComponent* SortingComponent = nullptr;

	UFUNCTION(BlueprintPure)
	virtual ACTGameModeLevel* GetGameMode() const;

	
protected:
	
	UFUNCTION()
	virtual void OnBoxBeginOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	virtual void OnBoxEndOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
	
	ACTGameModeLevel* GameModeLevel = nullptr;
	
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Interact(ACTSortable* OtherSortable);
};
