#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Car Model Structure
typedef struct CarModel {
    char model_name[50];
    char make[50];
    int year;
    int price;
    int num_available_cars;
    struct CarModel* next;
    struct CarModel* prev;
} CarModel;

// Hash Table Structure
typedef struct HashTable {
    int size;
    CarModel** table;
} HashTable;

//create a new hash table
HashTable* create_hash_table(int size) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    hash_table->size = size;
    hash_table->table = (CarModel**)malloc(sizeof(CarModel*) * size);
    for (int i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

// Function Prototypes
CarModel* create_car_model(char* model_name, char* make, int year, int price, int num_available_cars);
void add_car_model(HashTable* hash_table, CarModel* car_model);
CarModel* find_car_model(HashTable* hash_table, char* model_name);
void update_car_model(CarModel* car_model, char* make, int year, int price, int num_available_cars);
void delete_car_model(HashTable* hash_table, CarModel* car_model);
void sell_car(CarModel* car_model);
void display_inventory(CarModel* car_model);
void destroy_hash_table(HashTable* hash_table);

// Hash Function
int hash(char* key, int size) {
    int sum = 0;
    for (int i = 0; i < strlen(key); i++) {
        sum += key[i];
    }
    return sum % size;
}

// Create a new car model
CarModel* create_car_model(char* model_name, char* make, int year, int price, int num_available_cars) {
    CarModel* car_model = (CarModel*)malloc(sizeof(CarModel));
    strcpy(car_model->model_name, model_name);
    strcpy(car_model->make, make);
    car_model->year = year;
    car_model->price = price;
    car_model->num_available_cars = num_available_cars;
    car_model->next = NULL;
    car_model->prev = NULL;
    return car_model;
}

// Add a car model to the hash table
void add_car_model(HashTable* hash_table, CarModel* car_model) {
    int index = hash(car_model->model_name, hash_table->size);
    if (hash_table->table[index] == NULL) {
        hash_table->table[index] = car_model;
    }
    else {
        CarModel* current = hash_table->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = car_model;
        car_model->prev = current;
    }
}

// Find a car model in the hash table
CarModel* find_car_model(HashTable* hash_table, char* model_name) {
    int index = hash(model_name, hash_table->size);
    CarModel* current = hash_table->table[index];
    while (current != NULL) {
        if (strcmp(current->model_name, model_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//get the car model
CarModel* get_car_model(HashTable* hash_table, char* model_name) {
    int index = hash(model_name, hash_table->size);
    CarModel* current = hash_table->table[index];
    while (current != NULL) {
        if (strcmp(current->model_name, model_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Update a car model
void update_car_model(CarModel* car_model, char* make, int year, int price, int num_available_cars) {
    strcpy(car_model->make, make);
    car_model->year = year;
    car_model->price = price;
    car_model->num_available_cars = num_available_cars;
}

// Delete a car model from the hash table
void delete_car_model(HashTable* hash_table, CarModel* car_model) {
    int index = hash(car_model->model_name, hash_table->size);
    if (hash_table->table[index] == car_model) {
        hash_table->table[index] = car_model->next;
        if (car_model->next != NULL) {
            car_model->next->prev = NULL;
        }
    }
    else {
        if (car_model->prev != NULL) {
            car_model->prev->next = car_model->next;
        }
        if (car_model->next != NULL) {
            car_model->next->prev = car_model->prev;
        }
    }
    free(car_model);
}

// Sell a car
void sell_car(CarModel* car_model) {
    if (car_model->num_available_cars > 0) {
        car_model->num_available_cars--;
    }
}

// Display the current inventory
void display_inventory(CarModel* car_model) {
    printf("%-20s %-20s %-10s %-10s %-10s\n", "Model Name", "Make", "Year", "Price", "Available Cars");
    printf("--------------------------------------------------------\n");
    while (car_model != NULL) {
        printf("%-20s %-20s %-10d %-10d %-10d\n", car_model->model_name, car_model->make, car_model->year, car_model->price, car_model->num_available_cars);
        car_model = car_model->next;
    }
}

//view hash table
void view_hash_table(HashTable* hash_table) {
    printf("%-20s %-20s %-10s %-10s %-10s\n", "Model Name", "Make", "Year", "Price", "Available Cars");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < hash_table->size; i++) {
        CarModel* current = hash_table->table[i];
        while (current != NULL) {
            printf("%-20s %-20s %-10d %-10d %-10d\n", current->model_name, current->make, current->year, current->price, current->num_available_cars);
            current = current->next;
        }
    }
}

// Destroy the hash table
void destroy_hash_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        CarModel* current = hash_table->table[i];
        while (current != NULL) {
            CarModel* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hash_table->table);
    free(hash_table);
}

int main() {
    // Create a hash table with size 10
    HashTable* hash_table = create_hash_table(10);

    // Create a few car models
    CarModel* camry = create_car_model("Camry", "Toyota", 2019, 25000, 10);
    CarModel* corolla = create_car_model("Corolla", "Toyota", 2019, 20000, 5);
    CarModel* f150 = create_car_model("F-150", "Ford", 2019, 35000, 15);
    CarModel* mustang = create_car_model("Mustang", "Ford", 2019, 40000, 20);

    // Add the car models to the hash table
    add_car_model(hash_table, camry);
    add_car_model(hash_table, corolla);
    add_car_model(hash_table, f150);
    add_car_model(hash_table, mustang);



    // Display the current inventory
    view_hash_table(hash_table);

    // Sell a car
    sell_car(camry);

    // Display the updated inventory
   view_hash_table(hash_table);

    // Delete a car model
    delete_car_model(hash_table, f150);

    // Display the updated inventory
    view_hash_table(hash_table);

    // Destroy the hash table
    destroy_hash_table(hash_table);

    return 0;
}