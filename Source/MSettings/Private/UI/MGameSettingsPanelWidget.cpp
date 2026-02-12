// Copyright (c) Miknios. All rights reserved.


#include "UI/MGameSettingsPanelWidget.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "UI/MGameSettingListView.h"

void UMGameSettingsPanelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SettingsListView != nullptr)
	{
		SettingsListView->SetCategoryDefinitionAndInitializeList(SettingsCategoryDefinition);
	}
}

FReply UMGameSettingsPanelWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (SettingsListView == nullptr)
	{
		return FReply::Unhandled();
	}

	const UCommonInputSubsystem* InputSubsystem = GetInputSubsystem();
	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (TSharedPtr<SWidget> PrimarySlateWidget = SettingsListView->GetCachedWidget())
		{
			SettingsListView->NavigateToIndex(0);
			SettingsListView->SetSelectedIndex(0);

			return FReply::Handled();
		}
	}

	return FReply::Unhandled();
}
