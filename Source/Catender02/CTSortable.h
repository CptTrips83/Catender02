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

	/**
	 * A component used for sorting game objects within the level.
	 * This property is exposed to the Unreal Editor for easy access and manipulation.
	 *
	 * - EditAnywhere: Indicates that the property is editable in the Unreal Editor.
	 * - BlueprintReadWrite: Indicates that the property can be read or written from Blueprints.
	 * - meta = (AllowPrivateAccess, DeprecatedProperty):
	 *      - AllowPrivateAccess: Allows private access to this property within the class.
	 *      - DeprecatedProperty: Marks this property as deprecated, indicating it may be removed in future versions. Use GetSortiningComponent instead
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, DeprecatedProperty))
	UCTSortingComponent* SortingComponent = nullptr;

	UFUNCTION(BlueprintPure)
	virtual ACTGameModeLevel* GetGameMode() const;

	UFUNCTION(BlueprintPure)
	UCTSortingComponent* GetSortingComponent() const;
	
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
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Interact(ACTSortable* OtherSortable);
};
