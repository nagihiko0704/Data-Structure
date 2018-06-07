#pragma once

#include "user.h"

int *get_friend_num(UserType *user);
int get_total_friend_num(UserType *user);
float get_avg_friend_num(UserType *user);
int get_min_friend_num(UserType *user);
int get_max_friend_num(UserType *user);
void find_friend(UserType *user, int id_num);
int find_common_friend(UserType *user, int id_num1, int id_num2);