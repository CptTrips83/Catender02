// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldDayTimeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams
  (
  	FDayTimeChanged,
  	int, OldValue,
  	int, NewValue,
  	bool, OldIsDay,
  	bool, NewIsDay
  );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTWorldDayTimeComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UDirectionalLightComponent* DirectionalLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int DayLength = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int NightLength = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float HourLength = 60;

	int CurrentMinute = 0;
	int CurrentHour = 6;
	int CurrentDay = 1;

	int GetDayLength() const { return DayLength + NightLength; }
	
public:
	UCTWorldDayTimeComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool IsDay();
	
	UFUNCTION(BlueprintAssignable)
	FDayTimeChanged OnDayTimeChanged;

	UFUNCTION(BlueprintAssignable)
	FDayTimeChanged OnDayChanged;
};
