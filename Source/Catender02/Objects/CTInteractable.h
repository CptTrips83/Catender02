#pragma once

#include "CoreMinimal.h"
#include "./Catender02/CTSortable.h"
#include "CTInteractable.generated.h"


UCLASS()
class CATENDER02_API ACTInteractable : public ACTSortable
{
	GENERATED_BODY()

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
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Interact(ACTSortable* OtherSortable) override;
};
