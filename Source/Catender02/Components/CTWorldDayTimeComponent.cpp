
#include "CTWorldDayTimeComponent.h"


UCTWorldDayTimeComponent::UCTWorldDayTimeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWorldDayTimeComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UCTWorldDayTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentMinute += DeltaTime;

	if (CurrentMinute < HourLength) return;

	const int OldHour = CurrentMinute;
	const int OldDay = CurrentDay;
	const int OldIsDay = IsDay();
	
	if (CurrentMinute >= HourLength)
	{		
		CurrentMinute = 0;
		CurrentHour++;

		OnDayTimeChanged.Broadcast(OldHour, CurrentHour, OldIsDay, IsDay());
	}

	if (CurrentMinute > GetDayLength())
	{
		CurrentHour = 0;
		CurrentDay++;

		OnDayChanged.Broadcast(OldDay, CurrentDay, OldIsDay, IsDay());
	}
}

bool UCTWorldDayTimeComponent::IsDay()
{
	return true;
}

