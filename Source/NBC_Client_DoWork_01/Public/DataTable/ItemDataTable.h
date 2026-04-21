#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "ItemdataTable.generated.h"

USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="RowData")
	FName ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="RowData")
	TObjectPtr<UPaperSprite> ItemImage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="RowData")
	FText ItemDescription;
};
