#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_USERS 100
#define MAX_PRODUCTS 100

// Structures
typedef struct User {
    int id;
    char name[50];
    struct User* next;
} User;

typedef struct Product {
    int id;
    char name[50];
    struct Product* next;
} Product;

typedef struct Graph {
    int adjacencyMatrix[MAX_USERS][MAX_PRODUCTS];
    int weights[MAX_USERS][MAX_PRODUCTS]; // Weights for recommendation scoring
} Graph;

// Function Prototypes
int hash(int id, int tableSize);
void addUser(User* userTable[], int tableSize, int id, char* name);
User* getUser(User* userTable[], int tableSize, int id);
void updateUser(User* userTable[], int tableSize, int id, char* newName);
void addProduct(Product* productTable[], int tableSize, int id, char* name);
Product* getProduct(Product* productTable[], int tableSize, int id);
void updateProduct(Product* productTable[], int tableSize, int id, char* newName);
void initializeGraph(Graph* graph);
void recordBrowsing(Graph* graph, int userId, int productId);
void recordPurchase(Graph* graph, int userId, int productId);
void retrieveHistory(Graph* graph, int userId, int numProducts, Product* productTable[]);
void recommendProducts(Graph* graph, int userId, int numProducts, Product* productTable[]);
int calculateRecommendationScore(Graph* graph, int userId, int productId);

void displayMenu();

int main() {
    // Initialize tables and graph
    User* userTable[MAX_USERS] = {NULL};
    Product* productTable[MAX_PRODUCTS] = {NULL};
    Graph graph;
    initializeGraph(&graph);

    int choice, userId, productId, tableSize = MAX_USERS;
    char name[50];

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add User
                printf("Enter User ID (0 to %d): ", MAX_USERS - 1);
                scanf("%d", &userId);
                if (userId < 0 || userId >= MAX_USERS) {
                    printf("Invalid User ID.\n");
                    break;
                }
                printf("Enter User Name: ");
                scanf("%s", name);
                addUser(userTable, tableSize, userId, name);
                printf("User added successfully.\n");
                break;

            case 2: // Add Product
                printf("Enter Product ID (0 to %d): ", MAX_PRODUCTS - 1);
                scanf("%d", &productId);
                if (productId < 0 || productId >= MAX_PRODUCTS) {
                    printf("Invalid Product ID.\n");
                    break;
                }
                printf("Enter Product Name: ");
                scanf("%s", name);
                addProduct(productTable, tableSize, productId, name);
                printf("Product added successfully.\n");
                break;

            case 3: // Track Browsing History
                printf("Enter User ID (0 to %d): ", MAX_USERS - 1);
                scanf("%d", &userId);
                printf("Enter Product ID (0 to %d): ", MAX_PRODUCTS - 1);
                scanf("%d", &productId);
                if (userId < 0 || userId >= MAX_USERS || productId < 0 || productId >= MAX_PRODUCTS) {
                    printf("Invalid User or Product ID.\n");
                    break;
                }
                recordBrowsing(&graph, userId, productId);
                printf("Browsing history recorded.\n");
                break;

            case 4: // Track Purchase History
                printf("Enter User ID (0 to %d): ", MAX_USERS - 1);
                scanf("%d", &userId);
                printf("Enter Product ID (0 to %d): ", MAX_PRODUCTS - 1);
                scanf("%d", &productId);
                if (userId < 0 || userId >= MAX_USERS || productId < 0 || productId >= MAX_PRODUCTS) {
                    printf("Invalid User or Product ID.\n");
                    break;
                }
                recordPurchase(&graph, userId, productId);
                printf("Purchase history recorded.\n");
                break;

            case 5: // Retrieve User History
                printf("Enter User ID (0 to %d): ", MAX_USERS - 1);
                scanf("%d", &userId);
                if (userId < 0 || userId >= MAX_USERS) {
                    printf("Invalid User ID.\n");
                    break;
                }
                retrieveHistory(&graph, userId, MAX_PRODUCTS, productTable);
                break;

            case 6: // View Recommendations
                printf("Enter User ID (0 to %d): ", MAX_USERS - 1);
                scanf("%d", &userId);
                if (userId < 0 || userId >= MAX_USERS) {
                    printf("Invalid User ID.\n");
                    break;
                }
                recommendProducts(&graph, userId, MAX_PRODUCTS, productTable);
                break;

            case 7: // Exit
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function Definitions
int hash(int id, int tableSize) {
    return id % tableSize;
}

void addUser(User* userTable[], int tableSize, int id, char* name) {
    int index = hash(id, tableSize);
    User* newUser = (User*)malloc(sizeof(User));
    newUser->id = id;
    strcpy(newUser->name, name);
    newUser->next = userTable[index];
    userTable[index] = newUser;
}

User* getUser(User* userTable[], int tableSize, int id) {
    int index = hash(id, tableSize);
    User* temp = userTable[index];
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void updateUser(User* userTable[], int tableSize, int id, char* newName) {
    User* user = getUser(userTable, tableSize, id);
    if (user != NULL) {
        strcpy(user->name, newName);
    } else {
        printf("User ID not found.\n");
    }
}

void addProduct(Product* productTable[], int tableSize, int id, char* name) {
    int index = hash(id, tableSize);
    Product* newProduct = (Product*)malloc(sizeof(Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->next = productTable[index];
    productTable[index] = newProduct;
}

Product* getProduct(Product* productTable[], int tableSize, int id) {
    int index = hash(id, tableSize);
    Product* temp = productTable[index];
    while (temp != NULL) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void updateProduct(Product* productTable[], int tableSize, int id, char* newName) {
    Product* product = getProduct(productTable, tableSize, id);
    if (product != NULL) {
        strcpy(product->name, newName);
    } else {
        printf("Product ID not found.\n");
    }
}

void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < MAX_PRODUCTS; j++) {
            graph->adjacencyMatrix[i][j] = 0;
            graph->weights[i][j] = 0;
        }
    }
}

void recordBrowsing(Graph* graph, int userId, int productId) {
    graph->adjacencyMatrix[userId][productId] = 1;
    graph->weights[userId][productId] += 1;
}

void recordPurchase(Graph* graph, int userId, int productId) {
    graph->adjacencyMatrix[userId][productId] = 2;
    graph->weights[userId][productId] += 5;
}

void retrieveHistory(Graph* graph, int userId, int numProducts, Product* productTable[]) {
    printf("History for User %d:\n", userId);
    for (int j = 0; j < numProducts; j++) {
        if (graph->adjacencyMatrix[userId][j] == 1) {
            printf("Product %d: Browsed\n", j);
        } else if (graph->adjacencyMatrix[userId][j] == 2) {
            printf("Product %d: Purchased\n", j);
        }
    }
}

void recommendProducts(Graph* graph, int userId, int numProducts, Product* productTable[]) {
    printf("Recommendations for User %d:\n", userId);
    for (int j = 0; j < numProducts; j++) {
        if (graph->adjacencyMatrix[userId][j] == 0 && calculateRecommendationScore(graph, userId, j) > 0) {
            printf("Product %d: Recommended\n", j);
        }
    }
}

int calculateRecommendationScore(Graph* graph, int userId, int productId) {
    return graph->weights[userId][productId];
}

void displayMenu() {
    printf("\n*** E-commerce Platform ***\n");
    printf("1. Add User\n");
    printf("2. Add Product\n");
    printf("3. Browse Product\n");
    printf("4. Purchase Product\n");
    printf("5. Retrieve User History\n");
    printf("6. View Product Recommendations\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}