// AB_UNIT20_Mario Moreno.cpp: punto de entrada de la aplicación.

#include "AB_UNIT20_Mario Moreno.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <set>

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
    
    // Constructor principal
    Paciente(string nombre, string apellidos, string dni, string fechaIngreso, string enfermedad = "", vector<string> historialClinico = {})
        : nombre(nombre), apellidos(apellidos), dni(dni), fechaIngreso(fechaIngreso), enfermedad(enfermedad), historialClinico(historialClinico) {
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

    void listarPacientes(const vector<Paciente>& pacientes) {
        if (pacientes.empty()) {
            cout << "No hay pacientes registrados.\n";
            return;
        }

        cout << "--- Lista de Pacientes ---\n";
        for (size_t i = 0; i < pacientes.size(); ++i) {
            cout << "Paciente " << i + 1 << ":\n";
            cout << "Nombre: " << pacientes[i].nombre << "\n";
            cout << "Apellidos: " << pacientes[i].apellidos << "\n";
            cout << "DNI: " << pacientes[i].dni << "\n";
            cout << "Fecha de ingreso: " << pacientes[i].fechaIngreso << "\n";
            cout << "Enfermedad: " << (pacientes[i].enfermedad.empty() ? "No especificada" : pacientes[i].enfermedad) << "\n";
            cout << "Historial Clínico: " << (pacientes[i].historialClinico.empty() ? "No hay registros" : "") << "\n";
            if (!pacientes[i].historialClinico.empty()) {
                for (const string& registro : pacientes[i].historialClinico) {
                    cout << "  - " << registro << "\n";
                }
            }
            cout << "-------------------------\n";
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

    Medico(string nombre, string apellidos, string dni, bool disponible, string especialidad = "")
        : nombre(nombre), apellidos(apellidos), dni(dni), disponible(disponible), especialidad(especialidad) {
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
    static set<string> idGenerar;
    static vector<string> especialidades;

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

// Submenús
// Menú paciente
void menuPacientes(vector<Paciente>& pacientes) {
    short int opcion;
    do {
        cout << "--- Menu Pacientes ---\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Modificar datos del paciente\n";
        cout << "3. Lista de pacientes\n";
        cout << "4. Dar de alta medica\n";
        cout << "5. Dar de baja medica\n";
        cout << "6. Registrar historial clinico\n";
        cout << "7. Mostrar historial clinico\n";
        cout << "8. Reporte enfermedad cronica\n";
        cout << "9. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
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
                cout << "Ingrese fecha de ingreso (no si hay): ";
                cin.ignore();
                getline(cin, fechaIngreso);
                cout << "Ingrese enfermedad (opcional): ";
                cin.ignore();
                getline(cin, enfermedad);
                pacientes.emplace_back(nombre, apellidos, dni, fechaIngreso, enfermedad);
                cout << "Paciente registrado.\n";
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
            if (!pacientes.empty()) {
                pacientes[0].listarPacientes(pacientes);
            }
            else {
                cout << "No hay pacientes registrados.\n";
            }
            break;
        }
        case 4: {
            string dni;
            cout << "Ingrese el DNI del paciente para dar de alta medica: ";
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
        case 5: {
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
        case 6: {
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
        case 7: {
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
        case 8: {
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

// Ejemplos de pacientes, medicos y citas
void inicializarEjemplos(vector<Paciente>& pacientes, vector<Medico>& medicos, vector<CitaMedica>& citas) {
    pacientes = {
        {"Juan", "Perez Garcia", "12345678A", "2025-01-01", "Alergia", {"Alergia a fruto secos"}},
        {"Maria", "Lopez Hernandez", "23456789B", "2025-01-02", "Asma", {"Control de asma: receta de inhalador"}},
        {"Carlos", "Fernandez Gomez", "34567890C", "2025-01-03", "Diabetes", {"Diagnostico inicial: diabetes tipo 2"}},
        {"Ana", "Martinez Ruiz", "45678901D", "2025-01-04", "Hipertension", {"Consulta: padece presion arterial elavada"}},
        {"Pedro", "Gonzalez Sanchez", "56789012E", "2025-01-05", "Migraña", {"Tiene un tratamiento con analgesicos"}},
        {"Laura", "Hernandez Perez", "67890123F", "2025-01-06", "Artritis", {"Evaluacion inicial de articulaciones: manos con mayor dolor"}},
        {"Luis", "Garcia Torres", "78901234G", "2025-01-07", "", {}},
        {"Carmen", "Ruiz Romero", "89012345H", "2025-01-08", "Depresion", {"Primera consulta: inicio de terapia psicologica"}},
        {"Raul", "Sanchez Diaz", "90123456I", "2025-01-09", "Alergia", {"Control de alergias: prescripcion de antihistaminicos"}},
        {"Sara", "Gomez Castillo", "01234567J", "2025-01-10", "Cancer", {"Diagnostico inicial: derivacion a oncologia"}},
        { "Sofia", "Nunez Fernandez", "11223344A", "2025-01-11", "", {} },
        {"Daniel", "Ortiz Perez", "22334455B", "", "", {}},
        {"Lucia", "Ramirez Lopez", "33445566C", "", "", {}},
        {"Alejandro", "Morales Gomez", "44556677D", "", "", {}},
        {"Paula", "Diaz Torres", "55667788E", "", "", {}},
        {"Adrian", "Santos Sanchez", "66778899F", "", "", {}},
        {"Isabel", "Castro Martinez", "77889900G", "", "", {}},
        {"Miguel", "Reyes Hernandez", "88990011H", "", "", {}},
        {"Elena", "Vargas Ruiz", "99001122I", "", "", {}},
        {"Jorge", "Fuentes Garcia", "00112233J", "", "", {}}
    };

    medicos = {
        {"Dr. Jose", "Martinez Lopez", "11223344K", true, "Alergologia"},
        {"Dra. Andrea", "Garcia Hernandez", "22334455L", false, "Anatomia Patologica"},
        {"Dr. Mario", "Fernandez Ruiz", "33445566M", true, "Anestesiologia y Reanimacion"},
        {"Dra. Lucia", "Lopez Torres", "44556677N", true, "Angiologia y Cirugia Vascular"},
        {"Dr. Javier", "Gomez Sanchez", "55667788O", true, "Aparato Digestivo"},
        {"Dra. Elena", "Ruiz Perez", "66778899P", true, "Cardiologia"},
        {"Dr. Alvaro", "Hernandez Diaz", "77889900Q", true, "Psiquiatria"},
        {"Dra. Clara", "Martinez Garcia", "88990011R", true, "Medicina Interna"},
        {"Dr. Pablo", "Sanchez Romero", "99001122S", true, "Cirugia Oral y Maxilofacial"},
        {"Dra. Ines", "Gonzalez Castillo", "00112233T", true, "Cirugia Ortopedica y Traumatologia"},
        {"Dr. Roberto", "Morales Diaz", "12345001X", true, "Oncologia Medica"},
        {"Dra. Laura", "Torres Gomez", "23456002Y", true, "Cirugia Plastica, Estetica y Reparadora"},
        {"Dr. Sergio", "Campos Ortega", "34567003Z", false, "Cirugia Toracica"},
        {"Dra. Patricia", "Reyes Fuentes", "45678004W", true, "Dermatologia Medico-Quirurgica y Venereologia"},
        {"Dr. Diego", "Martin Rivera", "56789005V", true, "Endocrinologia y Nutricion"},
        {"Dra. Rosa", "Cabrera Leon", "67890106U", true, "Farmacologia Clinica"},
        {"Dr. Manuel", "Navarro Vega", "78901207T", false, "Geriatria"},
        {"Dra. Isabel", "Ramirez Sanchez", "89012308S", true, "Hematologia y Hemoterapia"},
        {"Dr. Juan", "Ortega Blanco", "90123409R", true, "Inmunologia"},
        {"Dra. Marta", "Vega Cruz", "01234510Q", true, "Medicina Fisica y Rehabilitacion"},
        { "Dr. Mario", "Moreno Lopez", "01234510Z", true, "Neurologia" }
    };

    citas = {
        {"C1", "2025-01-11 09:00", "Alergologia", &medicos[0], &pacientes[0], 3},
        {"C2", "2025-01-12 10:00", "Alergologia", &medicos[0], &pacientes[8], 4},
        {"C3", "2025-01-13 11:00", "Anestesiologia y Reanimacion", &medicos[2], &pacientes[10], 2},
        {"C4", "2025-01-14 12:00", "Angiologia y Cirugia Vascular", &medicos[3], &pacientes[6], 5},
        {"C5", "2025-01-15 13:00", "Aparato Digestivo", &medicos[4], &pacientes[11], 1},
        {"C6", "2025-01-16 09:00", "Cardiologia", &medicos[5], &pacientes[3], 3},
        {"C7", "2025-01-17 10:00", "Psiquiatria", &medicos[6], &pacientes[7], 4},
        {"C8", "2025-01-18 11:00", "Medicina Interna", &medicos[7], &pacientes[2], 2},
        {"C9", "2025-01-19 12:00", "Cirugia Oral y Maxilofacial", &medicos[8], &pacientes[12], 5},
        {"C10", "2025-01-20 13:00", "Cirugia Ortopedica y Traumatologia", &medicos[9], &pacientes[13], 1},
        {"C11", "2025-01-21 09:00", "Oncologia Medica", &medicos[10], &pacientes[9], 3},
        {"C12", "2025-01-22 10:00", "Cirugia Plastica, Estetica y Reparadora", &medicos[11], &pacientes[14], 4},
        {"C13", "2025-01-23 11:00", "Inmunologia", &medicos[18], &pacientes[15], 2},
        {"C14", "2025-01-24 12:00", "Dermatologia Medico-Quirurgica y Venereologia", &medicos[13], &pacientes[19], 5},
        {"C15", "2025-01-25 13:00", "Endocrinologia y Nutricion", &medicos[14], &pacientes[4], 1},
        {"C16", "2025-01-26 09:00", "Farmacologia Clinica", &medicos[15], &pacientes[1], 3},
        {"C17", "2025-01-27 10:00", "Neurologia", &medicos[20], &pacientes[16], 4},
        {"C18", "2025-01-28 11:00", "Hematologia y Hemoterapia", &medicos[17], &pacientes[17], 2},
        {"C19", "2025-01-29 12:00", "Inmunologia", &medicos[18], &pacientes[18], 5},
        {"C20", "2025-01-30 13:00", "Medicina Fisica y Rehabilitacion", &medicos[19], &pacientes[5], 2}
    };
}

// Menú opciones
void menuPrincipal() {
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<CitaMedica> citas;
    inicializarEjemplos(pacientes, medicos, citas);

    int opcion;
    do {
        cout << "--- Menu Principal ---\n";
        cout << "1. Gestionar pacientes\n";
        cout << "2. Gestionar medicos\n";
        cout << "3. Gestionar citas medicas\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuPacientes(pacientes); 
            break;
        case 2:
            menuMedicos(medicos);
            break;
        case 3:
            menuCitas(citas, medicos, pacientes);
            break;
        case 4:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 4);
}

// Main
int main() {
    menuPrincipal();
    return 0;
}