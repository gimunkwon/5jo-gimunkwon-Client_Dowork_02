#include "UI/InventorySlotWidget.h"

#include "PaperSprite.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Btn_InvenSlot)
	{
		Btn_InvenSlot->OnClicked.AddDynamic(this,&UInventorySlotWidget::OnButtonPressed);
	}
}

void UInventorySlotWidget::UpdateSlotImage(UPaperSprite* SpriteImage,FName SlotItemName)
{
	if (Image_Item && SpriteImage)
	{
		Image_Item->SetBrushResourceObject(SpriteImage);
	}
	if (!SlotItemName.IsNone())
	{
		ItemName = SlotItemName;
	}
}

void UInventorySlotWidget::OnButtonPressed()
{
	UE_LOG(LogTemp,Warning,TEXT("CurrentSlot Item Name was %s"),*ItemName.ToString());
}