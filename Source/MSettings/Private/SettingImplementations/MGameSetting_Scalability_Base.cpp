// Copyright (c) Miknios. All rights reserved.


#include "SettingImplementations/MGameSetting_Scalability_Base.h"

#include "MGameSettingsSaveObject.h"
#include "GameFramework/GameUserSettings.h"

UMGameSetting_Scalability_Base::UMGameSetting_Scalability_Base()
{
	ApplyMode = ESettingApplyMode::Realtime;
}

void UMGameSetting_Scalability_Base::Apply_Implementation()
{
	if (UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings())
	{
		ApplyScalabilitySetting(GameUserSettings, UMGameSettingsSaveObject::Get());
		UMGameSettingsSaveObject::SetSavedValueForSettingName(ScalabilitySettingName, GetSelectedValue());
		GameUserSettings->ApplyNonResolutionSettings();
	}
}

void UMGameSetting_Scalability_Base::SelectSavedOrDefaultValue()
{
	const int32 SavedValue = UMGameSettingsSaveObject::GetSavedValueForSettingName(ScalabilitySettingName);

	if (SavedValue == -1)
	{
		SelectDefaultValue();
		return;
	}

	const FName SavedOptionId = GetOptionIdForValue(SavedValue);
	SetSelectedOptionId(SavedOptionId);
}

void UMGameSetting_Scalability_Base::SelectDefaultValue()
{
	SetSelectedOptionId(TEXT("high"));
}

TArray<FName> UMGameSetting_Scalability_Base::GetPossibleOptionIds()
{
	return {TEXT("low"), TEXT("medium"), TEXT("high"), TEXT("epic"), TEXT("cinematic")};
}

int32 UMGameSetting_Scalability_Base::GetSavedValue() const
{
	return UMGameSettingsSaveObject::GetSavedValueForSettingName(ScalabilitySettingName);
}

FName UMGameSetting_Scalability_Base::GetSavedOptionId() const
{
	return GetOptionIdForValue(GetSavedValue());
}

int32 UMGameSetting_Scalability_Base::GetValueForOptionId(const FName OptionId)
{
	int32 QualityLevel = 2;
	if (OptionId == TEXT("low"))
	{
		QualityLevel = 0;
	}
	else if (OptionId == TEXT("medium"))
	{
		QualityLevel = 1;
	}
	else if (OptionId == TEXT("high"))
	{
		QualityLevel = 2;
	}
	else if (OptionId == TEXT("epic"))
	{
		QualityLevel = 3;
	}
	else if (OptionId == TEXT("cinematic"))
	{
		QualityLevel = 4;
	}

	return QualityLevel;
}

FName UMGameSetting_Scalability_Base::GetOptionIdForValue(const int32 Value)
{
	switch (Value)
	{
	case 0:
		return TEXT("low");
	case 1:
		return TEXT("medium");
	case 2:
		return TEXT("high");
	case 3:
		return TEXT("epic");
	case 4:
		return TEXT("cinematic");
	default: ;
		return TEXT("high");
	}
}

int32 UMGameSetting_Scalability_Base::GetSelectedValue() const
{
	return GetValueForOptionId(GetSelectedOptionId());
}

void UMGameSetting_Scalability_Base::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                            UMGameSettingsSaveObject* SettingsContainer)
{
}

UMGameSetting_Scalability_Foliage::UMGameSetting_Scalability_Foliage()
{
	ScalabilitySettingName = TEXT("Foliage");
}

void UMGameSetting_Scalability_Foliage::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                               UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetFoliageQuality(GetSelectedValue());
}

UMGameSetting_Scalability_Shadows::UMGameSetting_Scalability_Shadows()
{
	ScalabilitySettingName = TEXT("Shadows");
}

void UMGameSetting_Scalability_Shadows::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                               UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetShadowQuality(GetSelectedValue());
}

UMGameSetting_Scalability_PostProcessing::UMGameSetting_Scalability_PostProcessing()
{
	ScalabilitySettingName = TEXT("PostProcessing");
}

void UMGameSetting_Scalability_PostProcessing::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                                      UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetPostProcessingQuality(GetSelectedValue());
}

UMGameSetting_Scalability_Textures::UMGameSetting_Scalability_Textures()
{
	ScalabilitySettingName = TEXT("Textures");
}

void UMGameSetting_Scalability_Textures::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                                UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetTextureQuality(GetSelectedValue());
}

UMGameSetting_Scalability_Effects::UMGameSetting_Scalability_Effects()
{
	ScalabilitySettingName = TEXT("Effects");
}

void UMGameSetting_Scalability_Effects::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                               UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetVisualEffectQuality(GetSelectedValue());
}

UMGameSetting_Scalability_Shading::UMGameSetting_Scalability_Shading()
{
	ScalabilitySettingName = TEXT("Shading");
}

void UMGameSetting_Scalability_Shading::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                               UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetShadingQuality(GetSelectedValue());
}

UMGameSetting_Scalability_ViewDistance::UMGameSetting_Scalability_ViewDistance()
{
	ScalabilitySettingName = TEXT("ViewDistance");
}

void UMGameSetting_Scalability_ViewDistance::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                                    UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetViewDistanceQuality(GetSelectedValue());
}

UMGameSetting_Scalability_AntiAliasing::UMGameSetting_Scalability_AntiAliasing()
{
	ScalabilitySettingName = TEXT("AntiAliasing");
}

void UMGameSetting_Scalability_AntiAliasing::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetAntiAliasingQuality(GetSelectedValue());
}

UMGameSetting_Scalability_GlobalIllumination::UMGameSetting_Scalability_GlobalIllumination()
{
	ScalabilitySettingName = TEXT("GlobalIllumination");
}

void UMGameSetting_Scalability_GlobalIllumination::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                                          UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetGlobalIlluminationQuality(GetSelectedValue());
}

UMGameSetting_Scalability_Reflections::UMGameSetting_Scalability_Reflections()
{
	ScalabilitySettingName = TEXT("Reflections");
}

void UMGameSetting_Scalability_Reflections::ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
                                                                                   UMGameSettingsSaveObject* SettingsContainer)
{
	GameUserSettings->SetReflectionQuality(GetSelectedValue());
}
