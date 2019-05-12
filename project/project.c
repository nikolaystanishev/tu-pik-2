#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int save_products(char*, struct products*);
struct products* find_by_id(struct products*, long);
void delete_by_id(struct products*, long);
int add_new_product(struct products*);
int change_quantity_of_product(struct products*);
int print_product_with_id(struct products*);

int main() {
    char filename[100];
    printf("Provide filename: ");
    scanf("%s", filename);

    struct products *products = NULL;
    products = malloc(sizeof(struct products));
    if (products == NULL) {
        perror("malloc");
        return -1;
    }
    products->next = NULL;
    if (load_products(filename, products) == -1) {
        return -1;
    }

    struct products *ip = products->next;
    while(1) {
        if (ip == NULL) {
            break;
        }
        printf("%ld - %s\n", ip->val.id, ip->val.name);
        ip = ip->next;
    }
    printf("----------------------------------\n");

    int option = 0;
    int exit_flag = 1;
    while(exit_flag) {
        // system("@cls||clear");

        printf("1. Add new product\n");
        printf("2. Change quantity of product\n");
        printf("3. Show all products\n");
        printf("4. Show info for product\n");
        printf("5. Exit\n");

        printf("Insert option: ");
        if (scanf("%d", &option) == EOF) {
            break;
        }

        switch (option) {
            case 1:
                if (add_new_product(products)) {
                    return -1;
                }
                break;
            case 2:
                if (change_quantity_of_product(products)) {
                    return -1;
                }
                break;
            case 3:
                /* code */
                break;
            case 4:
                if (print_product_with_id(products)) {
                    return -1;
                }
                break;
            case 5:
                exit_flag = 0;
                break;
            default:
                break;
        }

        printf("Continue");
        char ch;
        scanf("%c",&ch);
        getchar();
    }

    if (save_products(filename, products)) {
        return -1;
    }

    return 0;
}

int load_products(char *filename, struct products *products) {
    FILE *fp = NULL;

    if ((fp = fopen(filename, "rb")) == NULL) {
        perror("fopen");
        return -1;
    }

    struct products *prev_products = products;
    struct products *curr_products = NULL;
    while (1) {
        struct product product;
        
        if (fread(&product, sizeof(struct product), 1, fp) != 1) {
            if (feof(fp)) {
                break;
            }
            fclose(fp);
            perror("fread");
            return -1;
        }

        curr_products = malloc(sizeof(struct products));
        if (curr_products == NULL) {
            perror("malloc");
            return -1;
        }
        curr_products->val = product;
        curr_products->next = NULL;

        prev_products->next = curr_products;
        prev_products = curr_products;
    }

    fclose(fp);

    return 0;
}

int save_products(char* filename, struct products *products) {
    FILE *fp  = NULL;

    if ((fp = fopen(filename, "wb")) == NULL) {
        perror("fopen");
        return -1;
    }

    while (1) {
        products = products->next;
        if (products == NULL) {
            break;
        }

        if (fwrite(&products->val, sizeof(struct product), 1, fp) != 1) {
            fclose(fp);
            perror("fwrite");
            return -1;
        }
    }

    return 0;
}

struct products* find_by_id(struct products *products, long id) {
    struct products *iterate_products = products->next;
    while(1) {
        if (iterate_products == NULL) {
            break;
        }

        if (iterate_products->val.id == id) {
            return iterate_products;
        }

        iterate_products = iterate_products->next;
    }

    return NULL;
}

void delete_by_id(struct products *products, long id) {
    struct products *prev_products = products;
    struct products *iterate_products = products->next;
    while(1) {
        if (iterate_products == NULL) {
            break;
        }

        if (iterate_products->val.id == id) {
            prev_products->next = iterate_products->next;
            break;
        }

        iterate_products = iterate_products->next;
        prev_products = prev_products->next;
    }
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
    scanf("%f", &price);
    printf("Insert quantity: ");
    scanf("%d", &quantity);
    printf("Insert date: ");
    scanf("%s", date);

    struct product product;
    product.id = id;
    strcat(product.name, name);
    product.price = price;
    product.quantity = quantity;
    strcat(product.date, date);

    struct products *last_products = products;
    while(last_products->next) {
        last_products = last_products->next;
    }

    struct products *next_products = NULL;
    next_products = malloc(sizeof(struct products));
    if (next_products == NULL) {
        perror("malloc");
        return -1;
    }
    next_products->val = product;
    next_products->next = NULL;

    last_products->next = next_products;

    return 0;
}

int print_product_with_id(struct products* products) {
    long id;
    printf("Insert id: ");
    scanf("%ld", &id);

    struct products *products_with_id = find_by_id(products, id);

    if (products_with_id == NULL) {
        printf("Missing product!\n");
    } else {
        printf("id: %ld\n", products_with_id->val.id);
        printf("name: %s\n", products_with_id->val.name);
        printf("price: %.2f\n", products_with_id->val.price);
        printf("quantity: %d\n", products_with_id->val.quantity);
        printf("date: %s\n", products_with_id->val.date);
    }

    return 0;
}

int change_quantity_of_product(struct products* products) {
    long id;
    printf("Insert id: ");
    scanf("%ld", &id);

    int quantity;
    printf("Insert quantity to change: ");
    scanf("%d", &quantity);

    struct products *products_with_id = find_by_id(products, id);

    if (products_with_id == NULL) {
        printf("Missing product!\n");
    } else {
        int new_quantity = products_with_id->val.quantity + quantity;
        if (new_quantity < 0) {
            printf("Quantity to change is bigger than product quantity!\n");
        } else if (new_quantity > 0) {
            products_with_id->val.quantity = new_quantity;
        } else if (new_quantity == 0) {
            delete_by_id(products, id);
        }
    }

    return 0;
}
