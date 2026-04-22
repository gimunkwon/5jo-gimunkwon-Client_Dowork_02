#include "UI/InventoryInfoWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/MyPlayer.h"
#include "Player/Controller/MyPlayerControlloer.h"
#include "Player/Inventory/MyPlayerInventory.h"

void UInventoryInfoWidget::UpdateItemInfo(FName SelectedItemName,UImage* SelectedImage)
{
	if (AMyPlayerControlloer* PC = Cast<AMyPlayerControlloer>(GetOwningPlayer()))
	{
		if (AMyPlayer* MyOwner = Cast<AMyPlayer>(PC->GetPawn()))
		{
			if (UMyPlayerInventory* OwnerInver = MyOwner->GetInventory())
			{
				UE_LOG(LogTemp,Warning,TEXT("아이템 정보 갱신중..."));
				
				if (OwnerInver->ItemInfo.Find(SelectedItemName))
				{
					if (Text_ItemName)
					{
						Text_ItemName->SetText(FText::FromName(SelectedItemName));
					}
					if (Text_ItemDescription)
					{
						Text_ItemDescription->SetText(*OwnerInver->ItemInfo.Find(SelectedItemName));
					}
					if (Image_Item)
					{
						Image_Item->SetBrushResourceObject(SelectedImage->GetBrush().GetResourceObject());
					}
				}
			}
		}
	}
}
