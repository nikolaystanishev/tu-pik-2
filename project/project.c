#include <stdio.h>
#include <string.h>

struct product {
    long id;
    char name[50];
    float price;
    int quantity;
    char date[11];
};

struct products {
    struct product val;    

    struct products *next;
};

int load_products(char*, struct products*);
int add_new_product(struct products*);
void find_last(struct products*, struct products*);

int main() {
    char filename[100];
    printf("Provide filename: ");
    scanf("%s", filename);

    struct products *products = NULL;
    if (load_products(filename, products)) {
        return -1;
    }

    int option = 0;
    int exit_flag = 1;
    while(exit_flag) {
        printf("1. Add new product");
        printf("2. Change quantity of product");
        printf("3. Show all products");
        printf("4. Show info for product");
        printf("5. Exit");

        scanf("%d", &option);

        switch (option) {
            case 1:
                if (add_new_product(products)) {
                    return -1;
                }
                break;
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            case 4:
                /* code */
                break;
            case 5:
                exit_flag = 0;
                break;
            default:
                break;
        }

        printf("Continue");
        getchar();
    }

    return 0;
}

int load_products(char *filename, struct products *products) {
    FILE *fp = NULL;

    if ((fp = fopen(filename, "rb")) == NULL) {
        perror("fopen");
        return -1;
    }

    struct products *curr_products = products;
    while (1) {
        struct product product;
        
        if (fread(&product, sizeof(struct product), 1, fp) != 1) {
            if (feof(fp)) {
                break;
            }
            perror("fwrite");
            fclose(fp);
            return -1;
        }

        curr_products->val = product;
        struct products *next_products = NULL;
        curr_products->next = next_products;
        curr_products = curr_products->next;
    }

    fclose(fp);

    return 0;
}

int add_new_product(struct products *products) {
    long id = 0;
    char name[50];
    float price;
    int quantity;
    char date[11];

    printf("Insert id: ");
    scanf("%ld", &id);
    printf("Insert name: ");
    scanf("%s", name);
    printf("Insert price: ");
    scanf("%.2f", &price);
    printf("Insert quantity: ");
    scanf("%d", &quantity);
    printf("Insert date: ");
    scanf("%s", &date);

    struct product product;
    product.id = id;
    strcat(product.name, name);
    product.price = price;
    product.quantity = quantity;
    strcat(product.date, date);

    struct products *last_products = NULL;
    find_last(products, last_products);

    struct products *next_products = NULL;
    next_products->val = product;
    last_products->next = next_products;

    return 0;
}

void find_last(struct products *products, struct products *last_products) {
    last_products = products;

    while(last_products->next) {
        last_products = last_products->next;
    }
}
