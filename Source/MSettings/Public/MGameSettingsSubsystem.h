// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MGameSettingsSubsystem.generated.h"

class UMGameSetting_Base;
class UMGameSettingsCollection;

UCLASS()
class MSETTINGS_API UMGameSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// ~ UGameInstanceSubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// ~ UGameInstanceSubsystem
	
	UFUNCTION(BlueprintCallable, Category = GameSettings)
	UMGameSetting_Base* GetSettingObjectForClass(TSubclassOf<UMGameSetting_Base> SettingClass);

protected:
	void InitializeSettings();

	UPROPERTY(Transient, VisibleAnywhere)
	TObjectPtr<UMGameSettingsCollection> GameSettingsCollection;

	UPROPERTY(Transient, VisibleAnywhere)
	TArray<TObjectPtr<UMGameSetting_Base>> SettingObjects;
};
