#ifndef USUARIO_H
#define USUARIO_H

typedef struct User {
    int id, age;
    char name[100];
    float balance;
} User;

typedef struct {
    User* users;
    int size;
    int capacity;
} UserVector;

// Initializes the vector with a initial size and capacity.
void initVector(UserVector* array);

/*
@brief Raises the capacity of the user vector.
@param array The vector to be resized
*/
void resizeVector(UserVector* array);

// Free the memory block that is being used by the vector.
void clearVectorMem(UserVector* array);

// Prints a list of all users in the console
void printVector(UserVector* array);

/* 
@brief Insert a new user to the vector.
@note Uses the resizeVector() if there is no memory available.

*/
void insertUser(UserVector* array, int id, int age, char* name, float balance);

// Removes a user from the vector
void deleteUser(UserVector* array, int userId);

/*
@brief Make a transference from a User to another. 

@param users the list of users currently registered
@param idSender The id from the person that is sending the money
@param idReceiver The id from the person that is receiving the money
*/
void transferBalance(UserVector* users, int idSender, int idReceiver, float value);

void exportUsers(const char* file, UserVector* array);

#endif
