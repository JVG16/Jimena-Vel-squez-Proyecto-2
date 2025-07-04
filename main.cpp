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

struct Califications
{
    string identification;
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

    }
    while (!verification || add.completeName.length() == 0);

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

    }
    while (!verification || add.age < 18 || add.age > 100);

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

    // Almacenar el archivo.

    ofstream archivo("ESTUDIANTES.txt", ios::app);
    if (archivo.is_open())
    {
        archivo << "Identificación: " << add.identification << endl;
        archivo << "Nombre completo: " << add.completeName << endl;
        archivo << "Provincia: " << add.province << endl;
        archivo << "Cantón: " << add.canton << endl;
        archivo << "Distrito: " << add.distrite << endl;
        archivo << "Edad: " << add.age << endl;
        archivo << "Género: ";
        switch (add.select)
        {
        case 1:
            archivo << "Masculino";
            break;
        case 2:
            archivo << "Femenino";
            break;
        case 3:
            archivo << "Otro";
            break;
        }
        archivo << endl;
        archivo << "-------------------------------" << endl;
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

// Verificar identificación del estudiante.

void IngresarCalificaciones(vector<Califications>& califications)
{
    string cedula;
    char respuesta;
    bool VoF = false;

    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                 REGISTRO DE NOTAS POR MATERIA                   |"<<endl;
    cout << "------------------------------------------------------------------ "<<endl;
    getch();
    cout << endl;

    do
    {
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        cin >> cedula;
        cin.ignore();

        // Buscar en el archivo ESTUDIANTES.txt

        ifstream archivo("ESTUDIANTES.txt");
        string palabra;

        VoF = false;
        while (archivo >> palabra)
        {
            if (palabra == "Identificación:")
            {
                archivo >> palabra; // Leer la cédula
                if (palabra == cedula)
                {
                    VoF = true;

                    // Leer y mostrar el nombre
                    string etiqueta, nombre;
                    archivo >> etiqueta; // Lee "Nombre"
                    archivo >> etiqueta; // Lee "completo:"
                    getline(archivo, nombre); // El resto es el nombre
                    cout << "Nombre del estudiante:" << nombre << endl;
                    getch();
                    cout << endl;
                    break;
                }
            }
        }

        archivo.close();

        if (!VoF)
        {
            cout << " Estudiante no registrado";
            cout << "¿Desea ingresar otra identificación? (S/N): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
        }

    }
    while (!VoF && respuesta == 'S');

    if (!VoF)
    {
        cout << "Volver al menú principal"<< endl;
        getch();
        cout << endl;
        return;
    }


    // Registro de materias.

    int cantSubject;

    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                            MATERIA                              |"<< endl;
    cout << "-------------------------------------------------------------------"<<endl;
    getch();
    cout << endl;

    do
    {

        cout << "Ingrese la cantidad de tareas a registrar (máximo 3):";
        cin >> cantSubject;

        if (cantSubject < 1 || cantSubject > 3)
        {
            cout << "Error: debe ingresar mínimo una o como máximo tres tareas.";
        }

    }
    while(cantSubject < 1 || cantSubject > 3);
    getch();
    cout << endl;

    for (int i=0; i < cantSubject; i++)

    {

        Califications reg;
        reg.identification = cedula;
        do
        {
            cout << "Ingrese el nombre de la materia:";
            cin.ignore();
            getline (cin,reg.subject);

            if (reg.subject.empty())
            {
                cout << "Error: no debe dejar el espacio vacío." << endl;
            }

        }
        while (reg.subject.empty());
        getch();
        cout << endl;

        // Calificaciones.

        float firstProject;
        float secondProject;
        float ensayo;
        float foro;
        float defense;

        do
        {
            cout << "Ingrese las notas en base 10:" << endl;
            getch();
            cout << endl;

            cout << "Proyecto 1:";
            cin >> reg.firstProject;

            if (reg.firstProject < 0 || reg.firstProject > 10 )
            {
                cout << "Vuelva a ingresar las notas" << endl;
            }
        }
        while (reg.firstProject < 0 || reg.firstProject > 10);

        do
        {

            cout << "Proyecto 2:";
            cin >> reg.secondProject;

            if (reg.secondProject < 0 || reg.secondProject > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.secondProject < 0 || reg.secondProject > 10);

        do
        {

            cout << "Ensayo:";
            cin >> reg.ensayo;

            if (reg.ensayo < 0 || reg.ensayo > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.ensayo < 0 || reg.ensayo > 10);

        do
        {

            cout << "Defensa:";
            cin >> reg.defense;

            if (reg.defense < 0 || reg.defense > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.defense < 0 || reg.defense > 10);

        do
        {

            cout << "Foro:";
            cin >> reg.foro;

            if (reg.foro < 0 || reg.foro > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.foro < 0 || reg.foro > 10);
        getch();
        cout << endl;

        // Calcular el promedio y su estado.

        float prom;

        prom= (firstProject + secondProject + ensayo + defense + foro)/ 5.0 ;
        cout << "Promedio calculado:" << prom << endl;

        if (prom>=7)
        {
            cout << "Estado: Aprobado" << endl;
        }
        else
        {
            cout << "Estado: Reprobado" << endl;
        }
        getch();
        cout << endl;

        // Archivo.

        ofstream archivoNotas("CALIFICACIONES.txt", ios::app);

        if (archivoNotas.is_open())
        {
            archivoNotas << "Identificación: " << reg.identification << endl;
            archivoNotas << "Materia: " << reg.subject << endl;
            archivoNotas << "Proyecto 1: " << reg.firstProject << endl;
            archivoNotas << "Proyecto 2: " << reg.secondProject << endl;
            archivoNotas << "Ensayo: " << reg.ensayo << endl;
            archivoNotas << "Defensa: " << reg.defense << endl;
            archivoNotas << "Foro: " << reg.foro << endl;
            archivoNotas << "Promedio: " << prom << endl;
            archivoNotas << "Estado: " << (prom >= 7.0 ? "Aprobado" : "Reprobado") << endl;
            archivoNotas << "------------------------------------" << endl;

            archivoNotas.close();
        }
        else
        {
            cout << "Error al abrir el archivo para guardar las calificaciones." << endl;
        }

    }
}

