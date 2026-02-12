// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MGameSettingsPanelWidget.generated.h"

class UMSettingsCategoryDefinition;
class UMGameSetting_Base;
class UMGameSettingListView;

UCLASS()
class MSETTINGS_API UMGameSettingsPanelWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	// ~ UUserWidget
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	// ~ UUserWidget

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Settings")
	TObjectPtr<UMSettingsCategoryDefinition> SettingsCategoryDefinition;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMGameSettingListView> SettingsListView;
	
	UPROPERTY(Transient)
	TArray<TObjectPtr<UMGameSetting_Base>> SettingsDisplayed;
};
