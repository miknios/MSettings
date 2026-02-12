// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MGameSetting_Base.h"
#include "MGameSetting_Scalability_Base.generated.h"

class UMGameSettingsSaveObject;

UCLASS(Abstract)
class MSETTINGS_API UMGameSetting_Scalability_Base : public UMGameSetting_Discrete
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Base();

	// ~ UMGameSetting_Base
	virtual void Apply_Implementation() override;
	virtual void SelectSavedOrDefaultValue() override;
	virtual void SelectDefaultValue() override;
	// ~ UMGameSetting_Base

	// ~ UMGameSetting_Discrete
	virtual TArray<FName> GetPossibleOptionIds() override;
	// ~ UMGameSetting_Discrete

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	static int32 GetValueForOptionId(const FName OptionId);

	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	static FName GetOptionIdForValue(const int32 Value);

	// Returns value saved in UGameSettingsSaveObject .ini file. This is the value that is applied and saved.
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	int32 GetSavedValue() const;

	// Returns value saved in UGameSettingsSaveObject .ini file. This is the value that is applied and saved. 
	// Translated to OptionId name (eg. low, medium, high, epic, cinematic)
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	FName GetSavedOptionId() const;

	// Returns value currently selected by user. This is the value that is visible in UI, but might not yet be applied
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	int32 GetSelectedValue() const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void ApplyScalabilitySetting(UGameUserSettings* GameUserSettings, UMGameSettingsSaveObject* SettingsContainer);

	// Used to identify setting in .ini file so we don't have to create a variable for each setting
	UPROPERTY(EditDefaultsOnly)
	FName ScalabilitySettingName;
};

UCLASS(Abstract)
class UMGameSetting_Scalability_Foliage : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Foliage();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_Shadows : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Shadows();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_PostProcessing : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_PostProcessing();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_Textures : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Textures();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_Effects : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Effects();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_Shading : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Shading();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_ViewDistance : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_ViewDistance();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_AntiAliasing : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_AntiAliasing();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_GlobalIllumination : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_GlobalIllumination();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};

UCLASS(Abstract)
class UMGameSetting_Scalability_Reflections : public UMGameSetting_Scalability_Base
{
	GENERATED_BODY()

public:
	UMGameSetting_Scalability_Reflections();

	// ~ UMGameSetting_Scalability_Base
	virtual void ApplyScalabilitySetting_Implementation(UGameUserSettings* GameUserSettings,
	                                                    UMGameSettingsSaveObject* SettingsContainer) override;
	// ~ UMGameSetting_Scalability_Base
};
