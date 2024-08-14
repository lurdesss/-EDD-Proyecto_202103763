#include "User.h"

// Constructor de la estructura User.
User::User(string paramFName, string paramLName, string paramBDate, string paramEmail, string paramPwd)
    : atrFName(paramFName), atrLName(paramLName), atrBDate(paramBDate), atrEmail(paramEmail), atrPwd(paramPwd), siguiente(nullptr) {}