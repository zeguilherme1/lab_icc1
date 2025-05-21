#ifndef USER_ACTIONS_H
#define USER_ACTIONS_H

void addNewUser(UserVector *array);

void removeUser(UserVector *array);

void makeTransference(UserVector *array);

// Prints a list of all users in the console
void printVector(UserVector* array);

void exportUsersToTxt(UserVector* array);

#endif