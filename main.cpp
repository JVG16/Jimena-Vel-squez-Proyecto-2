/*
Universidad Estatal a Distancia.
Estudiante: Jimena Velásquez Gómez.
Cédula: 1-1919-0417.
Docente: Jose Alonso Solís Benavides.
Proyecto #2
Segundo cuatrimestre, 2025.

Descripción del proyecto:
Este programa permitirá que el usuario realice un registro con su información personal(identificación,
nombre completo, lugar de residencia, edad y género). Además, tendrá que registrar las asigntaturas (máximo tres)
con sus respectivas notas. El usuario tendrá la oportunidad de modificar algunos de sus datos personales y también podrá modificar
las notas de la asignatura.

Referencias:
- Página Web: http://www.casdreams.com/auladeinformatica/cet/comandos_de_c.htm.
- Vídeo YouTube Writing and calling functions:https://www.youtube.com/watch?v=RWZi2nnxJow&t=264s
- Canal YouTube Programación ATS https://youtu.be/GaqgqQL3wnQ?si=x4UhR0lDGrMB9vFW

*/

#include <iostream>
#include <vector> // Funciones.
#include <string>
#include <fstream> // Archivos.
#include <conio.h>
#include <iomanip>
#include <locale.h>
#include <windows.h>

using namespace std;



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

void RegisterStudent (vector<Student>&students);
void ModifyStudentData (vector<Student>&students);
void ModifyStudentRecord (vector<Student>&students);
void DeleteStudentRegistration(vector<Student>& students, vector<Califications>& califications);
void StudentReport(vector<Student>& students, vector<Califications>& califications);
void saveStudentsToFile(const vector<Student>& students, const string& filename);
void saveStudentsModificationsToFile(const vector<Student>& students, const string& filename);
void saveStudentReport(const vector<Student>& students, const vector<Califications>& califications, const string& filename);
vector<Student> loadStudentsFromFile(const string& filename);

// Función para las calificaciones.

void EnterGrades (vector<Student>& students, vector<Califications>&califications);
void saveCalificationsToFile(const vector<Califications>& califications, const string& filename);
void ModifyRecordStudentNotes(vector<Student>&students,vector<Califications>&califications);
void SaveRegistrationNotesToFile (const vector<Califications>& califications, const string& filename);
void saveDeleteStudentRegistration (const vector<Califications>& califications, const string& filename);
vector<Califications> loadCalificationsFromFile(const string& filename);

int main()
{
    vector <Student>students;
    vector <Califications> califications;

    setlocale(LC_ALL, "Spanish");

    int option;
    do
    {

        cout <<  "--------------------------------------------------" << endl;
        cout <<  "|                  MENU PRINCIPAL                |" << endl;
        cout <<  "--------------------------------------------------" << endl;
        getch();
        cout << endl;
        cout << "1.Registrar estudiante."<< endl;
        cout << "2.Ingresar calificaciones en distintas materias." << endl;
        cout << "3.Modificar datos estudiantes." << endl;
        cout << "4.Modificar registo de notas por estudiante." << endl;
        cout << "5.Eliminar registro de estudiante." << endl;
        cout << "6.Reporte de estudiantes, promedios y estado." << endl;
        cout << "7.Salir del programa." << endl;
        cout << "Digite por favor un numero del 1-7." << endl;
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
            RegisterStudent(students);
            saveStudentsToFile(students, "ESTUDIANTES.txt");
            break;
        }
        case 2:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            EnterGrades(students, califications);
            saveCalificationsToFile(califications, "CALIFICACIONES.txt");
            break;
        }
        case 3:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            ModifyStudentData(students);
            saveStudentsModificationsToFile(students, "ESTUDIANTES.txt");
            break;
        }
        case 4:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            ModifyRecordStudentNotes(students, califications);
            SaveRegistrationNotesToFile(califications, "CALIFICACIONES.txt");
            break;
        }
        case 5:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            DeleteStudentRegistration(students, califications);
            saveDeleteStudentRegistration(califications, "CALIFICACIONES.txt");
            saveStudentsModificationsToFile(students, "ESTUDIANTES.txt");
            SaveRegistrationNotesToFile(califications, "CALIFICACIONES.txt");
            break;
        }
        case 6:
        {
            students = loadStudentsFromFile("ESTUDIANTES.txt");
            califications = loadCalificationsFromFile("CALIFICACIONES.txt");
            StudentReport (students,califications);
            break;
        }
        case 7:
        {
            cout << "Salir del programa." << endl;
            getch();
            cout << endl;
            break;
            default:
                cout << "Opción no valida" << endl;
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
        size_t PComa = 0;
        string Info;
        int Op = 0;

        while ((PComa = line.find(',')) != string::npos)
        {
            Info = line.substr(0, PComa);

            switch (Op)
            {
            case 0:
                student.id = Info;
                break;
            case 1:
                student.fullName = Info;
                break;
            case 2:
                student.province = Info;
                break;
            case 3:
                student.canton = Info;
                break;
            case 4:
                student.district = Info;
                break;
            case 5:
                student.age = stoi(Info);
                break;
            }

            line.erase(0, PComa + 1);
            Op++;
        }

        student.gender = stoi(line);
        students.push_back(student);
    }

    inFile.close();
    return students;
}

vector<Califications> loadCalificationsFromFile(const string& filename)
{
    vector<Califications> califications;
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error al abrir el archivo para lectura: " << filename << endl;
        return califications;
    }
    string line;
    while (getline(inFile, line))
    {
        Califications reg;
        size_t PComa = 0;
        string Info;
        int Op = 0;

        while ((PComa = line.find(',')) != string::npos)
        {
            Info = line.substr(0, PComa);

            switch (Op)
            {
            case 0:
                reg.id = Info;
                break;
            case 1:
                reg.subject = Info;
                break;
            case 2:
                reg.firstProject = stof(Info);
                break;
            case 3:
                reg.secondProject = stof(Info);
                break;
            case 4:
                reg.ensayo = stof(Info);
                break;
            case 5:
                reg.foro = stof(Info);
                break;
            case 6:
                reg.defense = stof(Info);
                break;
            case 7:
                reg.average = stof(Info);
                break;
            }
            line.erase(0, PComa + 1);
            Op++;
        }
        reg.status = line;
        califications.push_back(reg);
    }
    inFile.close();
    return califications;

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

void SaveRegistrationNotesToFile (const vector<Califications>& califications, const string& filename)
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

void RegisterStudent(vector<Student>& students)
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
        cout << "Ingrese la identificacion del estudiante (10 digitos): ";
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
            cout << "Error: debe ingresar 10 numeros y que no se repitan." << endl;
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
    cout << "Canton: ";
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
            cout << "Error: debe ingresar un numero valido." << endl;
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
        cout << "Opcion incorrecta" << endl;
        break;
    }
    getch();
    cout << endl;
    students.push_back(add);
}

// Función para las calificaciones.

void EnterGrades(vector<Student>& students, vector<Califications>& califications)
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
        cout << "Ingrese la identificacion del estudiante (10 digitos): ";
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
            cout << "Desea ingresar otra identificacion? (S/N): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
        }

    }
    while (!encontrado && respuesta == 'S');

    if (!encontrado)
    {
        cout << "Volver al menu principal." << endl;
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
        cout << "Ingrese la cantidad de tareas a registrar (Maximo 3): ";
        cin >> cantSubject;
        if (cantSubject < 1 || cantSubject > 3)
        {
            cout << "Error: debe ingresar minimo una o como maximo tres tareas." << endl;
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
            cout << "Ingrese el nombre de la materia:";
            getline(cin, reg.subject);
            if (reg.subject.empty())
            {
                cout << "Error: no debe dejar el espacio vacio." << endl;
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
                cout << "Nota incorrecta." << endl;
        }
        while (reg.firstProject < 0 || reg.firstProject > 10);

        do
        {
            cout << "Proyecto 2:";
            cin >> reg.secondProject;
            if (reg.secondProject < 0 || reg.secondProject > 10)
                cout << "Nota incorrecta." << endl;
        }
        while (reg.secondProject < 0 || reg.secondProject > 10);

        do
        {
            cout << "Ensayo:";
            cin >> reg.ensayo;
            if (reg.ensayo < 0 || reg.ensayo > 10)
                cout << "Nota incorrecta." << endl;
        }
        while (reg.ensayo < 0 || reg.ensayo > 10);

        do
        {
            cout << "Foro:";
            cin >> reg.foro;
            if (reg.foro < 0 || reg.foro > 10)
                cout << "Nota incorrecta." << endl;
        }
        while (reg.foro < 0 || reg.foro > 10);

        do
        {
            cout << "Defensa:";
            cin >> reg.defense;
            if (reg.defense < 0 || reg.defense > 10)
                cout << "Nota incorrecta." << endl;
        }
        while (reg.defense < 0 || reg.defense > 10);



        getch();
        cout << endl;

        reg.average = (reg.firstProject * 0.10 + reg.secondProject * 0.20 + reg.ensayo * 0.30 + reg.foro * 0.10 + reg.defense * 0.30 );

        if (reg.average >= 7.0 && reg.average <= 10)
        {
            reg.status = "Aprobado";
        }
        else if (reg.average >= 5.0 && reg.average < 7.0)
        {
            reg.status = "Reposicion";
        }
        else
        {
            reg.status = "Reprobado";
        }

        cout << "Promedio calculado: " << reg.average << endl;
        cout << "Estado: " << reg.status << endl;
        getch();
        cout << endl;

        califications.push_back(reg);
    }
}

// Case 3.

void ModifyStudentData(vector<Student>& students)
{
    string cedula;
    bool encontrado = false;

    cout << "--------------------------------------------------" << endl;
    cout << "|           MODIFICAR DATOS DE ESTUDIANTE        |" << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Ingrese la cedula del estudiante a modificar: ";
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
                    cout << "Edad incorrecta. Intente de nuevo." << endl;
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

void ModifyRecordStudentNotes(vector<Student>&students,vector<Califications>&califications)
{

    cout << "-------------------------------------------------------------------" << endl;
    cout << "|             MODIFICAR REGISTRO DE NOTAS DEL ESTUDIANTE            |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    getch();
    cout << endl;

    string cedula, materia;
    cout << "Digite el numero de cedula (10 digitos): ";
    cin >> cedula;
    cin.ignore();
    getch();
    cout << endl;

    cout << "Materia a modificar: ";
    getline(cin, materia);
    getch();
    cout << endl;

    bool encontrado = false;
    for (auto& reg : califications)
    {
        if (reg.id == cedula && reg.subject == materia)
        {
            encontrado = true;

            // 4) Pido nuevas notas.

            cout << "Ingrese las nuevas base 10:" << endl;

            do
            {
                cout << "Digite la nueva nota para el proyecto 1:";
                cin >> reg.firstProject;
                if (reg.firstProject < 0 || reg.firstProject > 10)
                    cout << "Nota incorrecta" << endl;
            }
            while (reg.firstProject < 0 || reg.firstProject > 10);

            do
            {
                cout << "Digite la nueva nota para el proyecto 2:";
                cin >> reg.secondProject;
                if (reg.secondProject < 0 || reg.secondProject > 10)
                    cout << "Nota incorrecta." << endl;
            }
            while (reg.secondProject < 0 || reg.secondProject > 10);

            do
            {
                cout << "Digite la nueva nota para el ensayo:";
                cin >> reg.ensayo;
                if (reg.ensayo < 0 || reg.ensayo > 10)
                    cout << "Nota incorrecta" << endl;
            }
            while (reg.ensayo < 0 || reg.ensayo > 10);

            do
            {
                cout << "Digite la nueva nota para el foro:";
                cin >> reg.foro;
                if (reg.foro < 0 || reg.foro > 10)
                    cout << "Nota incorrecta" << endl;
            }
            while (reg.foro < 0 || reg.foro > 10);

            do
            {
                cout << "Digite la nueva nota para la defensa:";
                cin >> reg.defense;
                if (reg.defense < 0 || reg.defense > 10)
                    cout << "Nota incorrecta." << endl;
            }
            while (reg.defense < 0 || reg.defense > 10);


            reg.average = (reg.firstProject*0.10 + reg.secondProject*0.20 + reg.ensayo*0.30 + reg.foro*0.10 + reg.defense*0.30);

            if (reg.average >= 7.0 && reg.average <= 10)
            {
                reg.status = "Aprobado";
            }
            else if (reg.average >= 5.0 && reg.average < 7.0)
            {
                reg.status = "Reposición";
            }
            else
            {
                reg.status = "Reprobado";
            }

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

// Case 5.

void DeleteStudentRegistration(vector<Student>& students, vector<Califications>& califications)
{
    char respuesta = 'S';

    while (respuesta == 'S')
    {
        string cedula;
        cout << "---------------------------------------------------------" << endl;
        cout << "|               ELIMINAR REGISTRO DE ESTUDIANTE         |" << endl;
        cout << "---------------------------------------------------------" << endl;

        cout << "Ingrese la cedula del estudiante a eliminar: ";
        cin >> cedula;

        bool encontrado = false;

        for (const auto& student : students)
        {
            if (student.id == cedula)
            {
                encontrado = true;

                cout << "Estudiante encontrado:" << student.fullName << endl;

                char confirmacion;
                cout << "¿Esta seguro que desea eliminar este registro? (S/N):";
                cin >> confirmacion;
                confirmacion = toupper(confirmacion);

                if (confirmacion == 'S')
                {
                    // Crear nuevos vectores sin el estudiante

                    vector<Student> tempStudents;
                    for (const auto& s : students)
                    {
                        if (s.id != cedula)
                            tempStudents.push_back(s);
                    }
                    students = tempStudents;

                    vector<Califications> tempCalifications;
                    for (const auto& c : califications)
                    {
                        if (c.id != cedula)
                            tempCalifications.push_back(c);
                    }
                    califications = tempCalifications;

                    // Guardar los nuevos datos en los archivos

                    saveStudentsToFile(students, "ESTUDIANTES.txt");
                    SaveRegistrationNotesToFile(califications, "CALIFICACIONES.txt");

                    cout << "Registro eliminado correctamente." << endl;
                    getch();
                }
                else
                {
                    cout << "No se elimino el registro." << endl;
                    getch();
                }
                break;
            }
        }

        if (!encontrado)
        {
            cout << "Estudiante no encontrado." << endl;
            getch();
        }

        cout << "¿Desea eliminar otro estudiante? (S/N):";
        cin >> respuesta;
        respuesta = toupper(respuesta);
    }

    cout << "Regresar al menu principal" << endl;
    getch();
}

void saveDeleteStudentRegistration (const vector<Califications>& califications, const string& filename)
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

// Case 6

void StudentReport(vector<Student>& students, vector<Califications>& califications)
{

    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "|                    REPORTE DE ESTUDIANTES - NOTAS FINALES                           |" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    cout << "|    ID     | Nombre               | Materia            | Promedio     |   Estado     |" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    for (const auto& student : students)
    {
        for (const auto& nota : califications)
        {
            if (nota.id == student.id)
            {
                cout << "| " << setw(11) << left << student.id
                     << "| " << setw(22) << left << student.fullName
                     << "| " << setw(22) << left << nota.subject
                     << "| " << setw(8) << fixed << setprecision(2) << nota.average
                     << "| " << setw(10) << left << nota.status << "|" << endl;
            }
        }
    }

    cout << "--------------------------------------------------------------------------------------" << endl;
    getch();
}

//Detalles


