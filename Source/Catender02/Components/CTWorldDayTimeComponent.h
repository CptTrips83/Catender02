
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DirectionalLight.h"
#include "CTWorldDayTimeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams
  (
  	FDayTimeChanged,
  	int, OldValue,
  	int, NewValue,
  	bool, OldIsDay,
  	bool, NewIsDay
  );

/**
 * A component that manages the simulation of day and night cycles, controlling a directional light
 * to visually represent the progression of time in a game world.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTWorldDayTimeComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * Holds a soft reference to an ADirectionalLight object which allows for
	 * deferred loading of the light asset and provides safety for cases when
	 * the asset isn't immediately available.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<ADirectionalLight> DirectionalLight;

	/**
	 * A reference to a curve asset used to drive a floating-point value over time, typically
	 * for the purpose of applying time-based modifications to variables such as light intensity
	 * throughout a day and night cycle in game environments.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	UCurveFloat* CurveFloat;

	/**
	 * Specifies the minimum light intensity value that the directional light can have during the day and night
	 * cycles in the game world. This ensures that the light never goes below this intensity even during the darkest
	 * periods, maintaining a base level of illumination for visibility and ambience.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	float MinLightIntensity = 0.1f;

	/**
	 * Defines the maximum intensity value that the directional light can reach during the simulation
	 * of day and night cycles in the game world. This cap ensures that the light does not exceed this
	 * intensity, maintaining a balanced visual brightness in the environment.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	float MaxLightIntensity = 10.0f;

	/**
	 * Determines the duration of the daytime cycle in the game world, affecting how long the 'day' period lasts
	 * before transitioning into night. This value is used in conjunction with night length to control the overall
	 * day and night cycle duration within the simulation.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	int DayLength = 16;

	/**
	 * Specifies the duration, in in-game hours, that the night period lasts within the day and night cycle in the game world.
	 * This value, in combination with DayLength, determines the total cycle duration, influencing game mechanics related
	 * to time of day.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	int NightLength = 8;

	/**
	 * A multiplier applied to the light intensity during nighttime, allowing for the adjustment
	 * of how dark the environment should be when the game world transitions to night.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	float NightModifier = 0.75f;

	/**
	 * Specifies the duration (in minutes) of an in-game hour. This value determines how long one hour lasts
	 * within the game world's simulated day and night cycle, affecting the progression speed of time in the game.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	float HourLength = 60;

	/**
	 * Represents the current minute within an in-game hour, used to track the passage of time
	 * in the game's day and night cycle simulation.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Day Time", meta = (AllowPrivateAccess = true))
	float CurrentMinute = 0;
	/**
	 * Represents the current hour in the in-game day and night cycle simulation.
	 * Used to track the progression of time within the game world.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Day Time", meta = (AllowPrivateAccess = true))
	int CurrentHour = 8;
	/**
	 * Represents the current day within the in-game day and night cycle simulation.
	 * Used to track the number of days that have passed in the game world.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Day Time", meta = (AllowPrivateAccess = true))
	int CurrentDay = 1;

	/**
	 * Defines the speed at which the light intensity changes, affecting the transition between day and night cycles in the game world.
	 * The value is configurable within the editor and can be accessed and modified in blueprints.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Day Time", meta = (AllowPrivateAccess = true))
	float LightIntensitySwitchSpeed = 0.0001f;
	
	/**
	 * Calculates the total length of a full day cycle, which includes both the day and night periods.
	 *
	 * @return The combined duration of day and night in the game's time cycle.
	 */
	UFUNCTION()
	int GetDayLength() const { return DayLength + NightLength; }

	/**
	 * Computes the light intensity value specific to each hour within the day and night cycle.
	 *
	 * @return The calculated light intensity for a particular hour based on the configured day and night durations.
	 */
	UFUNCTION()
	float GetHourLightIntensity() const;
	/**
	 * Computes a floating-point value representing the progress of the current hour within the
	 * entire day and night cycle based on configured durations.
	 *
	 * @return A normalized float value (between 0 and 1) indicating the proportion of the current
	 * hour within the total duration of the day and night cycle.
	 */
	UFUNCTION()
	float GetHourCurveValue() const;

	/**
	 * Specifies the desired light intensity for the directional light in the game world.
	 * This value is used to adjust the brightness of the light to create varying visual
	 * effects corresponding to different times of the day, enhancing the realism of the simulation.
	 */
	UPROPERTY()
	float TargetIntensity = 0.1f;
	
public:
	UCTWorldDayTimeComponent();

	UFUNCTION(BlueprintPure, Category = "Day Time")
	float GetCurrentIntensity() const;

	UFUNCTION(BlueprintPure, Category = "Day Time")
	float GetLightIntensitySwitchSpeed() const;
	
protected:
	virtual void BeginPlay() override;

	/**
	 * Handles changes in the game's day time, updating the directional light intensity
	 * to reflect the transition from one hour to another within the game world.
	 *
	 * @param OldHour The hour representing the previous state before the change.
	 * @param NewHour The hour representing the new state after the change.
	 * @param OldIsDay A boolean indicating if it was day in the previous state.
	 * @param NewIsDay A boolean indicating if it is day in the new state.
	 */
	UFUNCTION()
	virtual void DayTimeChanged(int OldHour, int NewHour, bool OldIsDay, bool NewIsDay);

	/**
	 * Adjusts the directional light's intensity towards the target intensity over time.
	 * This method gradually changes the light intensity to create a smooth transition
	 * between the current intensity and the target intensity.
	 */
	UFUNCTION()
	virtual void ApplyTargetIntensity();
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Checks if the current time in the game world is considered daytime.
	 *
	 * @return true if it is currently day, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool IsDay();

	/**
	 * Delegate that is triggered whenever there is a change in the day/night cycle time.
	 */
	UPROPERTY(BlueprintAssignable)
	FDayTimeChanged OnDayTimeChanged;

	/**
	 * Delegate that is triggered whenever the day changes within the game world, allowing other systems
	 * or components to react to the transition between days.
	 */
	UPROPERTY(BlueprintAssignable)
	FDayTimeChanged OnDayChanged;

	UPROPERTY(BlueprintAssignable)
	FDayTimeChanged OnDayNightChanged;
};
