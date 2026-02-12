// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MGameSettingsDeveloperSettings.generated.h"

class UMGameSettingsCollection;

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="M Game Settings"))
class MSETTINGS_API UMGameSettingsDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static UMGameSettingsDeveloperSettings* Get();

	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UMGameSettingsCollection> GameSettingsCollection;
};
