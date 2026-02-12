// Copyright (c) Miknios. All rights reserved.


#include "UI/MGameSettingWidget.h"

#include "CommonInputSubsystem.h"
#include "CommonRotator.h"
#include "CommonTextBlock.h"
#include "MGameSetting_Base.h"

void UMGameSettingWidget_Base::NativeOnEntryReleased()
{
	Setting = nullptr;
}

FReply UMGameSettingWidget_Base::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const UCommonInputSubsystem* InputSubsystem = GetInputSubsystem();
	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (const UWidget* PrimaryFocus = GetPrimaryGamepadFocusWidget())
		{
			const TSharedPtr<SWidget> WidgetToFocus = PrimaryFocus->GetCachedWidget();
			if (WidgetToFocus.IsValid())
			{
				return FReply::Handled().SetUserFocus(WidgetToFocus.ToSharedRef(), InFocusEvent.GetCause());
			}
		}
	}

	return FReply::Unhandled();
}

void UMGameSettingWidget_Base::SetSetting(UMGameSetting_Base& InSetting)
{
	Setting = &InSetting;

	Setting->OnAppliedDelegate.AddUniqueDynamic(this, &ThisClass::OnSettingApplied);
	Setting->OnSelectedValueChangedDelegate.AddUniqueDynamic(this, &ThisClass::OnSelectedValueChanged);
	Setting->OnEditableStateMightChangedDelegate.AddUniqueDynamic(this, &ThisClass::RefreshEditableState);

	if (Text_SettingName != nullptr)
	{
		Text_SettingName->SetText(InSetting.DisplayName);
	}
}

void UMGameSettingWidget_Base::OnSelectedValueChanged()
{
}

void UMGameSettingWidget_Base::OnSettingApplied()
{
}

void UMGameSettingWidget_Base::RefreshEditableState()
{
}

void UMGameSettingWidget_Discrete::SetSetting(UMGameSetting_Base& InSetting)
{
	DiscreteSetting = Cast<UMGameSetting_Discrete>(&InSetting);

	Super::SetSetting(InSetting);

	Refresh();
}

void UMGameSettingWidget_Discrete::RefreshEditableState()
{
	Super::RefreshEditableState();

	const bool bEditable = DiscreteSetting != nullptr && DiscreteSetting->IsAvailable();
	Rotator_SettingValue->SetIsEnabled(bEditable);
}

void UMGameSettingWidget_Discrete::OnSelectedValueChanged()
{
	Refresh();
}

void UMGameSettingWidget_Discrete::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Rotator_SettingValue->OnRotatedEvent.AddUObject(this, &ThisClass::HandleRotatorChangedValue);
}

void UMGameSettingWidget_Discrete::NativeOnEntryReleased()
{
	Super::NativeOnEntryReleased();

	DiscreteSetting = nullptr;
}

void UMGameSettingWidget_Discrete::Refresh()
{
	if (DiscreteSetting == nullptr)
	{
		return;
	}

	Rotator_SettingValue->PopulateTextLabels(DiscreteSetting->GetOptionDisplayNames());
	Rotator_SettingValue->SetSelectedItem(DiscreteSetting->GetSelectedOptionDataIndex());
	RefreshEditableState();
}

void UMGameSettingWidget_Discrete::HandleRotatorChangedValue(int OptionIndex, bool bUserInitiated)
{
	if (bUserInitiated)
	{
		DiscreteSetting->SetSelectedOptionIdByIndex(OptionIndex);
	}
}

void UMGameSettingWidget_Discrete::HandleOptionDecrease()
{
	Rotator_SettingValue->ShiftTextLeft();

	const int32 SelectedIndex = Rotator_SettingValue->GetSelectedIndex();

	if (SelectedIndex != INDEX_NONE)
	{
		DiscreteSetting->SetSelectedOptionIdByIndex(Rotator_SettingValue->GetSelectedIndex());
	}
}

void UMGameSettingWidget_Discrete::HandleOptionIncrease()
{
	Rotator_SettingValue->ShiftTextRight();

	const int32 SelectedIndex = Rotator_SettingValue->GetSelectedIndex();

	if (SelectedIndex != INDEX_NONE)
	{
		DiscreteSetting->SetSelectedOptionIdByIndex(Rotator_SettingValue->GetSelectedIndex());
	}
}
