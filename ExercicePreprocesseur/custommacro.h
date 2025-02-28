#pragma once
#include <iostream>

// Si pragma once n'est pas disponible faire un ifndef
#ifndef CUSTOMMACRO_H  // Vérifie si CUSTOMMACRO_H n'est pas encore défini
#define CUSTOMMACRO_H  // Définit CUSTOMMACRO_H pour éviter une seconde inclusion

#define NATURAL_NUMBER 2.73f
#define FIBONNACCI_NUMBER 1.618f
#define WIERD_NUMBER (NATURAL_NUMBER + FIBONNACCI_NUMBER)

#undef WIERD_NUMBER
#define WIERD_NUMBER (NATURAL_NUMBER + FIBONNACCI_NUMBER)

#define LOG(message) std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << message << std::endl;

#endif // CUSTOMMACRO_H