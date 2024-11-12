
#include "CTWorldDayTimeComponent.h"

#include "Components/DirectionalLightComponent.h"


float UCTWorldDayTimeComponent::GetHourLightIntensity() const
{
	return (MaxLightIntensity - MinLightIntensity) / ((DayLength + NightLength) / 2);
}

float UCTWorldDayTimeComponent::GetHourCurveValue() const
{
	float FloatHour = static_cast<float>(CurrentHour) / static_cast<float>(DayLength + NightLength);
	return CurveFloat->GetFloatValue(FloatHour);
}

UCTWorldDayTimeComponent::UCTWorldDayTimeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWorldDayTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	OnDayTimeChanged.AddDynamic(this, &UCTWorldDayTimeComponent::DayTimeChanged);
}

void UCTWorldDayTimeComponent::DayTimeChanged(int OldHour, int NewHour, bool OldIsDay, bool NewIsDay)
{
	if (OldHour == NewHour) return;
	if (!CurveFloat) return;
	if (!DirectionalLight) return;
	
	float CurveValue = GetHourCurveValue() * 10;
	float HourLightIntensity = GetHourLightIntensity();

	float NewLightIntensity = FMath::Clamp(
		(MinLightIntensity + (HourLightIntensity * CurveValue)),
		MinLightIntensity,
		MaxLightIntensity
		);

	FString DebugMessage = "Day Time: " + FString::FromInt(NewHour)
		+ " " + FString::SanitizeFloat(HourLightIntensity)
		+ " " + FString::SanitizeFloat(GetHourCurveValue())
		+ " " + FString::SanitizeFloat(NewLightIntensity);
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		DebugMessage
		);
	
	TargetIntensity = NewLightIntensity;
}

void UCTWorldDayTimeComponent::ApplyTargetIntensity()
{	
	float CurrentLightIntensity = DirectionalLight->GetComponent()->Intensity;

	if(CurrentLightIntensity == TargetIntensity) return;
	
	float Alpha = 0.005f;	
	float NewLightIntensity = FMath::Lerp(CurrentLightIntensity, TargetIntensity, Alpha);	
	DirectionalLight->GetComponent()->SetIntensity(NewLightIntensity);
}


void UCTWorldDayTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplyTargetIntensity();
	
	CurrentMinute += DeltaTime;

	if (CurrentMinute < HourLength) return;

	int OldHour = CurrentMinute;
	int OldDay = CurrentDay;
	bool OldIsDay = IsDay();
	
	if (CurrentMinute >= HourLength)
	{		
		CurrentMinute = 0;
		CurrentHour++;

		OnDayTimeChanged.Broadcast(OldHour, CurrentHour, OldIsDay, IsDay());
	}

	if (CurrentHour >= GetDayLength())
	{
		CurrentHour = 0;
		CurrentDay++;

		OnDayChanged.Broadcast(OldDay, CurrentDay, OldIsDay, IsDay());
	}
}

bool UCTWorldDayTimeComponent::IsDay()
{
	FString DebugMessageVariable = (GetHourCurveValue() > 0.3f) ? "true" : "false";
	FString DebugMessage = "Is Day: " + DebugMessageVariable;
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		DebugMessage
		);
	return GetHourCurveValue() > 0.3f;
}

