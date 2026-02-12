// Copyright (c) Miknios. All rights reserved.


#include "MGameSetting_Base.h"

#include "MGameSettingsSaveObject.h"
#include "GameFramework/GameUserSettings.h"

void UMGameSetting_Base::ApplyAndSave()
{
	if (bSuppressApply)
	{
		return;
	}
	
	Apply_Implementation();
	OnAppliedDelegate.Broadcast();

	UMGameSettingsSaveObject::Save();

	UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
	if (GameUserSettings != nullptr)
	{
		GameUserSettings->SaveSettings();
	}
}

void UMGameSetting_Base::RevertSelectedValueToSavedOrDefault(const bool bApply = true)
{
	bSuppressApply = true;
	SelectSavedOrDefaultValue();
	bSuppressApply = false;

	if (bApply)
	{
		ApplyAndSave();
	}
}

void UMGameSetting_Base::RevertSelectedValueToDefault(const bool bApply = true)
{
	bSuppressApply = true;
	SelectDefaultValue();
	bSuppressApply = false;

	if (bApply)
	{
		ApplyAndSave();
	}
}

void UMGameSetting_Base::Initialize()
{
	Initialize_Implementation();

	RevertSelectedValueToSavedOrDefault(true);
}

UGameUserSettings* UMGameSetting_Base::GetGameUserSettings()
{
	if (!IsValid(GEngine))
	{
		return nullptr;
	}
	
	return GEngine->GetGameUserSettings();
}

UMGameSettingsSaveObject* UMGameSetting_Base::GetGameSettingsSaveObject()
{
	return UMGameSettingsSaveObject::Get();
}

void UMGameSetting_Base::Initialize_Implementation()
{
}

TArray<FName> UMGameSetting_Discrete_OptionData::GetPossibleValues() const
{
	UMGameSetting_Discrete* SettingOuter = GetTypedOuter<UMGameSetting_Discrete>();
	return SettingOuter->GetPossibleOptionIds();
}

FName UMGameSetting_Discrete::GetSelectedOptionId() const
{
	return SelectedOptionId;
}

void UMGameSetting_Discrete::SetSelectedOptionId(const FName NewId)
{
	SelectedOptionId = NewId;
	OnSelectedValueChangedDelegate.Broadcast();

	if (ApplyMode == ESettingApplyMode::Realtime)
	{
		ApplyAndSave();
	}
}

void UMGameSetting_Discrete::SetSelectedOptionIdByIndex(const int OptionIndex)
{
	if (!OptionDataArray.IsValidIndex(OptionIndex))
	{
		return;
	}

	SetSelectedOptionId(OptionDataArray[OptionIndex]->ValueId);
}

int32 UMGameSetting_Discrete::GetSelectedOptionDataIndex() const
{
	for (int i = 0; i < OptionDataArray.Num(); ++i)
	{
		const UMGameSetting_Discrete_OptionData* Option = OptionDataArray[i];
		if (Option == nullptr)
		{
			continue;
		}

		if (Option->ValueId == SelectedOptionId)
		{
			return i;
		}
	}

	return INDEX_NONE;
}

TArrayView<const TObjectPtr<UMGameSetting_Discrete_OptionData>> UMGameSetting_Discrete::GetOptions() const
{
	return OptionDataArray;
}

TArray<FText> UMGameSetting_Discrete::GetOptionDisplayNames() const
{
	TArray<FText> DisplayNames;
	DisplayNames.Reserve(OptionDataArray.Num());
	for (const TObjectPtr<UMGameSetting_Discrete_OptionData> Option : OptionDataArray)
	{
		DisplayNames.Emplace(Option->DisplayName);
	}

	return DisplayNames;
}
