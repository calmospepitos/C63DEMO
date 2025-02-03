// Exercice-Logger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cassert>
#include <windows.h>
#include "Logger.h"
using namespace LoopEngine;

int main()
{
    SetConsoleOutputCP(1252);

    //�criture dans la console et le fichier "C63Demo/Exercice-Logger/LoopEngine.log"
    Logger* log = new Logger(Logger::TLevel::eINFO, true, true);
    assert(log != nullptr);

    log->Log("De l'information seulement.", Logger::TLevel::eINFO);
    log->Log("Un avertissement, peut causer des probl�mes mineurs.", Logger::TLevel::eWARNING);
    log->Log("Pour d�bogger", Logger::TLevel::eDEBUG);
    //log->Log("Une erreur, c'est grave et va casser l'application. Va suspendre avec la configuration par d�faut!", Logger::TLevel::eERROR);
    //log->SetFileTraceName("JeVaisInterrompre!");
    log->ActivateFileTrace(false);
    log->SetFileTraceName("NouveauLog.log");
    log->ActivateFileTrace(true);
    log->Log("Va �crire dans la console et NouveauLog.log.", Logger::TLevel::eINFO);

    log->SetLoggingLevel(Logger::TLevel::eWARNING);
    log->Log("Cette entr�e sera ignor�e.", Logger::TLevel::eINFO);

    //Ne va jamais interrompre
    log->SetAbortLevel(Logger::eNONE);
    //Cause une erreur
    log->SetFileTraceName("");

    //Toujours lib�rer sa m�moire
    delete log;
    log = nullptr;
}