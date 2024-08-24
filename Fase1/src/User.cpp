#include "User.h"

// Constructor de la estructura User.
User::User(int paramId, string paramFName, string paramLName, string paramBDate, string paramEmail, string paramPwd)
    : atrId(paramId), atrFName(paramFName), atrLName(paramLName), atrBDate(paramBDate), atrEmail(paramEmail), atrPwd(paramPwd), siguiente(nullptr) {}