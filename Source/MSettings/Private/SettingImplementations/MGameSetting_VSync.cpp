// Copyright (c) Miknios. All rights reserved.


#include "SettingImplementations/MGameSetting_VSync.h"

#include "MGameSettingsSaveObject.h"
#include "GameFramework/GameUserSettings.h"

void UMGameSetting_VSync::Apply_Implementation()
{
	if (!IsValid(GEngine))
	{
		return;
	}

	if (UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings())
	{
		const bool bVsyncEnabled = GetSelectedOptionId() == TEXT("on");
		GameUserSettings->SetVSyncEnabled(bVsyncEnabled);
		GameUserSettings->ApplySettings(false);

		UMGameSettingsSaveObject::Get()->bVsyncEnabled = bVsyncEnabled;
	}
}

void UMGameSetting_VSync::SelectSavedOrDefaultValue()
{
	const FName NameFromSaveObject = UMGameSettingsSaveObject::Get()->bVsyncEnabled ? TEXT("on") : TEXT("off");
	SetSelectedOptionId(NameFromSaveObject);
}

void UMGameSetting_VSync::SelectDefaultValue()
{
	SetSelectedOptionId(TEXT("off"));
}

TArray<FName> UMGameSetting_VSync::GetPossibleOptionIds()
{
	return {
		TEXT("on"),
		TEXT("off")
	};
}
