#include "UI/InventorySlotSelectContextWidget.h"

#include "Components/Button.h"
#include "Components/MenuAnchor.h"
#include "UI/InventoryWidget.h"

void UInventorySlotSelectContextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Btn_UseItem)
	{
		Btn_UseItem->OnClicked.AddDynamic(this, &UInventorySlotSelectContextWidget::OnUseButtonClicked);
	}
	if (Btn_DeleteItem)
	{
		Btn_DeleteItem->OnClicked.AddDynamic(this, &UInventorySlotSelectContextWidget::OnDeleteButtonClicked);
	}
	if (Btn_Close)
	{
		Btn_Close->OnClicked.AddDynamic(this, &UInventorySlotSelectContextWidget::OnCloseButtonClicked);
	}
}

void UInventorySlotSelectContextWidget::OnUseButtonClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("아이템 사용!"));
}

void UInventorySlotSelectContextWidget::OnCloseButtonClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("컨텍스트 메뉴를 닫습니다..."));
	
	if (OnCloseButton.IsBound())
	{
		OnCloseButton.Broadcast();
	}
}

void UInventorySlotSelectContextWidget::OnDeleteButtonClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("아이템 제거!"));
}
