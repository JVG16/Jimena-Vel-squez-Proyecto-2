#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits> // Para limpiar el buffer de entrada

using namespace std;

struct Student
{
    string id;
    string fullName;
    string province;
    string canton;
    string district;
    int age;
    int gender; // 0: masculino, 1: femenino, 2: otro
};

// Prototipos de funciones
void saveStudentsToFile(const vector<Student>& students, const string& filename);
vector<Student> loadStudentsFromFile(const string& filename);
void displayStudents(const vector<Student>& students);
void addStudent(vector<Student>& students);
bool modifyStudentById(vector<Student>& students, const string& id);
void displayMenu();

int main()
{
    vector<Student> students;
    const string filename = "students.txt";
    int option;

    do {
        displayMenu();
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer

        switch(option)
        {
            case 1:
                addStudent(students);
                saveStudentsToFile(students, filename);
                break;
            case 2:
                students = loadStudentsFromFile(filename);
                displayStudents(students);
                break;
            case 3:
            {
                students = loadStudentsFromFile(filename);
                string idToModify;
                cout << "Ingrese el ID del estudiante a modificar: ";
                getline(cin, idToModify);

                if (modifyStudentById(students, idToModify))
                {
                    saveStudentsToFile(students, filename);
                    cout << "Estudiante modificado y cambios guardados exitosamente.\n";
                }
                break;
            }
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while (option != 4);

    return 0;
}

void displayMenu()
{
    cout << "\nMENU DE GESTION DE ESTUDIANTES\n";
    cout << "1. Ingresar nuevo estudiante\n";
    cout << "2. Listar todos los estudiantes\n";
    cout << "3. Modificar estudiante por ID\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
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
                case 0: student.id = token; break;
                case 1: student.fullName = token; break;
                case 2: student.province = token; break;
                case 3: student.canton = token; break;
                case 4: student.district = token; break;
                case 5: student.age = stoi(token); break;
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

void displayStudents(const vector<Student>& students)
{
    if (students.empty())
    {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\nLISTADO DE ESTUDIANTES:\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "ID\tNombre\t\t\tProvincia\tCantón\t\tDistrito\tEdad\tGénero\n";
    cout << "--------------------------------------------------------------------\n";

    for (const auto& student : students)
    {
        cout << student.id << "\t"
             << student.fullName.substr(0, 15) << (student.fullName.length() > 15 ? "..." : "") << "\t"
             << student.province.substr(0, 10) << (student.province.length() > 10 ? "..." : "") << "\t"
             << student.canton.substr(0, 10) << (student.canton.length() > 10 ? "..." : "") << "\t"
             << student.district.substr(0, 10) << (student.district.length() > 10 ? "..." : "") << "\t"
             << student.age << "\t";

        switch(student.gender)
        {
            case 0: cout << "Masculino"; break;
            case 1: cout << "Femenino"; break;
            case 2: cout << "Otro"; break;
            default: cout << "Desconocido";
        }
        cout << endl;
    }
}

void addStudent(vector<Student>& students)
{
    Student newStudent;

    cout << "\nINGRESO DE NUEVO ESTUDIANTE\n";

    cout << "ID: ";
    getline(cin, newStudent.id);

    cout << "Nombre completo: ";
    getline(cin, newStudent.fullName);

    cout << "Provincia: ";
    getline(cin, newStudent.province);

    cout << "Cantón: ";
    getline(cin, newStudent.canton);

    cout << "Distrito: ";
    getline(cin, newStudent.district);

    cout << "Edad: ";
    cin >> newStudent.age;

    cout << "Género (0: Masculino, 1: Femenino, 2: Otro): ";
    cin >> newStudent.gender;

    students.push_back(newStudent);
    cout << "Estudiante agregado exitosamente.\n";
}

bool modifyStudentById(vector<Student>& students, const string& id)
{
    for (auto& student : students)
    {
        if (student.id == id)
        {
            cout << "\nMODIFICANDO ESTUDIANTE CON ID: " << id << endl;
            cout << "Deje en blanco los campos que no desea modificar.\n";

            cout << "Nombre completo (" << student.fullName << "): ";
            string input;
            getline(cin, input);
            if (!input.empty()) student.fullName = input;

            cout << "Provincia (" << student.province << "): ";
            getline(cin, input);
            if (!input.empty()) student.province = input;

            cout << "Cantón (" << student.canton << "): ";
            getline(cin, input);
            if (!input.empty()) student.canton = input;

            cout << "Distrito (" << student.district << "): ";
            getline(cin, input);
            if (!input.empty()) student.district = input;

            cout << "Edad (" << student.age << "): ";
            getline(cin, input);
            if (!input.empty()) student.age = stoi(input);

            cout << "Género (" << student.gender << " - 0: Masculino, 1: Femenino, 2: Otro): ";
            getline(cin, input);
            if (!input.empty()) student.gender = stoi(input);

            return true;
        }
    }

    cout << "No se encontró un estudiante con ID: " << id << endl;
    return false;
}
