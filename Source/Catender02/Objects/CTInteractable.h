#pragma once

#include "CoreMinimal.h"
#include "./Catender02/CTSortable.h"
#include "CTInteractable.generated.h"


UCLASS()
class CATENDER02_API ACTInteractable : public ACTSortable
{
	GENERATED_BODY()

	// TODO AddDynamic Binding to Capsule Component
	UFUNCTION()
	void OnBoxBeginOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	// TODO AddDynamic Binding to Capsule Component
	UFUNCTION()
	void OnBoxEndOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};
