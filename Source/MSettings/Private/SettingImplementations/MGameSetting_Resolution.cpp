// Copyright (c) Miknios. All rights reserved.


#include "SettingImplementations/MGameSetting_Resolution.h"

#include "MGameSettingsSaveObject.h"
#include "MGameSettingsSubsystem.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SettingImplementations/MGameSetting_FullscreenMode.h"

UMGameSetting_Resolution::UMGameSetting_Resolution()
{
	ApplyMode = ESettingApplyMode::OnApply;
}

void UMGameSetting_Resolution::Initialize_Implementation()
{
	TArray<FIntPoint> SupportedResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);

	ResolutionValueForOptionId.Reserve(SupportedResolutions.Num());
	OptionDataArray.Reserve(SupportedResolutions.Num());
	for (const FIntPoint& SupportedResolution : SupportedResolutions)
	{
		const FName OptionId = MakeResolutionId(SupportedResolution);
		ResolutionValueForOptionId.Emplace(OptionId, SupportedResolution);

		// Generate OptionData objects since they are not defined by the user but generated from available resolutions
		UMGameSetting_Discrete_OptionData* OptionDataNew = NewObject<UMGameSetting_Discrete_OptionData>(this);
		if (OptionDataNew != nullptr)
		{
			OptionDataNew->ValueId = OptionId;

			const FString DisplayStr = FString::Printf(TEXT("%sx%s"),
			                                           *LexToString(SupportedResolution.X),
			                                           *LexToString(SupportedResolution.Y));
			OptionDataNew->DisplayName = FText::FromString(DisplayStr);

			OptionDataArray.Emplace(OptionDataNew);
		}
	}

	// Save the best resolution that we can revert to in case of any problems
	NativeResolutionOptionId = MakeResolutionId(GetBestNativeResolution());
	
	BindToFullscreenModeChanges();
}

bool UMGameSetting_Resolution::IsAvailable() const
{
	UMGameSettingsSubsystem* SettingsSubsystem = GetTypedOuter<UMGameSettingsSubsystem>();
	if (!IsValid(SettingsSubsystem))
	{
		return Super::IsAvailable();
	}

	UMGameSetting_FullscreenMode* FullscreenModeSetting =
		Cast<UMGameSetting_FullscreenMode>(SettingsSubsystem->GetSettingObjectForClass(UMGameSetting_FullscreenMode::StaticClass()));
	if (!IsValid(FullscreenModeSetting))
	{
		return Super::IsAvailable();
	}
	
	return FullscreenModeSetting->GetSelectedOptionId() != TEXT("WindowedFullscreen");
}

void UMGameSetting_Resolution::Apply_Implementation()
{
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	if (!IsValid(GameUserSettings))
	{
		return;
	}

	const FName SelectedResId = GetSelectedOptionId();
	const FIntPoint SelectedResValue = GetResolutionValueForId(SelectedResId);
	GameUserSettings->SetScreenResolution(SelectedResValue);
	GameUserSettings->ApplyResolutionSettings(true);
}

void UMGameSetting_Resolution::SelectSavedOrDefaultValue()
{
	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	if (!IsValid(GameUserSettings))
	{
		return;
	}

	const FIntPoint ResolutionValueSaved = GameUserSettings->GetScreenResolution();
	const bool bShouldRevertToDefault = [ResolutionValueSaved, this]() -> bool
	{
		if (ResolutionValueSaved == FIntPoint::NoneValue)
		{
			return true;
		}

		const bool bSavedResAvailable = IsResolutionAvailableByValue(ResolutionValueSaved);
		return !bSavedResAvailable;
	}();

	if (bShouldRevertToDefault)
	{
		SelectDefaultValue();
		return;
	}

	SetSelectedOptionId(MakeResolutionId(ResolutionValueSaved));
}

void UMGameSetting_Resolution::SelectDefaultValue()
{
	SetSelectedOptionId(NativeResolutionOptionId);
}

TArray<FName> UMGameSetting_Resolution::GetPossibleOptionIds()
{
	TArray<FName> SupportedOptionIds;
	ResolutionValueForOptionId.GetKeys(SupportedOptionIds);

	return SupportedOptionIds;
}

FIntPoint UMGameSetting_Resolution::GetMaxSupportedResolution()
{
	FIntPoint MaxResolution;
	for (auto [ResId, ResValue] : ResolutionValueForOptionId)
	{
		if (ResValue.X * ResValue.Y > MaxResolution.X * MaxResolution.Y)
		{
			MaxResolution = ResValue;
		}
	}

	return MaxResolution;
}

FIntPoint UMGameSetting_Resolution::GetDesktopResolution()
{
	FDisplayMetrics Metrics;
	FDisplayMetrics::RebuildDisplayMetrics(Metrics);
	const FIntPoint PrimaryDisplayRes = FIntPoint(Metrics.PrimaryDisplayWidth, Metrics.PrimaryDisplayHeight);

	// Make sure it's available in supported resolutions so we don't set a resolution that's not available to select from UI
	if (!IsResolutionAvailableByValue(PrimaryDisplayRes))
	{
		return {};
	}

	return PrimaryDisplayRes;
}

FIntPoint UMGameSetting_Resolution::GetBestNativeResolution()
{
	const FIntPoint DesktopRes = GetDesktopResolution();
	if (DesktopRes.X > 0 && DesktopRes.Y > 0)
	{
		return DesktopRes;
	}

	return GetMaxSupportedResolution();
}

FName UMGameSetting_Resolution::MakeResolutionId(const FIntPoint& Resolution)
{
	return FName(Resolution.ToString());
}

bool UMGameSetting_Resolution::IsResolutionAvailableById(const FName ResolutionId)
{
	for (auto [ResId, ResValue] : ResolutionValueForOptionId)
	{
		if (ResId == ResolutionId)
		{
			return true;
		}
	}

	return false;
}

bool UMGameSetting_Resolution::IsResolutionAvailableByValue(const FIntPoint& Resolution)
{
	for (auto [ResId, ResValue] : ResolutionValueForOptionId)
	{
		if (ResValue == Resolution)
		{
			return true;
		}
	}

	return false;
}

FIntPoint UMGameSetting_Resolution::GetResolutionValueForId(const FName ResolutionId)
{
	if (!ResolutionValueForOptionId.Contains(ResolutionId))
	{
		return FIntPoint::NoneValue;
	}

	return ResolutionValueForOptionId[ResolutionId];
}

void UMGameSetting_Resolution::BindToFullscreenModeChanges()
{
	UMGameSettingsSubsystem* SettingsSubsystem = GetTypedOuter<UMGameSettingsSubsystem>();
	if (!IsValid(SettingsSubsystem))
	{
		return;
	}

	UMGameSetting_FullscreenMode* FullscreenModeSetting =
		Cast<UMGameSetting_FullscreenMode>(SettingsSubsystem->GetSettingObjectForClass(UMGameSetting_FullscreenMode::StaticClass()));
	if (!IsValid(FullscreenModeSetting))
	{
		return;
	}
	
	FullscreenModeSetting->OnSelectedValueChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnFullscreenModeSelectedValueChanged);
}

void UMGameSetting_Resolution::OnFullscreenModeSelectedValueChanged()
{
	SetSelectedOptionId(NativeResolutionOptionId);
	OnEditableStateMightChangedDelegate.Broadcast();
}
