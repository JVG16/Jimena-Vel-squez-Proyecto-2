#include <iostream>
#include <vector> // Funciones.
#include <string>
#include <fstream> // Archivos.
#include <conio.h>
#include <locale.h>

using namespace std;

// Función

struct Student
{
    string id;
    string fullName;
    string province;
    string canton;
    string district;
    int age;
    int gender;
};

struct Califications
{
    string id;
    string subject;
    float firstProject;
    float secondProject;
    float ensayo;
    float foro;
    float defense;
    float average;
    string status;
};

// Función de estudiantes.

void RegistrarEstudiante (vector<Student>&students);
void ModificarDatosEstudiante (vector<Student>&students);
void modificarRegistroEstudiante (vector<Student>&students);
void EliminarRegistroEstudiante (vector<Student>&students);
void ReporteEstudiante (vector<Student>&students);
void saveStudentsToFile(const vector<Student>& students, const string& filename);
void saveStudentsModificationsToFile(const vector<Student>& students, const string& filename);
vector<Student> loadStudentsFromFile(const string& filename);

// Función para las calificaciones.

void IngresarCalificaciones (vector<Student>& students, vector<Califications>&califications);
void saveCalificationsToFile(const vector<Califications>& califications, const string& filename);
void ModificarRegistroNotasEstudiantes(vector<Student>&students,vector<Califications>&califications);
void saveRegistroNotasToFile (const vector<Califications>& califications, const string& filename);


int main()
{
    setlocale(LC_CTYPE,"Spanish"); //Idioma y carácteres especiales.
    vector <Student>students;
    vector <Califications>califications;
    int option;
    do
    {
        cout << "Menu Principal"<< endl;
        cout << "1.Registrar estudiante."<< endl;
        cout << "2.Ingresar calificaciones en distintas materias." << endl;
        cout << "3.Modificar datos estudiantes." << endl;
        cout << "4.Modificar registo de notas por estudiante." << endl;
        cout << "5.Eliminar registro de estudiante." << endl;
        cout << "6.Reporte de estudiantes, promedios y estado." << endl;
        cout << "7.Salir del programa." << endl;
        cout << "Digite por favor un número del 1-7." << endl;
        cin >> option;
        if (cin.fail())
        {
            cin.clear();
            while (cin.get() != '\n');
        }
        cout << endl;

        switch(option)
        {
        case 1:
        {
            RegistrarEstudiante(students);
            saveStudentsToFile(students, "ESTUDIANTES.txt");
            break;
        }
        case 2:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            IngresarCalificaciones(students, califications);
            saveCalificationsToFile(califications, "CALIFICACIONES.txt");
            break;
        }
        case 3:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            ModificarDatosEstudiante(students);
            saveStudentsModificationsToFile(students, "ESTUDIANTES.txt");
            break;
        }
        case 4:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            ModificarRegistroNotasEstudiantes(students, califications);
            saveRegistroNotasToFile(califications, "CALIFICACIONES.txt");
            break;
        }
        case 5:
        {
            cout << "Eliminar registro de estudiante." << endl;
            getch();
            cout << endl;
            break;
        }
        case 6:
        {
            cout << "Reporte de estudiantes, promedios y estado." << endl;
            getch();
            cout << endl;
            break;
        }
        case 7:
        {
            cout << "Salir del programa." << endl;
            getch();
            cout << endl;
            break;
            default:
                cout << "Opción no válida" << endl;
            }

        }
    }
    while(option != 7);
    return 0;

}

vector<Student> loadStudentsFromFile(const string& filename)
{
    vector<Student> students;
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error al abrir el archivo para lectura: " << filename << endl;
        return students;
    }

    string line;
    while (getline(inFile, line))
    {
        Student student;
        size_t pos = 0;
        string token;
        int field = 0;

        while ((pos = line.find(',')) != string::npos)
        {
            token = line.substr(0, pos);

            switch (field)
            {
            case 0:
                student.id = token;
                break;
            case 1:
                student.fullName = token;
                break;
            case 2:
                student.province = token;
                break;
            case 3:
                student.canton = token;
                break;
            case 4:
                student.district = token;
                break;
            case 5:
                student.age = stoi(token);
                break;
            }

            line.erase(0, pos + 1);
            field++;
        }

        // El último campo (gender) no tiene coma después
        student.gender = stoi(line);
        students.push_back(student);
    }

    inFile.close();
    return students;
}

void saveStudentsToFile(const vector<Student>& students, const string& filename)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Error al abrir el archivo para escritura: " << filename << endl;
        return;
    }

    for (const auto& student : students)
    {
        outFile << student.id << ","
                << student.fullName << ","
                << student.province << ","
                << student.canton << ","
                << student.district << ","
                << student.age << ","
                << student.gender << "\n";
    }
    outFile.close();
}


void saveCalificationsToFile(const vector<Califications>& califications, const string& filename)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Error al abrir el archivo para escritura: " << filename << endl;
        return;
    }

    for (const auto& calification : califications)
    {
        outFile << calification.id << ","
                << calification.subject << ","
                << calification.firstProject << ","
                << calification.secondProject << ","
                << calification.ensayo << ","
                << calification.defense << ","
                << calification.foro << ","
                << calification.average << ","
                << calification.status << "\n";
    }

    outFile.close();
}

void saveStudentsModificationsToFile(const vector<Student>& students, const string& filename)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Error al abrir el archivo para escritura: " << filename << endl;
        return;
    }

    for (const auto& student : students)
    {
        outFile << student.id << ","
                << student.fullName << ","
                << student.province << ","
                << student.canton << ","
                << student.district << ","
                << student.age << ","
                << student.gender << "\n";
    }
    outFile.close();
}

void saveRegistroNotasToFile (const vector<Califications>& califications, const string& filename)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Error al abrir el archivo para escritura: " << filename << endl;
        return;
    }

    for (const auto& calification : califications)
    {
        outFile << calification.id << ","
                << calification.subject << ","
                << calification.firstProject << ","
                << calification.secondProject << ","
                << calification.ensayo << ","
                << calification.defense << ","
                << calification.foro << ","
                << calification.average << ","
                << calification.status << "\n";
    }

    outFile.close();
}

// Función Registrar Estudiante.

void RegistrarEstudiante(vector<Student>& students)
{

    cout << "--------------------------------------------------" << endl;
    cout << "|             REGISTRAR UN ESTUDIANTE             |" << endl;
    cout << "--------------------------------------------------" << endl;
    getch();
    cout << endl;

    Student add;

    // Identificación.

    bool verification;
    do
    {
        verification = true;
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        cin >> add.id;

        if (add.id.length() != 10)
        {
            verification = false;
        }
        else
        {
            for (int i = 0; i < add.id.length(); i++)
            {
                if (add.id[i] < '0' || add.id[i] > '9')
                {
                    verification = false;
                    break;
                }
            }

            bool todosIguales = true;
            for (int i = 1; i < add.id.length(); i++)
            {
                if (add.id[i] != add.id[0])
                {
                    todosIguales = false;
                    break;
                }
            }
            if (todosIguales)
            {
                verification = false;
            }
        }

        if (!verification)
        {
            cout << "Error: debe ingresar 10 números y que no se repitan." << endl;
        }

    }
    while (!verification);

    cin.ignore();
    getch();
    cout << endl;

    // Nombre completo
    do
    {
        verification = true;
        cout << "Ingrese el nombre completo (Nombre y dos apellidos): ";
        getline(cin, add.fullName);

        for (int i = 0; i < add.fullName.length(); i++)
        {
            if (!isalpha(add.fullName[i]) && add.fullName[i] != ' ')
            {
                verification = false;
                break;
            }
        }

        if (!verification || add.fullName.length() == 0)
        {
            cout << "Error: solo debe ingresar letras y espacios." << endl;
        }

    }
    while (!verification || add.fullName.length() == 0);

    getch();
    cout << endl;

    // Residencia.

    cout << "Ingrese el lugar de residencia: " << endl;
    cout << "Provincia: ";
    getline(cin, add.province);
    cout << "Cantón: ";
    getline(cin, add.canton);
    cout << "Distrito: ";
    getline(cin, add.district);

    getch();
    cout << endl;

    // Edad.

    do
    {
        verification = true;
        cout << "Ingrese la edad (18-100): ";
        cin >> add.age;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Error: debe ingresar un número válido." << endl;
            verification = false;
        }

        if (add.age < 18 || add.age > 100)
        {
            cout << "Error: la edad debe estar dentro del rango (18-100)." << endl;
            verification = false;
        }

    }
    while (!verification || add.age < 18 || add.age > 100);

    getch();
    cout << endl;

    // Género
    cout << "Seleccione un género:" << endl;
    cout << "1. Masculino" << endl;
    cout << "2. Femenino" << endl;
    cout << "3. Otro" << endl;
    cin >> add.gender;

    cout << "Género seleccionado: ";
    switch (add.gender)
    {
    case 1:
        cout << "Masculino" << endl;
        break;
    case 2:
        cout << "Femenino" << endl;
        break;
    case 3:
        cout << "Otro" << endl;
        break;
    default:
        cout << "Opción inválida" << endl;
        break;
    }
    getch();
    cout << endl;
    students.push_back(add);
}

// Función para las calificaciones.

void IngresarCalificaciones(vector<Student>& students, vector<Califications>& califications)
{
    string cedula;
    char respuesta;
    bool encontrado = false;

    cout << "-------------------------------------------------------------------" << endl;
    cout << "|                 REGISTRO DE NOTAS POR MATERIA                   |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    getch();
    cout << endl;

    do
    {
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        cin >> cedula;
        cin.ignore();

        encontrado = false;
        for (const auto& student : students)
        {
            if (student.id == cedula)
            {
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            cout << "Estudiante no registrado." << endl;
            cout << "Desea ingresar otra identificacón? (S/N): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
        }

    }
    while (!encontrado && respuesta == 'S');

    if (!encontrado)
    {
        cout << "Volver al menú principal." << endl;
        getch();
        cout << endl;
        return;
    }
    getch();
    cout << endl;

    int cantSubject;

    cout << "-------------------------------------------------------------------" << endl;
    cout << "|                            MATERIAS                             |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    getch();
    cout << endl;

    do
    {
        cout << "Ingrese la cantidad de tareas a registrar (Máximo 3): ";
        cin >> cantSubject;
        if (cantSubject < 1 || cantSubject > 3)
        {
            cout << "Error: debe ingresar mínimo una o como máximo tres tareas." << endl;
        }
    }
    while (cantSubject < 1 || cantSubject > 3);
    getch();
    cout << endl;

    for (int i = 0; i < cantSubject; i++)
    {
        Califications reg;
        reg.id = cedula;
        cin.ignore();

        do
        {
            cout << "Ingrese el nombre de la materia: ";
            getline(cin, reg.subject);
            if (reg.subject.empty())
            {
                cout << "Error: no debe dejar el espacio vacío." << endl;
            }
        }
        while (reg.subject.empty());
        getch();
        cout << endl;

        cout << "Ingrese las notas en base 10:" << endl;

        do
        {
            cout << "Proyecto 1:";
            cin >> reg.firstProject;
            if (reg.firstProject < 0 || reg.firstProject > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        }
        while (reg.firstProject < 0 || reg.firstProject > 10);

        do
        {
            cout << "Proyecto 2:";
            cin >> reg.secondProject;
            if (reg.secondProject < 0 || reg.secondProject > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        }
        while (reg.secondProject < 0 || reg.secondProject > 10);

        do
        {
            cout << "Ensayo:";
            cin >> reg.ensayo;
            if (reg.ensayo < 0 || reg.ensayo > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        }
        while (reg.ensayo < 0 || reg.ensayo > 10);

        do
        {
            cout << "Defensa:";
            cin >> reg.defense;
            if (reg.defense < 0 || reg.defense > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        }
        while (reg.defense < 0 || reg.defense > 10);

        do
        {
            cout << "Foro:";
            cin >> reg.foro;
            if (reg.foro < 0 || reg.foro > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        }
        while (reg.foro < 0 || reg.foro > 10);

        getch();
        cout << endl;

        reg.average = (reg.firstProject * 0.1 + reg.secondProject * 0.2 + reg.ensayo * 0.3 + reg.defense * 0.1 + reg.foro * 0.3) / 5.0;
        reg.status = reg.average >= 7 ? "Aprobado" : "Reprobado";
        cout << "Promedio calculado: " << reg.average << endl;
        cout << "Estado: " << reg.status << endl;
        getch();
        cout << endl;

        califications.push_back(reg);
    } // FIN del for.
}

// Función case 3.

void ModificarDatosEstudiante(vector<Student>& students)
{
    string cedula;
    bool encontrado = false;

    cout << "--------------------------------------------------" << endl;
    cout << "|           MODIFICAR DATOS DE ESTUDIANTE        |" << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Ingrese la cédula del estudiante a modificar: ";
    cin >> cedula;

    for (auto& student : students)
    {
        if (student.id == cedula)
        {
            encontrado = true;

            cout << "Estudiante encontrado: " << student.fullName << endl;

            // Modificar residencia

            cout << "Ingrese nueva provincia: ";
            cin.ignore();
            getline(cin, student.province);

            cout << "Ingrese nuevo cantón: ";
            getline(cin, student.canton);

            cout << "Ingrese nuevo distrito: ";
            getline(cin, student.district);

            // Modificar edad

            int nuevaEdad;
            bool validaEdad;
            do
            {
                validaEdad = true;
                cout << "Ingrese nueva edad (18-100): ";
                cin >> nuevaEdad;

                if (cin.fail() || nuevaEdad < 18 || nuevaEdad > 100)
                {
                    cout << "Edad inválida. Intente de nuevo." << endl;
                    cin.clear();
                    cin.ignore();
                    validaEdad = false;
                }
            }
            while (!validaEdad);

            student.age = nuevaEdad;

            cout << "Datos actualizados correctamente." << endl;
            getch();
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Estudiante no registrado." << endl;
        getch();
    }
}


// Case 4.

void ModificarRegistroNotasEstudiantes(vector<Student>&students,vector<Califications>&califications)
{

    cout << "-------------------------------------------------------------------" << endl;
    cout << "|             MODIFICAR REGISTRO DE NOTAS DEL ESTUDIANTE            |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    getch();
    cout << endl;

    string cedula, materia;
    cout << "Digite el número de cédula (10 dígitos): ";
    cin >> cedula;
    cin.ignore();
    getch();
    cout << endl;

    cout << "Materia a modificar: ";
    getline(cin, materia);
    getch();
    cout << endl;

    // 3) Busco ese registro.

    bool encontrado = false;
    for (auto& reg : califications)
    {
        if (reg.id == cedula && reg.subject == materia)
        {
            encontrado = true;

            // 4) Pido nuevas notas.

            cout << "Digite la nueva nota para el proyecto 1: ";
            cin >> reg.firstProject;
            cout << "Digite la nueva nota para el proyecto 2: ";
            cin >> reg.secondProject;
            cout << "Digite la nueva nota para el ensayo: ";
            cin >> reg.ensayo;
            cout << "Digite la nueva nota para la defensa: ";
            cin >> reg.defense;
            cout << "Digite la nueva nota para el foro: ";
            cin >> reg.foro;

            // 5) Recalculo promedio y estado.

            reg.average = (reg.firstProject*0.1 + reg.secondProject*0.2 + reg.ensayo*0.3 + reg.defense*0.1 + reg.foro*0.3) / 5.0;
            reg.status = (reg.average >= 7.0? "Aprobado" : "Reprobado");

            cout << "Promedio: " << reg.average
                 << "   Estado: " << reg.status << "\n";
            getch();
            cout << endl;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "Registro no encontrado.\n";
    }
}
