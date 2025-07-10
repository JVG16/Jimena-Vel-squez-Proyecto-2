#include <iostream>
#include <vector> // Funciones.
#include <string>
#include <fstream> // Archivos.
#include <conio.h>

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
    int cantSubject;
    string subject;
    float firstProject;
    float secondProject;
    float ensayo;
    float foro;
    float defense;
};

// Función de estudiantes.

void RegistrarEstudiante (vector<Student>&student);
void ModificardatosEstudiante (vector<Student>&student);
void modificarregistroEstudiante (vector<Student>&student);
void EliminarRegistroEstudiante (vector<Student>&student);
void ReporteEstudiante (vector<Student>&student);

// Función para las calificaciones.

void IngresarCalificaciones (vector<Califications>&califications);


int main()
{
    setlocale(LC_CTYPE,"Spanish"); //Idioma y carácteres especiales.
    vector <Student>student;
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
                IngresarCalificaciones(califications);
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
    }
    while(option != 7);
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
        cout << "Ingrese el nombre completo (nombre y apellidos): ";
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

    // Residencia
    cout << "Ingrese el lugar de residencia:" << endl;
    cout << "- Provincia: ";
    getline(cin, add.province);
    cout << "- Cantón: ";
    getline(cin, add.canton);
    cout << "- Distrito: ";
    getline(cin, add.district);

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

    student.push_back(add);

    // Guardar el estudiante sin etiquetas en el archivo (agregando al final)

ofstream archivo("ESTUDIANTES.txt", ios::app);
if (archivo.is_open())
{
    archivo << add.id << endl;
    archivo << add.fullName << endl;
    archivo << add.province << endl;
    archivo << add.canton << endl;
    archivo << add.district << endl;
    archivo << add.age << endl;
    archivo << add.gender << endl;  // Guardamos el número (1,2,3)
    archivo.close();

    cout << "Estudiante registrado con éxito en 'ESTUDIANTES.txt'" << endl;
}
else
{
    cout << "Error al abrir el archivo para guardar el estudiante." << endl;
}
getch();
cout << endl;

}

// Función para las calificaciones.

void IngresarCalificaciones(vector<Califications>& califications)
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

        ifstream archivo("ESTUDIANTES.txt");
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo de estudiantes." << endl;
            return;
        }

        encontrado = false;
        string linea;
        while (getline(archivo, linea))
        {
            if (linea == cedula)
            {
                encontrado = true;
                break;
            }
        }
        archivo.close();

        if (!encontrado)
        {
            cout << "Estudiante no registrado." << endl;
            cout << "¿Desea ingresar otra identificación? (S/N): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
        }

    } while (!encontrado && respuesta == 'S');

    if (!encontrado)
    {
        cout << "Volver al menú principal." << endl;
        getch();
        cout << endl;
        return;
    }

    int cantSubject;

    cout << "-------------------------------------------------------------------" << endl;
    cout << "|                            MATERIAS                             |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    getch();
    cout << endl;

    do
    {
        cout << "Ingrese la cantidad de tareas a registrar (máximo 3): ";
        cin >> cantSubject;
        if (cantSubject < 1 || cantSubject > 3)
        {
            cout << "Error: debe ingresar mínimo una o como máximo tres tareas." << endl;
        }
    } while (cantSubject < 1 || cantSubject > 3);
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
        } while (reg.subject.empty());
        getch();
        cout << endl;

        do
        {
            cout << "Ingrese Proyecto 1 (0-10): ";
            cin >> reg.firstProject;
            if (reg.firstProject < 0 || reg.firstProject > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        } while (reg.firstProject < 0 || reg.firstProject > 10);

        do
        {
            cout << "Ingrese Proyecto 2 (0-10): ";
            cin >> reg.secondProject;
            if (reg.secondProject < 0 || reg.secondProject > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        } while (reg.secondProject < 0 || reg.secondProject > 10);

        do
        {
            cout << "Ingrese Ensayo (0-10): ";
            cin >> reg.ensayo;
            if (reg.ensayo < 0 || reg.ensayo > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        } while (reg.ensayo < 0 || reg.ensayo > 10);

        do
        {
            cout << "Ingrese Defensa (0-10): ";
            cin >> reg.defense;
            if (reg.defense < 0 || reg.defense > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        } while (reg.defense < 0 || reg.defense > 10);

        do
        {
            cout << "Ingrese Foro (0-10): ";
            cin >> reg.foro;
            if (reg.foro < 0 || reg.foro > 10)
                cout << "Nota inválida, vuelva a ingresar." << endl;
        } while (reg.foro < 0 || reg.foro > 10);

        getch();
        cout << endl;

        float prom = (reg.firstProject * 0.1 + reg.secondProject * 0.2 + reg.ensayo * 0.3 + reg.defense * 0.1 + reg.foro * 0.3) / 5.0;
        cout << "Promedio calculado: " << prom << endl;
        cout << "Estado: " << (prom >= 7 ? "Aprobado" : "Reprobado") << endl;
        getch();
        cout << endl;

        ofstream archivoNotas("CALIFICACIONES.txt", ios::app);
        if (archivoNotas.is_open())
        {
            archivoNotas << reg.id << endl;
            archivoNotas << reg.subject << endl;
            archivoNotas << reg.firstProject << endl;
            archivoNotas << reg.secondProject << endl;
            archivoNotas << reg.ensayo << endl;
            archivoNotas << reg.defense << endl;
            archivoNotas << reg.foro << endl;
            archivoNotas << prom << endl;
            archivoNotas << (prom >= 7 ? "Aprobado" : "Reprobado") << endl;
            archivoNotas << "-----" << endl;
            archivoNotas.close();
        }
        else
        {
            cout << "Error al abrir el archivo para guardar las calificaciones." << endl;
        }
    } // FIN del for
} // FI

