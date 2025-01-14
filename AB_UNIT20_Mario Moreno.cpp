﻿// AB_UNIT20_Mario Moreno.cpp: punto de entrada de la aplicación.

#include "AB_UNIT20_Mario Moreno.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

// Clases
// Clase para pacientes
class Paciente {
public:
    string nombre;
    string apellidos;
    string dni;
    string fechaIngreso;
    string enfermedad;
    vector<string> historialClinico;

    Paciente(string nombre, string apellidos, string dni, string fechaIngreso, string enfermedad = "")
        : nombre(nombre), apellidos(apellidos), dni(dni), fechaIngreso(fechaIngreso), enfermedad(enfermedad) {
    }

    static void mostrarPacientesDesdeCSV(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << archivo << " para leer.\n";
            return;
        }

        vector<Paciente> pacientes;
        string linea;

        // Leer el archivo línea por línea
        while (getline(file, linea)) {
            stringstream ss(linea);
            string nombre, apellidos, dni, fechaIngreso, enfermedad;

            // Leer los campos separados por comas
            getline(ss, nombre, ',');
            getline(ss, apellidos, ',');
            getline(ss, dni, ',');
            getline(ss, fechaIngreso, ',');
            getline(ss, enfermedad);

            pacientes.emplace_back(nombre, apellidos, dni, fechaIngreso, enfermedad);
        }

        file.close();

        // Mostrar los pacientes en formato tabular
        if (pacientes.empty()) {
            cout << "No hay pacientes registrados en el archivo.\n";
            return;
        }

        cout << left << setw(15) << "Nombre"
            << setw(20) << "Apellidos"
            << setw(15) << "DNI"
            << setw(15) << "Fecha Ingreso"
            << setw(20) << "Enfermedad" << "\n";
        cout << string(85, '-') << "\n";

        for (const auto& paciente : pacientes) {
            cout << left << setw(15) << paciente.nombre
                << setw(20) << paciente.apellidos
                << setw(15) << paciente.dni
                << setw(15) << paciente.fechaIngreso
                << setw(20) << (paciente.enfermedad.empty() ? "N/A" : paciente.enfermedad) << "\n";
        }
    }

    void guardarEnArchivoCSV(const string& archivo) const {
        ofstream file(archivo, ios::app); // Abrir en modo "append" para agregar datos
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << archivo << " para escribir.\n";
            return;
        }

        file << nombre << "," << apellidos << "," << dni << "," << fechaIngreso << "," << enfermedad << "\n";
        file.close();
        cout << "Datos guardados en el archivo CSV correctamente.\n";
    }

    void modificarArchivoCSV(const string& archivo, const vector<Paciente>& pacientes) {
        ofstream file(archivo, ios::trunc); // Sobreescribir el archivo con los nuevos datos
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << archivo << " para escribir.\n";
            return;
        }

        for (const auto& paciente : pacientes) {
            file << paciente.nombre << "," << paciente.apellidos << "," << paciente.dni << "," << paciente.fechaIngreso << "," << paciente.enfermedad << "\n";
        }

        file.close();
        cout << "Archivo CSV actualizado correctamente.\n";
    }

    static void leerArchivoCSV(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << archivo << " para leer.\n";
            return;
        }

        cout << "Contenido del archivo CSV:\n";
        string linea;
        while (getline(file, linea)) {
            cout << linea << "\n";
        }

        file.close();
    }

    void modificarDatos(vector<Paciente>& pacientes) {
        cout << "Modificar datos del paciente.\n";
        bool continuar = true;

        while (continuar) {
            cout << "Seleccione el campo que desea modificar:\n";
            cout << "1. Nombre\n";
            cout << "2. Apellidos\n";
            cout << "3. DNI\n";
            cout << "4. Fecha de ingreso\n";
            cout << "5. Enfermedad\n";
            cout << "6. Finalizar modificaciones\n";
            cout << "Seleccione una opcion: ";

            int opcion;
            cin >> opcion;

            switch (opcion) {
            case 1:
                cout << "Nuevo nombre: ";
                cin >> nombre;
                break;
            case 2:
                cout << "Nuevos apellidos: ";
                cin.ignore();
                getline(cin, apellidos);
                break;
            case 3: {
                string nuevoDNI;
                cout << "Nuevo DNI: ";
                cin >> nuevoDNI;

                // Verificar si el DNI ya existe
                bool dniDuplicado = any_of(pacientes.begin(), pacientes.end(), [&nuevoDNI, this](const Paciente& p) {
                    return p.dni == nuevoDNI && p.dni != this->dni; // Excluir el paciente actual
                    });

                if (dniDuplicado) {
                    cout << "Error: El DNI ingresado ya pertenece a otro paciente. Intente nuevamente.\n";
                }
                else {
                    dni = nuevoDNI;
                    cout << "DNI actualizado correctamente.\n";
                }
                break;
            }
            case 4:
                cout << "Nueva fecha de ingreso: ";
                cin.ignore();
                getline(cin, fechaIngreso);
                break;
            case 5:
                cout << "Nueva enfermedad: ";
                cin.ignore();
                getline(cin, enfermedad);
                break;
            case 6:
                continuar = false;
                break;
            default:
                cout << "Opción no valida. Intente nuevamente.\n";
            }

            if (continuar) {
                cout << "¿Desea cambiar otro campo? (S/N): ";
                char respuesta;
                cin >> respuesta;
                continuar = toupper(respuesta) == 'S';
            }
        }

        cout << "Datos modificados correctamente.\n";
    }

    void altaPaciente() {
        cout << "El paciente " << nombre << " ha recibido el alta medica.\n";
    }

    void bajaPaciente() {
        cout << "El paciente " << nombre << " ha sido dado de baja.\n";
    }

    void registrarHistorial(string registro) {
        historialClinico.push_back(registro);
    }

    void mostrarHistorial() const {
        cout << "Historial clinico de " << nombre << ":\n";
        for (const auto& registro : historialClinico) {
            cout << "- " << registro << "\n";
        }
    }

    void gestionarEnfermedadCronica() {
        string enfermedadCronica, descripcion;
        cout << "Paciente: " << nombre << " " << apellidos << "\n";

        if (enfermedad.empty()) {
            cout << "El paciente no tiene una enfermedad registrada.\n";
            return;
        }

        cout << "Enfermedad actual registrada: " << enfermedad << "\n";
        cout << "¿Desea modificar esta enfermedad? (S/N): ";
        char opcionEnfermedad;
        cin >> opcionEnfermedad;
        if (toupper(opcionEnfermedad) == 'S') {
            cout << "Ingrese el nuevo nombre de la enfermedad cronica: ";
            cin.ignore();
            getline(cin, enfermedadCronica);
            enfermedad = enfermedadCronica;
        }
        else {
            enfermedadCronica = enfermedad;
        }

        bool descripcionExistente = false;
        for (auto& registro : historialClinico) {
            if (registro.find("Enfermedad cronica registrada: " + enfermedad) != string::npos) {
                cout << "Descripcion actual encontrada en el historial:\n" << registro << "\n";
                descripcionExistente = true;
                cout << "¿Desea modificar la descripcion? (S/N): ";
                char opcionModificarDescripcion;
                cin >> opcionModificarDescripcion;
                if (toupper(opcionModificarDescripcion) == 'S') {
                    cout << "Ingrese la nueva descripcion de la enfermedad: ";
                    cin.ignore();
                    getline(cin, descripcion);
                    registro = "Enfermedad cronica registrada: " + enfermedadCronica + " - " + descripcion;
                    cout << "Nueva descripcion registrada exitosamente.\n";
                }
                break;
            }
        }

        if (!descripcionExistente) {
            cout << "No hay descripción actual de la enfermedad.\n";
            cout << "¿Desea agregar una descripcion? (S/N): ";
            char opcionDescripcion;
            cin >> opcionDescripcion;
            if (toupper(opcionDescripcion) == 'S') {
                cout << "Ingrese la descripcion de la enfermedad: ";
                cin.ignore();
                getline(cin, descripcion);
                registrarHistorial("Enfermedad cronica registrada: " + enfermedadCronica + " - " + descripcion);
            }
            else {
                registrarHistorial("Enfermedad cronica registrada: " + enfermedadCronica);
            }
        }
    }
};

 vector<string> especialidades = {
                    "Alergologia", "Anatomia Patologica", "Anestesiologia y Reanimacion",
                    "Angiologia y Cirugia Vascular", "Aparato Digestivo", "Cardiologia",
                    "Cirugia Cardiovascular", "Cirugia General y del Aparato Digestivo",
                    "Cirugia Oral y Maxilofacial", "Cirugia Ortopedica y Traumatologia",
                    "Cirugia Pediatrica", "Cirugia Plastica, Estetica y Reparadora",
                    "Cirugía Toracica", "Dermatologia Medico-Quirurgica y Venereologia",
                    "Endocrinologia y Nutricion", "Farmacologia Clinica", "Geriatria",
                    "Hematologia y Hemoterapia", "Inmunologia", "Medicina del Trabajo",
                    "Medicina Familiar y Comunitaria", "Medicina Fisica y Rehabilitacion",
                    "Medicina Intensiva", "Medicina Interna", "Medicina Nuclear",
                    "Medicina Preventiva y Salud Publica", "Nefrologia", "Neumologia",
                    "Neurocirugia", "Neurofisiologia Clinica", "Neurologia",
                    "Obstetricia y Ginecologia", "Oftalmologia", "Oncologia Medica",
                    "Oncología Radioterapica", "Otorrinolaringologia",
                    "Pediatria y sus Areas Especificas", "Psiquiatria", "Radiodiagnostico",
                    "Reumatologia", "Urologia"
                };

// Clase para médicos
class Medico {
public:
    string nombre;
    string apellidos;
    string dni;
    string especialidad;
    bool disponible;

    Medico(string nombre, string apellidos, string dni, bool disponible)
        : nombre(nombre), apellidos(apellidos), dni(dni), disponible(disponible) {
    }

    void modificarDatos(vector<Medico>& medicos) {
        int opcion;
        do {
            cout << "Seleccione el campo que desea modificar:\n";
            cout << "1. Nombre\n";
            cout << "2. Apellidos\n";
            cout << "3. DNI\n";
            cout << "4. Disponibilidad\n";
            cout << "0. Salir\n";
            cout << "Ingrese su opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                cout << "Ingrese el nuevo nombre: ";
                cin >> nombre;
                break;
            case 2:
                cout << "Ingrese los nuevos apellidos: ";
                cin >> apellidos;
                break;
            case 3: {
                string nuevoDni;
                cout << "Ingrese el nuevo DNI: ";
                cin >> nuevoDni;

                auto it = find_if(medicos.begin(), medicos.end(), [&nuevoDni](const Medico& m) { return m.dni == nuevoDni; });
                if (it != medicos.end()) {
                    cout << "Error: Ya existe un medico con ese DNI.\n";
                }
                else {
                    dni = nuevoDni;
                    cout << "DNI actualizado correctamente.\n";
                }
                break;
            }
            case 4:
                cout << "Ingrese la nueva disponibilidad (1 para si, 0 para no): ";
                cin >> disponible;
                break;
            case 0:
                cout << "Saliendo de la modificacion de datos.\n";
                break;
            default:
                cout << "Opcion no valida.\n";
            }
        } while (opcion != 0);

        cout << "Los datos del medico han sido actualizados.\n";
    }

    void asignarEspecialidad(const vector<string>& especialidades) {
        cout << "Seleccione la especialidad:\n";
        for (size_t i = 0; i < especialidades.size(); ++i) {
            cout << i + 1 << ". " << especialidades[i] << '\n';
        }
        int seleccion;
        cout << "Seleccione una opcion (1-" << especialidades.size() << "): ";
        cin >> seleccion;
        if (seleccion >= 1 && seleccion <= especialidades.size()) {
            especialidad = especialidades[seleccion - 1];
            cout << "Especialidad asignada: " << especialidad << '\n';
        }
        else {
            cout << "Opcion no valida.\n";
        }
    }

    void altaMedico() {
        disponible = true;
        cout << "El medico " << nombre << " " << apellidos << " ha sido dado de alta y ahora esta disponible.\n";
    }

    void bajaMedico() {
        disponible = false;
        cout << "El medico " << nombre << " " << apellidos << " ha sido dado de baja y ahora no esta disponible.\n";
    }

    static void listarMedicos(const vector<Medico>& medicos, bool disponibilidad) {
        vector<const Medico*> filtrados;
        for (const auto& medico : medicos) {
            if (medico.disponible == disponibilidad) {
                filtrados.push_back(&medico);
            }
        }
        sort(filtrados.begin(), filtrados.end(), [](const Medico* a, const Medico* b) {
            return a->especialidad < b->especialidad;
            });

        cout << "--- Lista de medicos " << (disponibilidad ? "disponibles" : "no disponibles") << " ---\n";
        for (const auto* medico : filtrados) {
            cout << medico->nombre << " " << medico->apellidos << " - Especialidad: " << medico->especialidad << '\n';
        }
    }
};

// Clase para citas médicas
class CitaMedica {
public:
    string id;
    string fechaHora;
    string especialidad;
    Medico* medico;
    Paciente* paciente;
    short int nivelUrgencia;
    string estado; // Puede ser "pendiente" o "atendida"

    CitaMedica(string id, string fechaHora, string especialidad, Medico* medico, Paciente* paciente, short int nivelUrgencia)
        : id(id), fechaHora(fechaHora), especialidad(especialidad), medico(medico), paciente(paciente), nivelUrgencia(nivelUrgencia), estado("pendiente") {}

    void modificarCita() {
        cout << "Modificar datos de la cita.\n";
        cout << "Nueva fecha y hora: ";
        cin.ignore();
        getline(cin, fechaHora);
        cout << "Nuevo nivel de urgencia (1-5): ";
        cin >> nivelUrgencia;
    }

    static void ordenarCitas(vector<CitaMedica>& citas) {
        sort(citas.begin(), citas.end(), [](CitaMedica& a, CitaMedica& b) {
            if (a.fechaHora != b.fechaHora)
                return a.fechaHora < b.fechaHora;
            return a.nivelUrgencia > b.nivelUrgencia;
        });
    }

    static void listarCitasPendientesPorEspecialidad(vector<CitaMedica>& citas, const string& horaActual) {
        // Actualizar el estado de citas según la hora actual
        for (auto& cita : citas) {
            if (cita.estado == "pendiente" && horaActual > cita.fechaHora) {
                cita.estado = "expirada";
            }
        }

        // Filtrar y ordenar las citas pendientes por especialidad
        vector<CitaMedica> pendientes;
        copy_if(citas.begin(), citas.end(), back_inserter(pendientes), [](CitaMedica& cita) {
            return cita.estado == "pendiente";
        });

        sort(pendientes.begin(), pendientes.end(), [](CitaMedica& a, CitaMedica& b) {
            return a.especialidad < b.especialidad;
        });

        // Imprimir las citas pendientes
        cout << "Citas pendientes por especialidad:\n";
        for (const auto& cita : pendientes) {
            cout << "ID: " << cita.id << " | Especialidad: " << cita.especialidad << " | Fecha y Hora: " << cita.fechaHora << " | Paciente: " << cita.paciente->nombre << "\n";
        }
    }

    static void listarPacientesAtendidosEntreFechas(const vector<CitaMedica>& citas, const string& fechaInicio, const string& fechaFin) {
        // Filtrar y ordenar las citas atendidas dentro del rango de fechas
        vector<CitaMedica> atendidas;
        copy_if(citas.begin(), citas.end(), back_inserter(atendidas), [&](const CitaMedica& cita) {
            return cita.estado == "atendida" && cita.fechaHora >= fechaInicio && cita.fechaHora <= fechaFin;
        });

        sort(atendidas.begin(), atendidas.end(), [](CitaMedica& a, CitaMedica& b) {
            return a.fechaHora > b.fechaHora; // Más reciente a más antiguo
        });

        // Imprimir las citas atendidas
        cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";
        for (const auto& cita : atendidas) {
            cout << "Fecha y Hora: " << cita.fechaHora << " | Paciente: " << cita.paciente->nombre << " | Especialidad: " << cita.especialidad << "\n";
        }
    }

    static void marcarCitaComoAtendida(vector<CitaMedica>& citas) {
        string idCita;
        cout << "Ingrese el ID de la cita para marcar como atendida: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, idCita);

        bool encontrada = false;
        for (auto& cita : citas) {
            if (cita.id == idCita) {
                if (cita.estado == "pendiente") {
                    cita.estado = "atendida";
                    cout << "La cita con ID " << idCita << " ha sido marcada como atendida.\n";
                }
                else {
                    cout << "La cita con ID " << idCita << " no estaba pendiente.\n";
                }
                encontrada = true;
                break;
            }
        }

        if (!encontrada) {
            cout << "No se encontro una cita pendiente con el ID especificado.\n";
        }
    }
};

// Función para obtener la hora actual como cadena en formato "YYYY-MM-DD HH:MM"
string obtenerHoraActual() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", tiempoLocal);
    return string(buffer);
}

// Almacenamientos de ID y que sean únicos
set<string> idGenerar;

string generarIDCita(Paciente* paciente) {
    // Obtener iniciales del paciente
    string iniciales;
    if (!paciente->nombre.empty())
        iniciales += toupper(paciente->nombre[0]);
    if (!paciente->apellidos.empty()) {
        auto espacio = paciente->apellidos.find(' ');
        iniciales += toupper(paciente->apellidos[0]);
        if (espacio != string::npos && espacio + 1 < paciente->apellidos.length())
            iniciales += toupper(paciente->apellidos[espacio + 1]);
    }

    // Generar número aleatorio
    string idCita;
    srand(time(nullptr));
    do {
        int numero = rand() % 10000; // Generar número aleatorio de 4 cifras
        char numeroStr[5];
        snprintf(numeroStr, sizeof(numeroStr), "%04d", numero);
        idCita = string(numeroStr) + " " + iniciales;
    } while (idGenerar.count(idCita)); // Repetir si el ID ya existe

    idGenerar.insert(idCita);
    return idCita;
}

// Clase para gestiones
class Gestiones {
public:

    
};

// Submenús
// Menú paciente
void menuPacientes(vector<Paciente>& pacientes, const string& archivoCSV) {
    short int opcion;
    do {
        cout << "--- Menú Pacientes ---\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Modificar datos del paciente\n";
        cout << "3. Dar de alta médica\n";
        cout << "4. Dar de baja médica\n";
        cout << "5. Registrar historial clínico\n";
        cout << "6. Mostrar historial clínico\n";
        cout << "7. Reporte enfermedad crónica\n";
        cout << "8. Mostrar lista de pacientes\n"; // Nueva opción
        cout << "9. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, apellidos, dni, fechaIngreso, enfermedad;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cin.ignore();
            cout << "Ingrese apellidos: ";
            getline(cin, apellidos);
            cout << "Ingrese DNI: ";
            cin >> dni;

            // Verificar si el DNI ya existe
            bool dniDuplicado = any_of(pacientes.begin(), pacientes.end(), [&dni](const Paciente& p) {
                return p.dni == dni;
                });

            if (dniDuplicado) {
                cout << "Error: El DNI ingresado ya pertenece a otro paciente. Registro cancelado.\n";
            }
            else {
                cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fechaIngreso);
                cout << "Ingrese enfermedad (opcional): ";
                getline(cin, enfermedad);

                // Registrar paciente en el vector y en el archivo CSV
                Paciente nuevoPaciente(nombre, apellidos, dni, fechaIngreso, enfermedad);
                pacientes.push_back(nuevoPaciente);
                nuevoPaciente.guardarEnArchivoCSV(archivoCSV);

                cout << "Paciente registrado y guardado en archivo CSV.\n";
            }
            break;
        }
        case 2: {
            string dni;
            cout << "Ingrese el DNI del paciente a modificar: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->modificarDatos(pacientes); // Pasamos el vector pacientes como argumento
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 3: {
            string dni;
            cout << "Ingrese el DNI del paciente para dar de alta médica: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->altaPaciente();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 4: {
            string dni;
            cout << "Ingrese el DNI del paciente para dar de baja médica: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->bajaPaciente();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 5: {
            string dni, registro;
            cout << "Ingrese el DNI del paciente: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                cout << "Ingrese el registro para el historial clínico: ";
                cin.ignore();
                getline(cin, registro);
                it->registrarHistorial(registro);
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 6: {
            string dni;
            cout << "Ingrese el DNI del paciente: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->mostrarHistorial();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 7: {
            string dni;
            cout << "Ingrese el DNI del paciente: ";
            cin >> dni;
            auto it = find_if(pacientes.begin(), pacientes.end(), [&dni](Paciente& p) { return p.dni == dni; });
            if (it != pacientes.end()) {
                it->gestionarEnfermedadCronica();
            }
            else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 8: {
            Paciente::mostrarPacientesDesdeCSV(archivoCSV);
            break;
        }
        case 9:
            cout << "Volviendo al menú principal.\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 9);
}


// Menú médicos
void menuMedicos(vector<Medico>& medicos) {
    short int opcion;
    do {
        cout << "--- Menu Medicos ---\n";
        cout << "1. Registrar medico\n";
        cout << "2. Modificar datos del medico\n";
        cout << "3. Asignar especialidad\n";
        cout << "4. Listado medicos disponibles\n";
        cout << "5. Listado medicos no disponibles\n";
        cout << "6. Dar de alta\n";
        cout << "7. Dar de baja\n";
        cout << "8. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, apellidos, dni;
            bool disponible;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese apellidos: ";
            cin >> apellidos;
            cout << "Ingrese DNI: ";
            cin >> dni;

            auto it = find_if(medicos.begin(), medicos.end(), [&dni](const Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                cout << "Error: Ya existe un medico con ese DNI.\n";
            }
            else {
                cout << "Medico disponible (1 para si, 0 para no): ";
                cin >> disponible;
                medicos.emplace_back(nombre, apellidos, dni, disponible);
                cout << "Medico registrado.\n";
            }
            break;
        }
        case 2: {
            string dni;
            cout << "Ingrese el DNI del medico a modificar: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->modificarDatos(medicos);
            }
            else {
                cout << "Medico no encontrado.\n";
            }
            break;
        }
        case 3: {
            string dni;
            cout << "Ingrese el DNI del medico para asignar especialidad: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->asignarEspecialidad(especialidades);
            }
            else {
                cout << "Medico no registrado.\n";
            }
            break;
        }
        case 4:
            Medico::listarMedicos(medicos, true);
            break;
        case 5:
            Medico::listarMedicos(medicos, false);
            break;
        case 6: {
            string dni;
            cout << "Ingrese el DNI del medico para dar de alta: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->altaMedico();
            }
            else {
                cout << "Medico no encontrado.\n";
            }
            break;
        }
        case 7: {
            string dni;
            cout << "Ingrese el DNI del medico para dar de baja: ";
            cin >> dni;
            auto it = find_if(medicos.begin(), medicos.end(), [&dni](Medico& m) { return m.dni == dni; });
            if (it != medicos.end()) {
                it->bajaMedico();
            }
            else {
                cout << "Medico no encontrado.\n";
            }
            break;
        }
        case 8:
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 8);
}


// Menú citas médicas
void menuCitas(vector<CitaMedica>& citas, vector<Medico>& medicos, vector<Paciente>& pacientes) {
    short int opcion;
    do {
        cout << "--- Menu citas ---\n";
        cout << "1. Asignar cita\n";
        cout << "2. Modificar datos de la cita\n";
        cout << "3. Cancelar cita\n";
        cout << "4. Citas ordenadas por fecha o nivel de urgencia\n";
        cout << "5. Registro de citas completo\n";
        cout << "6. Marcar citas pendientes como atendidas\n";
        cout << "7. Lista citas pendientes por especialidad\n";
        cout << "8. Lista pacientes atendidos entre un rango de fechas\n";
        cout << "9. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string id;
            string fechaHora, especialidad;
            short int nivelUrgencia;
            Medico* medico = nullptr;
            Paciente* paciente = nullptr;

            cout << "Asignar una nueva cita\n";
            cout << "Fecha y hora (YYYY-MM-DD HH:MM): ";
            cin.ignore();
            getline(cin, fechaHora);
            cout << "Elija una especialidad:\n";
            for (size_t i = 0; i < especialidades.size(); ++i) {
                cout << i + 1 << ". " << especialidades[i] << endl;
            }

            short int especialidadSeleccion;
            cout << "Seleccione el numero de la especialidad (0 para cancelar): ";
            cin >> especialidadSeleccion;

            if (especialidadSeleccion < 1 || especialidadSeleccion > especialidades.size()) {
                cout << "Especialidad invalida. Operacion cancelada.\n";
                break;
            }

            especialidad = especialidades[especialidadSeleccion - 1];

            // Seleccionar médico
            cout << "Medicos disponibles de la especialidad " << especialidad << ":\n";
            vector<Medico*> medicosEspecialidad;
            for (auto& medicoIter : medicos) {
                if (medicoIter.especialidad == especialidad && medicoIter.disponible) {
                    medicosEspecialidad.push_back(&medicoIter);
                }
            }

            if (medicosEspecialidad.empty()) {
                cout << "No hay medicos disponibles para esta especialidad.\n";
                break;
            }

            for (size_t i = 0; i < medicosEspecialidad.size(); ++i) {
                cout << i + 1 << ". " << medicosEspecialidad[i]->nombre << " " << medicosEspecialidad[i]->apellidos << endl;
            }

            int medicoSeleccion;
            cout << "Seleccione el numero del medico (0 para cancelar): ";
            cin >> medicoSeleccion;

            if (medicoSeleccion > 0 && medicoSeleccion <= medicosEspecialidad.size()) {
                medico = medicosEspecialidad[medicoSeleccion - 1];
            }
            else {
                cout << "Selección invalida. Operacion cancelada.\n";
                break;
            }

            // Seleccionar paciente
            cout << "Lista de pacientes registrados:\n";
            for (size_t i = 0; i < pacientes.size(); ++i) {
                cout << i + 1 << ". " << pacientes[i].nombre << " " << pacientes[i].apellidos << " - DNI: " << pacientes[i].dni << endl;
            }

            int pacienteSeleccion;
            cout << "Seleccione el numero del paciente (0 para cancelar): ";
            cin >> pacienteSeleccion;

            if (pacienteSeleccion > 0 && pacienteSeleccion <= pacientes.size()) {
                paciente = &pacientes[pacienteSeleccion - 1];
            }
            else {
                cout << "Seleccion invalida. Operacion cancelada.\n";
                break;
            }

            // Generar ID único dependiendo de las inciales del paciente
            id = generarIDCita(paciente);

            cout << "Nivel de urgencia (1-5, siendo 5 el mas urgente): ";
            cin >> nivelUrgencia;

            if (nivelUrgencia < 1 || nivelUrgencia > 5) {
                cout << "Nivel de urgencia invalido. Operacion cancelada.\n";
                break;
            }

            // Crear la cita y agregarla a la lista
            citas.emplace_back(id, fechaHora, especialidad, medico, paciente, nivelUrgencia);
            cout << "Cita asignada exitosamente.\n";
            cout << "ID: " << id << ", Fecha: " << fechaHora << ", Especialidad: " << especialidad;
            cout << ", Medico: " << medico->nombre << " " << medico->apellidos;
            cout << ", Paciente: " << paciente->nombre << " " << paciente->apellidos;
            cout << ", Nivel de urgencia: " << nivelUrgencia << endl;
            break;
        }
        case 2: {
            string id;
            cout << "Ingrese el ID de la cita a modificar: ";
            cin >> id;
            for (auto& cita : citas) {
                if (cita.id == id) {
                    cita.modificarCita();
                    cout << "Cita modificada con exito.\n";
                    break;
                }
            }
            break;
        }
        case 3: {
            string nombre, apellidos;
            cout << "Ingrese el nombre y apellidos del paciente o medico: ";
            cin >> nombre >> apellidos;

            vector<CitaMedica*> coincidencias;
            for (auto& cita : citas) {
                if (cita.medico->nombre == nombre && cita.medico->apellidos == apellidos ||
                    cita.paciente->nombre == nombre && cita.paciente->apellidos == apellidos) {
                    coincidencias.push_back(&cita);
                }
            }

            if (coincidencias.empty()) {
                cout << "No se encontraron coincidencias.\n";
                break;
            }

            for (size_t i = 0; i < coincidencias.size(); ++i) {
                cout << i + 1 << ". Cita ID: " << coincidencias[i]->id << " - Fecha: " << coincidencias[i]->fechaHora
                    << " - Medico: " << coincidencias[i]->medico->nombre << " " << coincidencias[i]->medico->apellidos
                    << " - Paciente: " << coincidencias[i]->paciente->nombre << " " << coincidencias[i]->paciente->apellidos << endl;
            }

            int seleccion;
            cout << "Seleccione el numero de la cita a cancelar: ";
            cin >> seleccion;

            if (seleccion > 0 && seleccion <= coincidencias.size()) {
                auto it = remove_if(citas.begin(), citas.end(), [&](CitaMedica& cita) {
                    return &cita == coincidencias[seleccion - 1];
                    });
                citas.erase(it, citas.end());
                cout << "Cita cancelada con exito.\n";
            }
            else {
                cout << "Seleccion invalida.\n";
            }
            break;
        }
        case 4: {
            short int subopciones;
            cout << "Elige una opcion para ordenar las citas:\n";
            cout << "1. Ordenar por fecha\n";
            cout << "2. Ordenar por nivel de urgencia\n";
            cout << "Opcion: ";
            cin >> subopciones;

            time_t t = time(nullptr);
            tm* now = localtime(&t);
            char currentDate[20];
            strftime(currentDate, sizeof(currentDate), "%Y-%m-%d %H:%M", now);

            if (subopciones == 1) {
                sort(citas.begin(), citas.end(), [](const CitaMedica& a, const CitaMedica& b) {
                    return a.fechaHora < b.fechaHora;
                    });

                cout << "Citas ordenadas por fecha (solo futuras):\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora >= currentDate) { // Filtrar citas futuras
                        cout << "ID: " << cita.id
                            << " - Fecha: " << cita.fechaHora
                            << " - Paciente: " << cita.paciente->nombre << " " << cita.paciente->apellidos
                            << " - Medico: " << cita.medico->nombre << " " << cita.medico->apellidos
                            << " - Nivel de urgencia: " << cita.nivelUrgencia << endl;
                    }
                }
            }
            else if (subopciones == 2) {
                sort(citas.begin(), citas.end(), [](const CitaMedica& a, const CitaMedica& b) {
                    return a.nivelUrgencia > b.nivelUrgencia;
                    });

                cout << "Citas ordenadas por nivel de urgencia (más urgentes primero, solo futuras):\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora >= currentDate) {
                        cout << "ID: " << cita.id
                            << " - Fecha: " << cita.fechaHora
                            << " - Nivel de urgencia: " << cita.nivelUrgencia
                            << " - Paciente: " << cita.paciente->nombre << " " << cita.paciente->apellidos
                            << " - Medico: " << cita.medico->nombre << " " << cita.medico->apellidos << endl;
                    }
                }
            }
            else {
                cout << "Opcion invalida.\n";
            }
            break;
        }
        case 5: {
            time_t t = time(nullptr);
            tm* now = localtime(&t);
            char currentDate[20];
            strftime(currentDate, sizeof(currentDate), "%Y-%m-%d %H:%M", now);

            short int subopciones;
            cout << "Elige una opcion:\n1. Citas pasadas\n2. Citas futuras\nOpcion: ";
            cin >> subopciones;

            if (subopciones == 1) {
                cout << "Citas pasadas:\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora < currentDate)
                        cout << "ID: " << cita.id << " - Fecha: " << cita.fechaHora << " - Paciente: " << cita.paciente->nombre << endl;
                }
            }
            else if (subopciones == 2) {
                cout << "Citas futuras:\n";
                for (const auto& cita : citas) {
                    if (cita.fechaHora >= currentDate)
                        cout << "ID: " << cita.id << " - Fecha: " << cita.fechaHora << " - Paciente: " << cita.paciente->nombre << " - Medico: " << cita.medico->nombre << endl;
                }
            }
            else {
                cout << "Opcion invalida.\n";
            }
            break;
        }
        case 6: {
            // Función para marcar una cita específica como atendida.
            cout << "Marcar una cita que esta pendiente como atendida\n";
            CitaMedica::marcarCitaComoAtendida(citas);
            break;
        }
        case 7: {
            cout << "Seleccione una especialidad de la lista:\n";
            for (size_t i = 0; i < especialidades.size(); ++i) {
                cout << i + 1 << ". " << especialidades[i] << "\n";
            }

            // Leer la selección del usuario
            int opcion;
            cout << "Ingrese el numero de la especialidad: ";
            cin >> opcion;

            // Validar la opción seleccionada
            if (opcion < 1 || opcion > static_cast<int>(especialidades.size())) {
                cout << "Opcion invalida. Intentelo de nuevo.\n";
                break;
            }

            // Obtener la especialidad seleccionada
            string especialidadSeleccionada = especialidades[opcion - 1];

            // Llamar a la función con la especialidad seleccionada
            CitaMedica::listarCitasPendientesPorEspecialidad(citas, especialidadSeleccionada);
            break;
        }
        case 8: {
            // Función para listar pacientes atendidos entre fechas.
            string fechaInicio, fechaFin;
            cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
            cin.ignore();
            getline(cin, fechaInicio);
            cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
            getline(cin, fechaFin);
            CitaMedica::listarPacientesAtendidosEntreFechas(citas, fechaInicio, fechaFin);
            break;
        }
        case 9:
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 9);
}

// Menú gestiones
/* void menuGestiones(Gestiones Gestiones) {
    short int opcion;
    do {
        cout << "--- Menu servicios ---\n";
        cout << "1. Hacer backups\n";
        cout << "2. Por si acaso falta algo\n";
        cout << "3. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
         
        }
        case 2: {
           
        }
        case 3: {
           
        }
        */

// Menú opciones
void menuPrincipal() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<CitaMedica> citas;
    Gestiones Gestiones;
    string archivoCSV = "pacientes.csv"; // Ruta al archivo CSV

    int opcion;
    do {
        cout << "--- Menu Principal ---\n";
        cout << "1. Gestionar pacientes\n";
        cout << "2. Gestionar medicos\n";
        cout << "3. Gestionar citas medicas\n";
        cout << "4. Gestiones varias (sin uso de momento)\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuPacientes(pacientes, archivoCSV); 
            break;
        case 2:
            menuMedicos(medicos);
            break;
        case 3:
            menuCitas(citas, medicos, pacientes);
            break;
        case 4:
            // menuGestiones(gestiones);
            break;
        case 5:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 5);
}

// Main
int main() {
    menuPrincipal();
    vector<Paciente> pacientes;
    string archivoCSV = "pacientes.csv";

    // Crear pacientes
    Paciente paciente1("Juan", "Perez", "12345678A", "2025-01-14", "Gripe");
    Paciente paciente2("Maria", "Lopez", "87654321B", "2025-01-13", "Faringitis");

    pacientes.push_back(paciente1);
    pacientes.push_back(paciente2);

    // Guardar pacientes en archivo CSV
    for (const auto& paciente : pacientes) {
        paciente.guardarEnArchivoCSV(archivoCSV);
    }

    // Leer archivo CSV para verificar
    Paciente::leerArchivoCSV(archivoCSV);

    // Modificar datos de un paciente
    pacientes[0].nombre = "Juan Carlos";
    pacientes[0].enfermedad = "Covid-19";

    // Actualizar archivo CSV con nuevos datos
    paciente1.modificarArchivoCSV(archivoCSV, pacientes);

    // Leer archivo CSV nuevamente para verificar los cambios
    Paciente::leerArchivoCSV(archivoCSV);

    return 0;
}