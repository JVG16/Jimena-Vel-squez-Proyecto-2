#include <iostream>
#include <vector> // Funciones.
#include <string>
#include <fstream> // Archivos.
#include <conio.h>

using namespace std;

// Función

struct Student
{
    string identification;
    string completeName;
    string province;
    string canton;
    string distrite;
    int age;
    int select;
};

// Función de estudiantes.

void RegistrarEstudiante (vector<Student>&student);
void IngresarCalificaciones (vector<Student>&student);
void ModificardatosEstudiante (vector<Student>&student);
void modificarregistroEstudiante (vector<Student>&student);
void EliminarRegistroEstudiante (vector<Student>&student);
void ReporteEstudiante (vector<Student>&student);

int main()
{
    setlocale(LC_CTYPE,"Spanish"); //Idioma y carácteres especiales.
    vector <Student>student;
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
        cout << "Digite por favor un número del 1-7" << endl;
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
            // Registrar función.

            RegistrarEstudiante(student);
            break;

        case 2:
        {
            cout << "Ingresar calificaciones en distintas materias." << endl;
            getch();
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "Modificar datos estudiantes." << endl;
            getch();
            cout << endl;
            break;
        }
        case 4:
        {
            cout << "Modificar registo de notas por estudiante." << endl;
            getch();
            cout << endl;
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
    }while(option != 7);
    return 0;

}

// Función Registrar Estudiante.

void RegistrarEstudiante(vector<Student>& student)
{
    cout << "Registrar estudiante." << endl;

    Student add;

    // Identificación
    bool verification;
    do
    {
        verification = true;
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        cin >> add.identification;

        if (add.identification.length() != 10)
        {
            verification = false;
        }
        else
        {
            for (int i = 0; i < add.identification.length(); i++)
            {
                if (add.identification[i] < '0' || add.identification[i] > '9')
                {
                    verification = false;
                    break;
                }
            }

            bool todosIguales = true;
            for (int i = 1; i < add.identification.length(); i++)
            {
                if (add.identification[i] != add.identification[0])
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

    } while (!verification);

    cin.ignore();
    getch();
    cout << endl;

    // Nombre completo
    do
    {
        verification = true;
        cout << "Ingrese el nombre completo (nombre y apellidos): ";
        getline(cin, add.completeName);

        for (int i = 0; i < add.completeName.length(); i++)
        {
            if (!isalpha(add.completeName[i]) && add.completeName[i] != ' ')
            {
                verification = false;
                break;
            }
        }

        if (!verification || add.completeName.length() == 0)
        {
            cout << "Error: solo debe ingresar letras y espacios." << endl;
        }

    } while (!verification || add.completeName.length() == 0);

    getch();
    cout << endl;

    // Residencia
    cout << "Ingrese el lugar de residencia:" << endl;
    cout << "- Provincia: ";
    getline(cin, add.province);
    cout << "- Cantón: ";
    getline(cin, add.canton);
    cout << "- Distrito: ";
    getline(cin, add.distrite);

    getch();
    cout << endl;

    // Edad
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

    } while (!verification || add.age < 18 || add.age > 100);

    getch();
    cout << endl;

    // Género
    cout << "Seleccione un género:" << endl;
    cout << "1. Masculino" << endl;
    cout << "2. Femenino" << endl;
    cout << "3. Otro" << endl;
    cin >> add.select;

    cout << "Género seleccionado: ";
    switch (add.select)
    {
    case 1: cout << "Masculino" << endl; break;
    case 2: cout << "Femenino" << endl; break;
    case 3: cout << "Otro" << endl; break;
    default: cout << "Opción inválida" << endl; break;
    }

    student.push_back(add);

     // Almacenar el archivo.

    ofstream archivo("ESTUDIANTES.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Identificación: " << add.identification << endl;
        archivo << "Nombre completo: " << add.completeName << endl;
        archivo << "Provincia: " << add.province << endl;
        archivo << "Cantón: " << add.canton << endl;
        archivo << "Distrito: " << add.distrite << endl;
        archivo << "Edad: " << add.age << endl;
        archivo << "Género: ";
        switch (add.select) {
            case 1: archivo << "Masculino"; break;
            case 2: archivo << "Femenino"; break;
            case 3: archivo << "Otro"; break;
        }
        archivo << endl;
        archivo << "-------------------------------" << endl;
        archivo.close();

        cout << "Estudiante registrado con éxito en 'ESTUDIANTES.txt'" << endl;
    } else {
        cout << "Error al abrir el archivo para guardar el estudiante." << endl;
    }
    getch();
    cout << endl;
}
