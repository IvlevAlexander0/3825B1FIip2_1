#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
typedef struct {
    char code[5];
    char name[50];
    int price;
    int sale;
} Product;
typedef struct {
    Product product[50];
    int count[50];
    int currentCashCheckMembersCount;
} CashCheck;
void printProductInfo(Product product) {
    printf("\nProduct info:\ncode - %s\nname - %s\nprice - %d\nsale - %d\n\n\n",
        product.code, product.name, product.price, product.sale);
}
void printCashCheck(CashCheck check) {
    printf("\nCashCheck:\n\n");
    int totalCashCheckPriceWithSale = 0;
    int totalCashCheckPriceWithoutSale = 0;
    for (int i = 0; i < check.currentCashCheckMembersCount; ++i)
    {
        int productPriceWithSale = check.product[i].price * (100 - check.product[i].sale) / 100;
        int checkMembewrPriceWithSale = productPriceWithSale * check.count[i];
        totalCashCheckPriceWithoutSale += check.product[i].price * check.count[i];
        totalCashCheckPriceWithSale += checkMembewrPriceWithSale;
        printf("CashCheck member:\nname - %s\nprice - %d\ncount - %d\nsale - %d\nproduct price with sale - %d\ntotal price with sale - %d\n\n",
            check.product[i].name, check.product[i].price, check.count[i], check.product[i].sale, productPriceWithSale, checkMembewrPriceWithSale);
    }
    printf("The total cost of the product: %d\n", totalCashCheckPriceWithoutSale);
    printf("Total discount: %d\n", totalCashCheckPriceWithoutSale - totalCashCheckPriceWithSale);
    printf("Total amount to be paid: %d\n\n", totalCashCheckPriceWithSale);
}
int checkProductCode(char code[]) {
    if (strlen(code) != 4)
    {
        printf("The code length is not equal to 4\n");
        return 0;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (code[i] < '0' || code[i] > '9')
        {
            printf("Incorrect character in the code\n");
            return 0;
        }
    }
    return 1;
}
int checkExistenceCode(char code[], Product* curProd, int prodCount) {
    if (findProductByCode(curProd, prodCount, code) != -1)
    {
        printf("Product with this code already exists\n");
        return 1;
    }
    return 0;
}
int findProductByCode(Product* products, int currentProductCount, char inputCode[]) {
    int isEqual = 1;
    int productNum = -1;
    for (int i = 0; i < currentProductCount; ++i)
    {
        isEqual = 1;
        for (int j = 0; j < 4; ++j)
        {
            if (inputCode[j] != products[i].code[j])
            {
                isEqual = 0;
                break;
            }
        }
        if (isEqual == 1)
        {
            productNum = i;
            break;
        }
    }
    return productNum;
}
Product addProduct(Product* products, int currentProductCount) {
    Product userProduct;
    char userProductCode[6];
    printf("Enter the code (4 numbers)\n");
    scanf("%5s", &userProductCode);
    int isCodeCorrect = checkProductCode(userProductCode);
    int isCodeExist = checkExistenceCode(userProductCode, products, currentProductCount);
    while (!isCodeCorrect || isCodeExist)
    {
        printf("Enter the code (4 numbers)\n");
        clearInputBuffer();
        scanf("%5s", &userProductCode);
        isCodeCorrect = checkProductCode(userProductCode);
        isCodeExist = checkExistenceCode(userProductCode, products, currentProductCount);
    }
    strcpy(userProduct.code, userProductCode);
    printf("Enter the product name\n");
    clearInputBuffer();
    scanf("%50s", &userProduct.name);
    printf("Enter the price (in rubles without kopecks)\n");
    clearInputBuffer();
    scanf("%d", &userProduct.price);
    printf("Enter a discount (from 1 to 50)\n");
    clearInputBuffer();
    scanf("%d", &userProduct.sale);
    while (userProduct.sale < 1 || userProduct.sale  > 50)
    {
        printf("Error. The discount must be between 1 and 50\n");
        clearInputBuffer();
        scanf("%d", &userProduct.sale);
    }
    return userProduct;
}
void scanProduct(Product* products, int currentProductCount) {
    char inputCode[6];
    printf("Enter the code (4 numbers)\n");
    scanf("%5s", &inputCode);
    int isCodeCorrect = checkProductCode(inputCode);
    while (!isCodeCorrect)
    {
        printf("Enter the code (4 numbers)\n");
        clearInputBuffer();
        scanf("%5s", &inputCode);
        isCodeCorrect = checkProductCode(inputCode);
    }
    int productNum = findProductByCode(products, currentProductCount, &inputCode);
    if (productNum != -1)
    {
        printProductInfo(products[productNum]);
    }
    else {
        printf("Product with code %s not found\n", inputCode);
    }
}
CashCheck addProductToCashCheck(Product* products, int currentProductCount, CashCheck check) {
    char inputCode[6];
    printf("Enter the product code\n");
    clearInputBuffer();
    scanf("%5s", &inputCode);
    int isCodeCorrect = checkProductCode(inputCode);
    while (!isCodeCorrect)
    {
        printf("Enter the code (4 numbers)\n");
        clearInputBuffer();
        scanf("%5s", &inputCode);
        isCodeCorrect = checkProductCode(inputCode);
    }
    int productNum = findProductByCode(products, currentProductCount, &inputCode);
    int productInCheckNum = findProductByCode(check.product, check.currentCashCheckMembersCount, &inputCode);
    if (productNum != -1) {
        if (productInCheckNum != -1)
        {
            check.count[productInCheckNum]++;
        }
        else
        {
            check.product[check.currentCashCheckMembersCount] = products[productNum];
            check.count[check.currentCashCheckMembersCount] = 1;
            check.currentCashCheckMembersCount++;
        }
    }
    else
    {
        printf("Product with code %s not found\n", inputCode);
    }
    return check;
}
int getProgrammMode() {
    int operationNumber = 0;
    printf("Select programm mode:\n");
    scanf("%d", &operationNumber);
    return operationNumber;
}
int main() {
    int programmMode = 0;
    int currentProductCount = 5;
    int currentCashCheckCount = 0;
    Product product1 = { "1122","banana",200,10 };
    Product product2 = { "1133","apple",350,25 };
    Product product3 = { "1144","milk",132,3 };
    Product product4 = { "1155","bread",40,2 };
    Product product5 = { "1166","sausage",1320,47 };
    Product products[50] = { product1, product2, product3, product4, product5 };
    CashCheck check;
    check.currentCashCheckMembersCount = 0;
    printf("Operations:\n");
    printf("1.Adding a product description to the program while it is running\n");
    printf("2.Scanning a product and displaying its description\n");
    printf("3.Scanning an item and adding it to the receipt\n");
    printf("4.Generate a final check\n");
    printf("5.Start generating a new check\n");
    printf("0.Exit the programm\n");
    programmMode = getProgrammMode();
    while (1) {
        switch (programmMode) {
        case 0:
            printf("Exit the programm\n");
            return 0;
        case 1:
        {
            products[currentProductCount] = addProduct(products, currentProductCount);
            currentProductCount++;
            break;
        }
        case 2:
            scanProduct(&products, currentProductCount);
            break;
        case 3:
            check = addProductToCashCheck(&products, currentProductCount, check);
            break;
        case 4:
            printCashCheck(check);
            break;
        case 5:
            check.currentCashCheckMembersCount = 0;
            break;
        default:
        {
            for (int i = 0; i < currentProductCount; ++i) {
                printProductInfo(products[i]);
            }
        }
        clearInputBuffer();
        programmMode = getProgrammMode();
    }
}