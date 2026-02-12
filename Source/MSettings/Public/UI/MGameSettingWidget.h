// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "MGameSettingWidget.generated.h"

class UCommonButtonBase;
class UCommonRotator;
class UMGameSetting_Discrete;
class UCommonTextBlock;
class UMGameSetting_Base;

UCLASS(Abstract, NotBlueprintable, meta = (Category = "Settings", DisableNativeTick))
class MSETTINGS_API UMGameSettingWidget_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	// ~ IUserObjectListEntry
	virtual void NativeOnEntryReleased() override;
	// ~ IUserObjectListEntry

	// ~ UCommonUserWidget
	// Focus transitioning to subwidgets for the gamepad
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	// ~ UCommonUserWidget

	UFUNCTION(BlueprintImplementableEvent)
	UWidget* GetPrimaryGamepadFocusWidget();

	virtual void SetSetting(UMGameSetting_Base& InSetting);

	UFUNCTION()
	virtual void OnSelectedValueChanged();
	
	UFUNCTION()
	virtual void OnSettingApplied();
	
	UFUNCTION()
	virtual void RefreshEditableState();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Text_SettingName;

	UPROPERTY()
	TObjectPtr<UMGameSetting_Base> Setting;
};

UCLASS(Abstract, Blueprintable, meta = (Category = "Settings", DisableNativeTick))
class UMGameSettingWidget_Discrete : public UMGameSettingWidget_Base
{
	GENERATED_BODY()

public:
	// ~ UMGameSettingWidget_Base
	virtual void SetSetting(UMGameSetting_Base& InSetting) override;
	virtual void RefreshEditableState() override;
	virtual void OnSelectedValueChanged() override;
	// ~ UMGameSettingWidget_Base

	// ~ UUserWidget
	virtual void NativeOnInitialized() override;
	// ~ UUserWidget

	// ~ IUserObjectListEntry
	virtual void NativeOnEntryReleased() override;
	// ~ IUserObjectListEntry

protected:
	void Refresh();

	// ~ Handlers
	void HandleRotatorChangedValue(int OptionIndex, bool bUserInitiated);
	void HandleOptionDecrease();
	void HandleOptionIncrease();
	// ~ Handlers

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UMGameSetting_Discrete> DiscreteSetting;

	// ~ Default Widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonRotator> Rotator_SettingValue;
	// ~ Default Widgets
};
