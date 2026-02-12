// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MGameSettingsSaveObject.generated.h"

UCLASS(Config=GameUserSettings)
class MSETTINGS_API UMGameSettingsSaveObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	static UMGameSettingsSaveObject* Get();

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	static void Save();

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	static int32 GetSavedValueForSettingName(const FName SettingName);

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	static void SetSavedValueForSettingName(const FName SettingName, int32 Value);

	UPROPERTY(Config, EditAnywhere)
	bool bVsyncEnabled = true;

	UPROPERTY(Config, EditAnywhere)
	TMap<FName, int32> SettingValueForName;

	// UPROPERTY(Config, EditAnywhere)
	// int32 FoliageQuality = -1;

	// UPROPERTY(Config, EditAnywhere)
	// int32 ShadowsQuality = -1;

	// UPROPERTY(Config, EditAnywhere)
	// int32 PostProcessingQuality = -1;

	// UPROPERTY(Config, EditAnywhere)
	// int32 TextureQuality = -1;

	// UPROPERTY(Config, EditAnywhere)
	// int32 VisualEffectQuality = -1;

	// UPROPERTY(Config, EditAnywhere)
	// int32 ShadingQuality = -1;
};
