# Examinationsprojekt - Reglering av pingisboll

Detta repo innehåller kod för att reglera en pingisboll på en ramp. Det är ett examinationsprojekt i kursen Inbyggda System och Signaler som ges på Malmö Högskola. 

Mjukvaran består av två delar:

- Matlab-kod: com.m är en Matlab-funktion som upprättar kommunikation med Arduino via seriell port, samt plottar resultatet av regleringen.
- C-program för processorn SAM3X8E: pingisproj innehåller ett projekt som öpnas i Atmel Studio 7.0 (ej 6.2). Programmet bygger på FreeRTOS och innehåller två processer, en för att kommunicera med Matlab och en för att reglera pingisbollen.

Författare: Dennis Wildmark och Olle Casperson
