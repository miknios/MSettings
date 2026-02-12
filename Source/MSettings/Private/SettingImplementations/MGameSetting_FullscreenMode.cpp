// Copyright (c) Miknios. All rights reserved.


#include "SettingImplementations/MGameSetting_FullscreenMode.h"

#include "GameFramework/GameUserSettings.h"

void UMGameSetting_FullscreenMode::Initialize_Implementation()
{
	Super::Initialize_Implementation();
}

void UMGameSetting_FullscreenMode::Apply_Implementation()
{
	UGameUserSettings* GameUserSettings = GetGameUserSettings();
	if (!IsValid(GameUserSettings))
	{
		return;
	}

	int32 SelectedOptionValue = GetPossibleOptionIds().IndexOfByKey(GetSelectedOptionId());
	if (SelectedOptionValue == INDEX_NONE)
	{
		SelectedOptionValue = UGameUserSettings::GetDefaultWindowMode();
	}

	GameUserSettings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(SelectedOptionValue));
	GameUserSettings->ApplyResolutionSettings(true);
}

void UMGameSetting_FullscreenMode::SelectSavedOrDefaultValue()
{
	const UGameUserSettings* GameUserSettings = GetGameUserSettings();
	if (!IsValid(GameUserSettings))
	{
		return;
	}

	const EWindowMode::Type SavedValue = GameUserSettings->GetFullscreenMode();
	SetSelectedOptionId(GetOptionIdForValue(SavedValue));
}

void UMGameSetting_FullscreenMode::SelectDefaultValue()
{
	const EWindowMode::Type DefaultMode = UGameUserSettings::GetDefaultWindowMode();
	SetSelectedOptionId(GetOptionIdForValue(DefaultMode));
}

TArray<FName> UMGameSetting_FullscreenMode::GetPossibleOptionIds()
{
	// In order defined in EWindowMode::Type, it seems consistent between unreal classes
	return
	{
		TEXT("ExclusiveFullscreen"),
		TEXT("WindowedFullscreen"),
		TEXT("Windowed")
	};
}

FName UMGameSetting_FullscreenMode::GetOptionIdForValue(const int32 FullscreenModeValue)
{
	TArray<FName> PossibleOptions = GetPossibleOptionIds();
	if (!ensureAlways(PossibleOptions.IsValidIndex(FullscreenModeValue)))
	{
		return TEXT("WindowedFullscreen");
	}

	return PossibleOptions[FullscreenModeValue];
}
