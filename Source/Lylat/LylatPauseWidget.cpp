// Copyright (c) 2020 Team Project: Lylat. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish or distribute. This does not allow commercial distribution.
//
// This license does not cover any content made by any commercial entity.
//
// Under the category "content used without permission" falls any content regarding the "Star Fox" trademark.
// Star Fox is a registered trademark of Nintendo Co., Ltd.
// 
// Under the category "content used according to licensing" fall the Discord Game SDK and the Ultralight SDK.
// Discord is a registered trademark of Discord, Inc.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "LylatPauseWidget.h"
#include "LylatGameHUD.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "PauseMenuText"

void SLylatPauseWidget::Construct(const FArguments& inArgs)
{
	bCanSupportFocus = true;
	OwningHUD = inArgs._OwningHUD;
	
	const FMargin contentPadding	= FMargin(20.f, 10.f);
	const FMargin buttonPadding		= FMargin(10.f);

	const FText pauseTitleText		= LOCTEXT("PauseTitle", "Paused");
	const FText resumeButtonText	= LOCTEXT("ResumeButton", "Resume");
	const FText quitButtonText		= LOCTEXT("QuitToMenuButton", "Quit to menu");

	FSlateFontInfo pauseTextStyle	= FCoreStyle::Get().GetFontStyle("EmbossedText");
	pauseTextStyle.Size = 80.f;

	FSlateFontInfo buttonTextStyle	= FCoreStyle::Get().GetFontStyle("EmbossedText");
	buttonTextStyle.Size = 40.f;

	ChildSlot
	[
		SNew(SOverlay)

		// Widgets
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(contentPadding)
		[
			SNew(SVerticalBox)

			// Paused caption
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text(pauseTitleText)
				.Font(pauseTextStyle)
				.Justification(ETextJustify::Left)
			]

			// Resume Button
			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SLylatPauseWidget::OnResume)
				[
					SNew(STextBlock)
					.Text(resumeButtonText)
					.Font(buttonTextStyle)
					.Justification(ETextJustify::Center)
				]
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]

			// Quit to Menu Button
			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SLylatPauseWidget::OnQuit)
				[
					SNew(STextBlock)
					.Text(quitButtonText)
					.Font(buttonTextStyle)
					.Justification(ETextJustify::Center)
				]
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]
		]
	];
}

FReply SLylatPauseWidget::OnResume() const
{
	if (!OwningHUD.IsValid()) return FReply::Handled();

	OwningHUD->ShowHUD();
	OwningHUD->PlayerOwner->Pause();
	return FReply::Handled();
}

FReply SLylatPauseWidget::OnQuit() const
{
	if (!OwningHUD.IsValid()) return FReply::Handled();

	UGameplayStatics::OpenLevel(OwningHUD->PlayerOwner, "Initial");
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
