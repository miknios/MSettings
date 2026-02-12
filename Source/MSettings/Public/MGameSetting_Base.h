// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MGameSetting_Base.generated.h"

class UMGameSettingsSaveObject;
class UMGameSettingWidget_Base;

UENUM(BlueprintType)
enum class ESettingApplyMode : uint8
{
	Realtime, // Apply instantly
	OnApply // Apply only when user clicks Apply
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMOnGameSettingSelectedValueChangedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMOnGameSettingAppliedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMOnGameSettingEditableStateMightChangeSignature);

UCLASS(Abstract, Blueprintable)
class MSETTINGS_API UMGameSetting_Base : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	ESettingApplyMode ApplyMode = ESettingApplyMode::OnApply;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Settings")
	FMOnGameSettingSelectedValueChangedSignature OnSelectedValueChangedDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Settings")
	FMOnGameSettingAppliedSignature OnAppliedDelegate;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Settings")
	FMOnGameSettingEditableStateMightChangeSignature OnEditableStateMightChangedDelegate;

	// Applied selected value to engine and saves to config files
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ApplyAndSave();

	// Reverts selected value to last saved value
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void RevertSelectedValueToSavedOrDefault(bool bApply);

	// Resets to default value defined per setting class
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void RevertSelectedValueToDefault(bool bApply);
	
	// Each setting can decide if it's available based on other settings
	UFUNCTION(BlueprintCallable, Category = "Settings")
	virtual bool IsAvailable() const { return true; }

	// Called when setting object is created to initialize with saved value or default
	void Initialize();

protected:
	static UGameUserSettings* GetGameUserSettings();
	static UMGameSettingsSaveObject* GetGameSettingsSaveObject();
	
	// Apply current value to engine
	virtual void Apply_Implementation() PURE_VIRTUAL(UGameSetting::Apply_Implementation,);

	// Revert to last saved value
	virtual void SelectSavedOrDefaultValue() PURE_VIRTUAL(UGameSetting::SelectSavedValue,);

	// Reset to designer default
	virtual void SelectDefaultValue() PURE_VIRTUAL(UGameSetting::SelectDefaultValue,);
	
	// Optional step to initialize some data on setting object creation
	virtual void Initialize_Implementation();
	
	// Helper value used for suppressing apply when needed
	UPROPERTY(Transient)
	bool bSuppressApply = false;
};

UCLASS(DefaultToInstanced, EditInlineNew)
class UMGameSetting_Discrete_OptionData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings", meta = (GetOptions = GetPossibleValues))
	FName ValueId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Settings")
	FText Description;

	UFUNCTION()
	TArray<FName> GetPossibleValues() const;
};

UCLASS(Abstract)
class UMGameSetting_Discrete : public UMGameSetting_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Game Settings")
	FName GetSelectedOptionId() const;
	
	void SetSelectedOptionId(FName NewId);
	void SetSelectedOptionIdByIndex(int OptionIndex);
	int32 GetSelectedOptionDataIndex() const;
	TArrayView<const TObjectPtr<UMGameSetting_Discrete_OptionData>> GetOptions() const;
	TArray<FText> GetOptionDisplayNames() const;

	UFUNCTION()
	virtual TArray<FName> GetPossibleOptionIds() PURE_VIRTUAL(UMGameSetting_Discrete::GetPossibleOptionIds, return {};)

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category="Settings")
	TArray<TObjectPtr<UMGameSetting_Discrete_OptionData>> OptionDataArray;

	UPROPERTY(Transient)
	FName SelectedOptionId;
};
